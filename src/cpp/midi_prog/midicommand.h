#ifndef MIDICOMMAND_H
#define MIDICOMMAND_H

#include <string>
#include <map>
#include <vector>

class Parameter;

class MIDICommand
{
public:
    MIDICommand(std::string name = "");

    std::string generate(std::vector<long> values);
    std::string generate(std::map<std::string, std::string> values);

private:
    std::string name;
    std::string midi;
    std::map<std::string, Parameter> parameters;
    std::vector<std::string> aliases;
};

#endif // MIDICOMMAND_H
