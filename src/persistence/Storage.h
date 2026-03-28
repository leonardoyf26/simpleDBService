#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <unordered_map>

namespace simpledb
{

class Storage
{
public:
    Storage(const std::string& filename);

    void save(const std::unordered_map<std::string, std::string>& data);
    std::unordered_map<std::string, std::string> load();

private:
    std::string filename;
};

} // namespace simpledb

#endif