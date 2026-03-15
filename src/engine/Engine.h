#ifndef ENGINE_H
#define ENGINE_H

#include <string>

#include "../storage/database.h"
#include "../parser/command.h"

namespace simpledb
{

class Engine
{
public:
    Engine() = default;
    ~Engine() = default;

    // Executa um comando e retorna a resposta
    std::string execute(const Command& cmd);

private:
    Database db;
};

} // namespace simpledb

#endif