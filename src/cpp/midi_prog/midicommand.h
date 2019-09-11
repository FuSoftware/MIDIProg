#ifndef MIDICOMMAND_H
#define MIDICOMMAND_H

#include <string>
#include <map>
#include <vector>

#include "parameter.h"

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

private:
    std::string name;
    std::string midi;
    std::map<std::string, Parameter> parameters;
    std::vector<std::string> aliases;
};

#endif // MIDICOMMAND_H
