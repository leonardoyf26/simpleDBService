#include "Engine.h"

namespace simpledb
{

Engine::Engine()
    : storage("data/db.txt")
{
    auto data = storage.load();
    db.loadData(data);
}

std::string Engine::execute(const Command& cmd)
{
    switch (cmd.type)
    {
    case CommandType::SET:
        db.set( cmd.key, cmd.value);
        storage.save(db.getAll());
        return "OK";
    case CommandType::GET:
        {
            auto result = db.get(cmd.key);
            if (result.has_value())
            {
                return result.value();
            }
            return "(nil)";
        }
    case CommandType::DEL:
        if (db.del(cmd.key))
        {
            storage.save(db.getAll());
            return "OK";
        }
        return "(nil)";
    case CommandType::EXISTS:
        return db.exists( cmd.key )? "true" : "false";
    case CommandType::EXIT:
        return "EXIT";
    case CommandType::UNKNOWN:
    default:
        return "ERR unknown command";
    }
}

}