#include "config.h"

#include <fstream>
#include <vector>
#include "utils.h"
#include <iostream>

#include "parameter.h"

Config::Config()
{

}

void Config::run_file(std::string path)
{
    this->curr_folder = get_folder(path);
    std::vector<Command> commands = CommandParser::parse_commands_file(path);
    this->run(commands);
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
    if(c.getName() == "synth")
    {
        std::string id = c.getParameter("id");
        Synth* s = new Synth(id);
        if(c.hasParameter("name")) s->setName(c.getParameter("name"));
        if(c.hasParameter("manufacturer")) s->setManufacturer(c.getParameter("manufacturer"));
        this->curr_synth = s;
        std::pair<std::string, Synth*> data(id, s);
        this->synths.insert(data);
    }
    else if(c.getName() == "command")
    {
        if(this->curr_synth != nullptr)
        {
            MIDICommand comm(c.getParameter("name"));
            comm.addAliases(c.getParameter("alias"));
            comm.setMidi(c.getParameter("midi"));

            //Parameters
            size_t i = 0;
            std::string key = "parameter";
            while(c.hasNumberedParameter("parameter", i))
            {
                std::string p = c.getNumberedParameter("parameter",i);
                i++;
                comm.addParameter(p);
            }
            this->curr_synth->getCommands()->push_back(comm);
        }
    }
    else if(c.getName() == "source")
    {
        std::string path = (this->folder != "" ? this->folder + "/" : "") + c.getParameter(0);
        this->run_file(path);
    }
    else if(c.getName() == "folder")
    {
        if(c.hasParameter("type"))
        {
            std::string type = c.getParameter("type");

            if(type == "relative")
            {
                this->folder = this->curr_folder;
            }
            else if (type == "absolute")
            {
                this->folder = "";
            }
        }
    }
    else
    {
        std::cout << "Unrecognized command " << c.getName() << std::endl;
    }
}

Synth* Config::get_synth(std::string id)
{
    return map_has_key(this->synths, id) ? this->synths[id] : nullptr;
}

void Config::report_parameter_number_error(std::string command, size_t number, size_t found)
{
    std::cout << "Expected '" << number << "' parameters for the '" << command << "' command. Found '" << found << "'" << std::endl;
}

std::vector<std::string> Config::get_synth_list()
{
    std::vector<std::string> keys;
    for(auto it = this->synths.begin(); it != this->synths.end(); ++it) {
        keys.push_back(it->first);
    }
    return keys;
}

std::vector<Synth*> Config::get_synth_values()
{
    std::vector<Synth*> values;
    for(auto it = this->synths.begin(); it != this->synths.end(); ++it) {
        values.push_back(it->second);
    }
    return values;
}
