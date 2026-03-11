#include <unordered_map>
#include <string>
#include <optional>


#ifndef DATABASE_H
#define DATABASE_H

class Database
{
private:
    std::unordered_map<std::string, std::string> data;

public:
    void set(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key);
    bool del(const std::string& key);
    bool exists(const std::string& key) const;
};

#endif