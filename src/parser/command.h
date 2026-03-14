#include <string>

#ifndef COMMAND_H
#define COMMAND_H

namespace simpledb
{
enum class CommandType
{
    SET,
    GET,
    DEL,
    EXISTS,
    EXIT,
    UNKNOWN
};

struct Command
{
    CommandType type;
    std::string key;
    std::string value;

    Command() : type(CommandType::UNKNOWN) {}
};
} // namespace simpledb

#endif