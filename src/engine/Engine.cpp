#include "Engine.h"

namespace simpledb
{

std::string Engine::execute(const Command& cmd)
{
    switch (cmd.type)
    {
    case CommandType::SET:
        db.set( cmd.key, cmd.value);
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
        return db.del( cmd.key )? "OK" : "(nil)";
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