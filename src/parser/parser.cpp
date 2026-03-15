#include "Parser.h"
#include <cctype>
#include <algorithm>
#include <unordered_map>

namespace simpledb
{

static const std::unordered_map<std::string, CommandType> commandMap =
{
    {"SET", CommandType::SET},
    {"GET", CommandType::GET},
    {"DEL", CommandType::DEL},
    {"EXISTS", CommandType::EXISTS},
    {"EXIT", CommandType::EXIT}
};

Command Parser::parse(const std::string& input)
{
    auto tokens = tokenize(input);

    if (tokens.empty())
        return Command{};

    CommandType type = getCommandType(tokens[0]);
    return buildCommand(tokens, type);
}

std::vector<std::string> Parser::tokenize(const std::string& input) const
{
    std::vector<std::string> tokens;

    size_t start = 0;
    size_t end;

    while ((end = input.find(' ', start)) != std::string::npos)
    {
        if (end > start)
            tokens.push_back(input.substr(start, end - start));

        start = end + 1;
    }

    if (start < input.size())
        tokens.push_back(input.substr(start));

    return tokens;
}

CommandType Parser::getCommandType(const std::string& token) const
{
    std::string upper = token;

    std::transform(
        upper.begin(),
        upper.end(),
        upper.begin(),
        [](unsigned char c){ return std::toupper(c); }
    );

    auto it = commandMap.find(upper);

    if (it != commandMap.end())
        return it->second;

    return CommandType::UNKNOWN;
}

Command Parser::buildCommand(const std::vector<std::string>& tokens, CommandType type) const
{
    Command cmd;
    cmd.type = type;

    switch (type)
    {
        case CommandType::SET:
            if (tokens.size() == 3)
            {
                cmd.key = tokens[1];
                cmd.value = tokens[2];
            }
            else
            {
                cmd.type = CommandType::UNKNOWN;
            }
            break;

        case CommandType::GET:
        case CommandType::DEL:
        case CommandType::EXISTS:
            if (tokens.size() == 2)
            {
                cmd.key = tokens[1];
            }
            else
            {
                cmd.type = CommandType::UNKNOWN;
            }
            break;

        case CommandType::EXIT:
            if (tokens.size() != 1)
                cmd.type = CommandType::UNKNOWN;
            break;
        case CommandType::UNKNOWN:
        default:
            break;
    }

    return cmd;
}

}
