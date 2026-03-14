#include "parser.h"
#include <cctype>
#include <algorithm>
#include <iostream>

namespace simpledb
{

Command Parser::parse(const std::string& input)
{
    auto tokens = tokenize(input);

    if (tokens.empty())
        return buildCommand(tokens, CommandType::UNKNOWN);

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
        [](unsigned char c) { return std::toupper(c); });

    if (upper == "SET")    return CommandType::SET;
    if (upper == "GET")    return CommandType::GET;
    if (upper == "DEL")    return CommandType::DEL;
    if (upper == "EXISTS") return CommandType::EXISTS;
    if (upper == "EXIT")   return CommandType::EXIT;

    return CommandType::UNKNOWN;
}

Command Parser::buildCommand(const std::vector<std::string>& tokens, CommandType type)
{
    Command cmd;
    cmd.type = type;

    switch (type)
    {
        case CommandType::SET:
            if (tokens.size() >= 3)
            {
                cmd.key = tokens[1];
                cmd.value = tokens[2];
            }
            break;

        case CommandType::GET:
        case CommandType::DEL:
        case CommandType::EXISTS:
            if (tokens.size() >= 2)
                cmd.key = tokens[1];
            break;

        case CommandType::EXIT:
        case CommandType::UNKNOWN:
        default:
            break;
    }

    return cmd;
}

}
