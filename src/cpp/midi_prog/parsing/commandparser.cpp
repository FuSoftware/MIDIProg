#include "commandparser.h"
#include <regex>
#include "utils.h"
#include <sstream>
#include <fstream>
#include <iostream>

CommandParser::CommandParser()
{

}

std::vector<std::string> CommandParser::get_commands_file(std::string file)
{
    std::ifstream t(file);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return CommandParser::get_commands(buffer.str());
}

std::vector<std::string> CommandParser::get_commands(std::string content)
{
    std::string current_command = "";
    std::vector<std::string> commands;
    std::vector<std::string> lines =  split(content, '\n', true);

    for(std::string line : lines)
    {
        if(line != "")
        {
            if (line[0] == '-')
            {
                current_command += line;
            }
            else
            {
                commands.push_back(current_command);
                current_command = line;
            }
        }
    }

    return commands;
}

static std::vector<Command> parse_commands_file(std::string file)
{
    return CommandParser::parse_commands(CommandParser::get_commands_file(file));
}

std::vector<Command> CommandParser::parse_commands(std::vector<std::string> content)
{
    std::vector<Command> commands;

    for(std::string c : content)
    {
        commands.push_back(parse_command(c));
    }

    return commands;
}

Command CommandParser::parse_command(std::string content)
{
    Command command;
    std::regex r_params("-(\\S+) \"([^\"]+)\"");
    std::regex r_comm("([^\"\\s]+)-");

    std::smatch match;

    if(std::regex_search(content, match, r_comm))
    {
        command.name = match[1];
    }

    std::string s = content;

    while(std::regex_search(s, match, r_params))
    {
        command.parameters.insert(std::make_pair<std::string, std::string>(match[1],match[2]));
        s = match.suffix();
    }

    return command;
}
