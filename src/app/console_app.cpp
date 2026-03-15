#include <iostream>
#include <string>

#include "../parser/Parser.h"
#include "../engine/Engine.h"

namespace simpledb
{

void runConsoleApp()
{
    Parser parser;
    Engine engine;

    std::cout << "SimpleDB Console v0.1\n";
    std::cout << "Type EXIT to quit\n\n";

    std::string input;

    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, input);

        // Ignora linha vazia
        if (input.empty())
            continue;

        Command cmd = parser.parse(input);

        std::string response = engine.execute(cmd);

        if (cmd.type == CommandType::EXIT)
        {
            std::cout << "Bye!\n";
            break;
        }

        std::cout << response << std::endl;
    }
}

} // namespace simpledb


// Ponto de entrada obrigatório do C++
int main()
{
    simpledb::runConsoleApp();
    return 0;
}