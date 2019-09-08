#include "interpreter.h"
#include <iostream>
#include "utils.h"

Interpreter::Interpreter()
{

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
    std::vector<std::string> tokens = split(command, ' ', true);
}

void Interpreter::load_synth(std::string id)
{
    Synth *s = config.get_synth(id);
    this->synth = s;
}
