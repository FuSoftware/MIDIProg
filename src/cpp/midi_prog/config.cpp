#include "config.h"

#include <fstream>
#include <vector>
#include "utils.h"
#include <iostream>

#include "synth.h"
#include "midicommand.h"
#include "parameter.h"

Config::Config()
{

}

void Config::run_file(std::string path)
{
    this->run(CommandParser::parse_commands_file(path));
}

void Config::run(std::vector<Command> commands)
{
    for(auto c: commands)
    {
        this->run(c);
    }
}

void Config::run(Command c)
{
    if(c.name == "synth")
    {
        Synth s(c.parameters["id"]);
        if(c.hasParameter("name")) s.setName(c.parameters["name"]);
        if(c.hasParameter("manufacturer")) s.setManufacturer(c.parameters["manufacturer"]);
        this->curr_synth = &s;
    }
    else if(c.name == "command")
    {
        if(this->curr_synth != nullptr)
        {
            MIDICommand comm(c.parameters["name"]);
        }
    }
    else
    {

    }
}

void Config::load_synth(std::string id)
{

}

void Config::report_parameter_number_error(std::string command, size_t number, size_t found)
{
    std::cout << "Expected '" << number << "' parameters for the '" << command << "' command. Found '" << found << "'" << std::endl;
}
