#include "interpreter.h"
#include <iostream>
#include <fstream>
#include "utils.h"

Interpreter::Interpreter()
{

}

void Interpreter::run_file(std::string path)
{
    this->current_folder = get_folder(path);
    std::ifstream input( path );
    for(std::string line; getline(input, line); )
    {
        this->run(line);
    }
}

void Interpreter::run(std::vector<std::string> commands)
{
    for(auto c : commands)
    {
        this->run(c);
    }
}

void Interpreter::run(std::string command)
{
    trim(command);
    if(command == "") return;

    std::vector<std::string> tokens = split(command, ' ', true);
    std::string c = tokens[0];

    std::cout << "Running "<< c << std::endl;

    if(c == "synth")
    {
        this->load_synth(tokens[1]);
    }
    else if(c == "config")
    {
        std::string path = (this->folder != "" ? this->folder + "/" : "") + tokens[1];
        this->config.run_file(path);
    }
    else if(c == "channel")
    {
        this->channel = std::stoi(tokens[1]);
    }
    else if(c == "sysex")
    {
        std::string alias = tokens[1];
        std::vector<long> values;

        if(this->channel >= 0) values.push_back(channel);

        for(size_t i=2; i<tokens.size(); i++)
        {
            values.push_back(std::stoi(tokens[i]));
        }

        std::string data = this->sysex[alias]->generate(values);
        std::cout << data << std::endl;
    }
    else if(c == "midi")
    {

    }
    else if(c == "folder")
    {
        if(tokens[1] == "relative")
        {
            this->folder = this->current_folder;
        }
        else if(tokens[1] == "absolute")
        {
            this->folder = "";
        }

    }
    else
    {
        std::cout << "Unknown command : " << c << std::endl;
    }
}

void Interpreter::load_synth(std::string id)
{
    Synth *s = config.get_synth(id);
    this->synth = s;

    std::vector<MIDICommand> *commands = s->getCommands();
    this->sysex.clear();

    for(size_t i=0; i<commands->size(); i++)
    {
        MIDICommand *m = &commands->at(i);
        for(auto a : m->getAliases())
        {
            std::pair<std::string, MIDICommand*> p(a,m);
            this->sysex.insert(p);
        }
    }
}
