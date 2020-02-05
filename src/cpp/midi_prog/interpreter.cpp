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

    //std::cout << "Running "<< c << std::endl;

    if(c == "synth")
    {
        this->sysex = this->load_synth(tokens[1]);
    }
    else if(c == "interactive")
    {
        this->interactive();
    }
    else if(c == "config")
    {
        std::string path = (this->folder != "" ? this->folder + "/" : "") + tokens[1];
        this->config.run_file(path);
    }
    else if(c == "midiconfig")
    {
        std::string path = (this->folder != "" ? this->folder + "/" : "") + tokens[1];
        this->config.run_file(path);
        if(this->config.get_synth("midi") != nullptr)
        {
            this->midi = this->load_synth("midi");
        }
        else
        {
            std::cout << "Could not load the generic midi configuration" << std::endl;
        }

    }
    else if(c == "port")
    {
        this->port = std::stoi(tokens[1]);
        this->interface.setPort(this->port);
    }
    else if(c == "portlist")
    {
        this->interface.listPorts();
    }
    else if(c == "channel")
    {
        this->channel = std::stoi(tokens[1]);
    }
    else if(c == "receive")
    {
        this->interface.waitMidi();
    }
    else if(c == "send")
    {
        std::vector<unsigned char> data = stob(tokens[1]);
        this->interface.send(data);
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

        std::vector<unsigned char> data = this->sysex[alias]->generateBytes(values);

        std::cout << this->sysex[alias]->generate(values) << std::endl;
        std::cout << std::hex;
        for(auto d : data)
        {
            std::cout << std::hex << static_cast<int>(d) << " ";
        }
        std::cout << std::dec << std::endl;

        this->interface.send(data);
    }
    else if(c == "midi")
    {
        std::string alias = tokens[1];
        std::vector<long> values;

        if(this->channel >= 0) values.push_back(channel);

        for(size_t i=2; i<tokens.size(); i++)
        {
            values.push_back(std::stoi(tokens[i]));
        }

        std::vector<unsigned char> data = this->midi[alias]->generateBytes(values);

        std::cout << this->midi[alias]->generate(values) << std::endl;
        std::cout << std::hex;
        for(auto d : data)
        {
            std::cout << std::hex << static_cast<int>(d) << " ";
        }
        std::cout << std::dec << std::endl;

        this->interface.send(data);
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

void Interpreter::interactive()
{
    std::string command;
    while (true)
    {
        if(this->synth != nullptr) std::cout << this->synth->getName();
        std::cout << "@" << this->port;
        if(this->channel > -1) std::cout << "-" << this->channel;
        std::cout << " > ";

        std::getline(std::cin, command);

        std::vector<std::string> commands = split(command, '|', true);

        if(command == "exit"){
            break;
        } else{
            this->run(commands);
        }
    }
}

std::map<std::string, MIDICommand*> Interpreter::load_synth(std::string id)
{
    Synth *s = config.get_synth(id);
    this->synth = s;

    std::vector<MIDICommand> *commands = s->getCommands();
    std::map<std::string, MIDICommand*> midi;

    for(size_t i=0; i<commands->size(); i++)
    {
        MIDICommand *m = &commands->at(i);
        for(auto a : m->getAliases())
        {
            std::pair<std::string, MIDICommand*> p(a,m);
            midi.insert(p);
        }
    }

    return midi;
}
