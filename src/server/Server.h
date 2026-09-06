#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <mutex>
#include <atomic>

#include "../engine/Engine.h"
#include "../parser/parser.h"

namespace simpledb
{

class Server
{
public:
    // Construtor com porta
    explicit Server(int port);

    ~Server();

    // Inicia o servidor
    void start();

    // Função estática para signal handler
    static void signalHandler(int signum);

    // Flag para controlar término
    static std::atomic<bool> shouldExit;

private:
    int port;
    int server_fd;

    Parser parser;
    Engine engine;
    std::mutex connection_mutex;  // Uma conexão por vez

    // Loop principal
    void run();

    // Aceita um cliente
    int acceptClient();

    // Trata comunicação com cliente (múltiplas requisições)
    void handleClient(int client_fd);

    // Lê mensagem do cliente
    std::string receive(int client_fd);

    // Envia resposta para cliente
    void sendResponse(int client_fd, const std::string& response);
};

} // namespace simpledb

#endif