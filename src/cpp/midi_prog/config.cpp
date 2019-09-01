#include "config.h"

#include <fstream>
#include <vector>
#include "utils.h"
#include "command_parsing.h"
#include <iostream>

#include "synth.h"

Config::Config()
{

}

void Config::run_file(std::string path)
{
    std::ifstream input(path);

    for(std::string line; getline( input, line );)
    {
        trim(line);
        if(line != "")
        {
            this->run(line);
        }
    }
}

void Config::run(std::string line)
{
    std::vector<std::string> tokens = split(line, '=', true);
    ConfigCommand command = resolve_command(tokens[0]);

    switch(command)
    {
        case ConfigCommand::SOURCE:
            if(tokens.size() == 2) this->run_file(tokens[1]);
            else report_parameter_number_error("source", 1, tokens.size()-1);
            break;
        case ConfigCommand::DEFINE_SYNTH:
            break;
        case ConfigCommand::DEFINE_COMMAND:
            break;
        case ConfigCommand::SET_NAME:
            if(tokens.size() == 2) this->curr_synth->setName(tokens[1]);
            else report_parameter_number_error("set name", 1, tokens.size()-1);
            break;
        case ConfigCommand::SET_MANUFACTURER:
            break;
        case ConfigCommand::SET_ALIAS:
            break;
        case ConfigCommand::SET_PARAMETER:
            break;
        case ConfigCommand::SET_SYSEX:
            break;
        case ConfigCommand::UNKNOWN:
            std::cout << "Found unknown command : '" << line << "'" << std::endl;
            break;
    }
}

void Config::load_synth(std::string id)
{

}

ConfigCommand Config::resolve_command(std::string &command)
{
    if (command == "define command")
        return ConfigCommand::DEFINE_COMMAND;
    else if (command == "set sysex")
        return ConfigCommand::SET_SYSEX;
    else if (command == "set parameter")
        return ConfigCommand::SET_PARAMETER;
    else if (command == "set alias")
        return ConfigCommand::SET_ALIAS;
    else if (command == "define synth")
        return ConfigCommand::DEFINE_SYNTH;
    else if (command == "set manufacturer")
        return ConfigCommand::SET_MANUFACTURER;
    else if (command == "set name")
        return ConfigCommand::SET_NAME;
    else if (command == "source")
        return ConfigCommand::SOURCE;
    else
        return ConfigCommand::UNKNOWN;
}

void Config::report_parameter_number_error(std::string command, size_t number, size_t found)
{
    std::cout << "Expected '" << number << "' parameters for the '" << command << "' command. Found '" << found << "'" << std::endl;
}
