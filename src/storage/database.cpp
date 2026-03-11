#include "Database.h"

void Database::set(const std::string& key, const std::string& value)
{
    data[key] = value;
}

std::optional<std::string> Database::get(const std::string& key)
{
    auto it = data.find(key);
    if(it != data.end())
    {
        return it->second;
    }
    return std::nullopt;
}

bool Database::del(const std::string& key)
{
    return data.erase(key) > 0;
}

bool Database::exists(const std::string& key) const
{
    return data.find(key) != data.end();
}