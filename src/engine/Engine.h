#ifndef ENGINE_H
#define ENGINE_H

#include <string>

#include "../storage/database.h"
#include "../parser/command.h"
#include "../persistence/Storage.h"

namespace simpledb
{

class Engine
{
public:
    Engine();
    ~Engine() = default;

    // Executa um comando e retorna a resposta
    std::string execute(const Command& cmd);

private:
    Database db;
    Storage storage;
};

} // namespace simpledb

#endif