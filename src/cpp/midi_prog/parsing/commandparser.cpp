#include "commandparser.h"
#include <regex>
#include "utils.h"
#include <sstream>
#include <fstream>
#include <iostream>

void Command::addParameter(std::string k, std::string v)
{
    this->values.push_back(v);
    this->parameters.insert(std::make_pair<std::string, std::string>(k.c_str(),v.c_str()));
}

std::string Command::getParameter(std::string key)
{
    return this->parameters[key];
}

std::string Command::getParameter(size_t index)
{
    return this->values[index];
}

bool Command::hasParameter(std::string p)
{
    return map_has_key<std::string, std::string>(this->parameters,p);
}

bool Command::hasNumberedParameter(std::string p, size_t index)
{
    p.append("_");
    p.append(std::to_string(index));
    return map_has_key<std::string, std::string>(this->parameters,p);
}

std::string Command::getNumberedParameter(std::string p, size_t index)
{
    p.append("_");
    p.append(std::to_string(index));
    return hasParameter(p) ? this->parameters[p] :  "";
}

std::string Command::getName()
{
    return this->name;
}

void Command::setName(std::string name)
{
    this->name = name;
}

std::map<std::string, std::string> Command::getParameters()
{
    return  this->parameters;
}

CommandParser::CommandParser()
{

}

std::vector<std::string> CommandParser::get_commands_file(std::string file)
{
    std::ifstream t(file);
    std::stringstream buffer;
    buffer << t.rdbuf();
    if(buffer.str() == "") std::cout << "File " << file << " couldn't be read" << std::endl;
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
            else if(current_command == "")
            {
                current_command = line;
            }
            else
            {
                commands.push_back(current_command);
                current_command = line;
            }
        }
    }

    if(current_command != "") commands.push_back(current_command);

    return commands;
}

std::vector<Command> CommandParser::parse_commands_file(std::string file)
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
    std::regex r_comm("([^\"\\s]+)(\\s?+)-");

    std::smatch match;

    if(std::regex_search(content, match, r_comm))
    {
        command.setName(match[1]);
    }

    std::string s = content;
    std::unordered_map<std::string, size_t> count;

    while(std::regex_search(s, match, r_params))
    {
        bool is_numbered = (match[1].str()[0] == '@');
        std::string p = static_cast<std::string>(match[1].str());
        if(is_numbered)
        {
            if(!umap_has_key<std::string, size_t>(count, p))
            {
                count.insert(std::make_pair<std::string, size_t>(p.c_str(), 0));
            }
            size_t c = count[p];
            count[p] = count[p]+1;
            p.erase(0,1);
            p.append("_");
            p.append(std::to_string(c));
        }

        command.addParameter(p, match[2]);
        s = match.suffix();
    }

    return command;
}
