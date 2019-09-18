#ifndef SYNTH_H
#define SYNTH_H

#include <string>
#include <vector>

class MIDICommand;

class Synth
{
public:
    Synth(const Synth &s);
    Synth(std::string id = "");

    void setName(std::string name);
    void setManufacturer(std::string manufacturer);
    std::vector<MIDICommand> *getCommands();

    std::string getId();
    std::string getName();
    std::string getManufacturer();

private:
    std::string name;
    std::string id;
    std::string manufacturer;
    std::vector<MIDICommand> commands;
};

#endif // SYNTH_H
