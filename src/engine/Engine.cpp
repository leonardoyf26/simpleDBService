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
        // SET: insere ou atualiza a chave
        db.set(cmd.key, cmd.value);
        storage.save(db.getAll());  // Persiste em arquivo
        return "OK";
        
    case CommandType::GET:
        // GET: retorna valor ou (nil) se não existir
        {
            auto result = db.get(cmd.key);
            if (result.has_value())
            {
                return result.value();
            }
            return "(nil)";
        }
        
    case CommandType::DEL:
        // DEL: remove a chave se existir
        if (db.del(cmd.key))
        {
            storage.save(db.getAll());  // Persiste em arquivo
            return "OK";
        }
        return "(nil)";
        
    case CommandType::EXISTS:
        // EXISTS: verifica se chave existe
        return db.exists(cmd.key) ? "true" : "false";
        
    case CommandType::EXIT:
        // EXIT: sinal para modo console encerrar
        return "EXIT";
        
    case CommandType::DISCONNECT:
        // DISCONNECT: sinal para servidor encerrar conexão
        return "DISCONNECT";
        
    case CommandType::UNKNOWN:
    default:
        return "ERR unknown command";
    }
}

}