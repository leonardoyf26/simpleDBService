#include <string>
#include <vector>
#include "command.h"

#ifndef PARSER_H
#define PARSER_H

namespace simpledb
{

class Parser
{
public:
    Command parse(const std::string& input);

private:
    std::vector<std::string> tokenize(const std::string& input) const;
    CommandType getCommandType(const std::string& token) const;
    Command buildCommand(const std::vector<std::string>& tokens, CommandType type);
};

} // namespace simpledb

#endif