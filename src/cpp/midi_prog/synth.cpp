#include "synth.h"
#include "midicommand.h"

Synth::Synth(const Synth &s)
{
    this->name = s.name;
    this->id = s.id;
    this->manufacturer = s.manufacturer;
    this->commands = s.commands;
}

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

std::string Synth::getId()
{
    return this->id;
}
