#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <csignal>

#include "./Server.h"

namespace simpledb
{

// Inicializar flag estática
std::atomic<bool> Server::shouldExit(false);

// Signal handler estático
void Server::signalHandler(int signum) {
    std::cout << "\n\nRecebido sinal " << signum << ". Encerrando servidor...\n";
    shouldExit = true;
}

Server::Server(int port) : port(port), server_fd(-1) {
    // Registrar signal handler para SIGTERM e SIGINT
    signal(SIGTERM, Server::signalHandler);
    signal(SIGINT, Server::signalHandler);

    // 1. Socket Creation (IPv4, TCP)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        throw std::runtime_error("Falha ao criar socket: " + std::string(strerror(errno)));
    }

    // 2. Configuration (Allow address reuse)
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        close(server_fd);
        throw std::runtime_error("Falha em setsockopt: " + std::string(strerror(errno)));
    }

    // 3. Prepare address structure
    sockaddr_in serverAddress{}; 
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY; 
    serverAddress.sin_port = htons(static_cast<uint16_t>(port));

    // 4. Bind (Associate socket with the address and port)
    if (bind(server_fd, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) < 0) {
        close(server_fd);
        throw std::runtime_error("Erro no bind (Porta " + std::to_string(port) + " ocupada?): " + std::string(strerror(errno)));
    }

    // 5. Listen (Mark socket as passive to accept incoming connections)
    // Backlog de 1: apenas 1 conexão simultânea (compatível com mutex de uma por vez)
    if (listen(server_fd, 1) < 0) { 
        close(server_fd);
        throw std::runtime_error("Erro no listen: " + std::string(strerror(errno)));
    }

    std::cout << "Servidor SimpleDB na porta " << port << " (uma conexão por vez)\n";
}

Server::~Server() {
    // Close the server socket if it's open
    if (server_fd != -1) {
        close(server_fd);
    }
}

void Server::start()
{
    run();
}

void Server::run()
{
    while (!shouldExit)
    {
        int clientSocket = acceptClient();
        if (clientSocket < 0)
            continue;

        handleClient(clientSocket);
    }

    std::cout << "Servidor encerrado.\n";
}

int Server::acceptClient() {
    struct sockaddr_in clientAddress{};
    socklen_t clientLen = sizeof(clientAddress);

    // Tentar aceitar cliente com timeout
    int client_fd = accept(server_fd, reinterpret_cast<struct sockaddr*>(&clientAddress), &clientLen);

    if (client_fd < 0) {
        if (shouldExit)
            return -1;
        std::cerr << "Erro ao aceitar conexão: " << strerror(errno) << std::endl;
        return -1;
    }

    std::cout << "Cliente conectado de " << inet_ntoa(clientAddress.sin_addr) << "\n";
    return client_fd;
}

void Server::handleClient(int client_fd)
{
    if (client_fd < 0) 
        return;

    // Lock de mutex: apenas UMA conexão é processada por vez
    // Outras conexões aguardam até que a atual seja finalizada
    // Isso é intencional: força processamento sequencial para evitar race conditions
    std::lock_guard<std::mutex> lock(connection_mutex);

    std::cout << "Iniciando sessão do cliente\n";

    // Loop: cliente pode enviar múltiplas requisições na mesma conexão
    // Encerra quando enviar DISCONNECT ou fechar conexão
    while (!shouldExit)
    {
        std::string message = receive(client_fd);

        // Se recebeu vazio, cliente fechou
        if (message.empty())
        {
            std::cout << "Cliente desconectou\n";
            break;
        }

        std::cout << "Recebido: " << message << "\n";
        Command cmd = parser.parse(message);

        std::string response = engine.execute(cmd);
        sendResponse(client_fd, response);

        // Se cliente enviou DISCONNECT, encerrar sessão
        if (cmd.type == CommandType::DISCONNECT)
        {
            std::cout << "Cliente solicitou desconexão\n";
            break;
        }
    }

    // Fechar socket do cliente
    close(client_fd);
    std::cout << "Sessão do cliente encerrada\n";
}

std::string Server::receive(int client_fd)
{
    std::string message(1024, '\0');
    int bytes = recv(client_fd, message.data(), message.size(), 0);

    if (bytes <= 0)
        return "";

    message.resize(bytes);
    return message;
}

void Server::sendResponse(int client_fd, const std::string& response)
{
    send(client_fd, response.data(), response.size(), 0);
}

}