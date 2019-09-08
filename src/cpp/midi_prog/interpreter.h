#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <vector>
#include "config.h"
#include "synth.h"

class Interpreter
{
public:
    Interpreter();
    void load_synth(std::string id);

    void run(std::vector<std::string> commands);
    void run(std::string command);

private:
    Synth *synth = nullptr;
    Config config;
};

#endif // INTERPRETER_H
