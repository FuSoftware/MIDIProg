#include "midicommand.h"
#include "utils.h"
#include <algorithm>
#include <iostream>

MIDICommand::MIDICommand(std::string name) : name(name)
{

}

std::string MIDICommand::generate(std::vector<long> values)
{
    if(values.size() != this->parameters.size())
    {
        std::cout << "Command " << this->name << " expected " << this->parameters.size() << " parameters, got " <<values.size() << std::endl;
        return "";
    }
    else
    {
        std::map<std::string, std::string> val;
        std::vector<std::string> keys = this->parameter_names;

        for(size_t i=0;i<values.size();i++)
        {
            val[keys[i]] = this->parameters[keys[i]].midi(values[i]);
        }

        return this->generate(val);
    }
}

std::string MIDICommand::generate(std::map<std::string, std::string> values)
{
    std::string midi = this->midi;
    for(std::map<std::string,std::string>::iterator it = values.begin(); it != values.end(); ++it) {
        findAndReplaceAll(midi, it->first, it->second);
    }
    return midi;
}

std::vector<unsigned char> MIDICommand::generateBytes(std::vector<long> values)
{
    return stob(this->generate(values));
}

std::vector<unsigned char> MIDICommand::generateBytes(std::map<std::string, std::string> values)
{
    return stob(this->generate(values));
}

void MIDICommand::addParameter(std::string p)
{
    std::vector<std::string> tokens = split(p, ':', true);
    this->addParameter(tokens[0], std::stod(tokens[1]) , tokens[2]);
}

void MIDICommand::addParameter(std::string key, double length, std::string name)
{
    this->addParameter(Parameter(key, name, length));
}

void MIDICommand::addParameter(Parameter p)
{
    std::string k = p.getKey();
    std::pair<std::string, Parameter> data(k, p);
    this->parameters.insert(data);
    this->parameter_names.push_back(k);
}

void MIDICommand::addAliases(std::string values)
{
    std::vector<std::string> aliases = split(values, ' ', true);
    this->addAliases(aliases);
}

void MIDICommand::addAliases(std::vector<std::string> values)
{
    for(auto a : values)
    {
        this->aliases.push_back(a);
    }
}


void MIDICommand::setMidi(std::string midi)
{
    this->midi = midi;
}

std::vector<std::string> MIDICommand::getAliases()
{
    return this->aliases;
}
