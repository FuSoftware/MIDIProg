#ifndef MIDICOMMAND_H
#define MIDICOMMAND_H

#include <string>
#include <unordered_map>
#include <map>
#include <vector>

#include "parameter.h"

using ParameterMap = std::unordered_map<std::string, Parameter>;

class MIDICommand
{
public:
    MIDICommand(std::string name = "");

    std::string generate(std::vector<long> values);
    std::string generate(std::map<std::string, std::string> values);

    std::vector<unsigned char> generateBytes(std::vector<long> values);
    std::vector<unsigned char> generateBytes(std::map<std::string, std::string> values);

    void addParameter(std::string p);
    void addParameter(std::string key, double length, std::string name);
    void addParameter(Parameter p);

    void addAliases(std::string values);
    void addAliases(std::vector<std::string> values);

    void setMidi(std::string midi);

    std::vector<std::string> getAliases();

    std::string getName();
    std::string getMidi();

private:
    std::string name;
    std::string midi;
    std::unordered_map<std::string, Parameter> parameters;
    std::vector<std::string> parameter_names;
    std::vector<std::string> aliases;
};

#endif // MIDICOMMAND_H
