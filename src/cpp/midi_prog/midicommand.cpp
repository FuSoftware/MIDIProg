#include "midicommand.h"

//#include <algorithm>
#include "parameter.h"

MIDICommand::MIDICommand(std::string name) : name(name)
{

}

std::string MIDICommand::generate(std::vector<long> values)
{
    if(values.size() != this->parameters.size())
    {
        return "";
    }
    else
    {
        std::map<std::string, std::string> val;
        std::vector<std::string> keys;

        for(std::map<std::string,Parameter>::iterator it = this->parameters.begin(); it != this->parameters.end(); ++it) {
            keys.push_back(it->first);
        }

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
    //for(std::map<std::string,std::string>::iterator it = values.begin(); it != values.end(); ++it) {
    //    std::replace(midi.begin(), midi.end(), it->first,values[it->second]);
    //}
    return midi;
}
