#include "Storage.h"

#include <fstream>
#include <sstream>

namespace simpledb
{

Storage::Storage(const std::string& filename)
    : filename(filename)
{}

void Storage::save(const std::unordered_map<std::string, std::string>& data)
{
    std::ofstream file(filename, std::ios::trunc);

    if (!file.is_open())
        return;

    for (const auto& [key, value] : data)
    {
        file << key << "=" << value << "\n";
    }
}

std::unordered_map<std::string, std::string> Storage::load()
{
    std::unordered_map<std::string, std::string> data;

    std::ifstream file(filename);

    if (!file.is_open())
        return data;

    std::string line;

    while (std::getline(file, line))
    {
        size_t pos = line.find('=');

        if (pos == std::string::npos)
            continue;

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        data[key] = value;
    }

    return data;
}

}