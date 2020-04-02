#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <vector>
#include "config.h"
#include "synth.h"
#include "midicommand.h"
#include "midiinterface.h"

class Interpreter
{
public:
    Interpreter();
    std::map<std::string, MIDICommand *> load_synth(std::string id);

    void run_file(std::string command);
    void run(std::vector<std::string> commands);
    void run(std::string command);
    void interactive();

private:
    MIDIInterface interface;
    Synth *synth = nullptr;
    std::map<std::string, MIDICommand*> sysex;
    std::map<std::string, MIDICommand*> midi;
    Config config;
    int port = 0;
    int channel = -1;
    std::string folder;
    std::string current_folder;
};

#endif // INTERPRETER_H
