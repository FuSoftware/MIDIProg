#include "synth.h"
#include "midicommand.h"

Synth::Synth(std::string id) : id(id)
{

}


void Synth::setName(std::string name)
{
    this->name = name;
}

void Synth::setManufacturer(std::string manufacturer)
{
    this->manufacturer = manufacturer;
}

std::vector<MIDICommand> *Synth::getCommands()
{
    return &this->commands;
}
