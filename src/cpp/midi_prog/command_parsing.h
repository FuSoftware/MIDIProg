#ifndef COMMAND_PARSING_H
#define COMMAND_PARSING_H

#include <string>
#include <sstream>
#include <vector>

#include "utils.h"

std::vector<std::string> split(const std::string& s, char delimiter, bool trim_token = false)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream token_stream(s);
    while (std::getline(token_stream, token, delimiter))
    {
        if(trim_token) trim(token);
        tokens.push_back(token);
    }
    return tokens;
}

#endif // COMMAND_PARSING_H
