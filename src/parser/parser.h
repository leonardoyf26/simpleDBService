#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "command.h"

namespace simpledb
{

class Parser
{
public:
    Command parse(const std::string& input);

private:
    std::vector<std::string> tokenize(const std::string& input) const;
    CommandType getCommandType(const std::string& token) const;
    Command buildCommand(const std::vector<std::string>& tokens, CommandType type) const;
    std::string trim(const std::string& str) const;
};

} // namespace simpledb

#endif