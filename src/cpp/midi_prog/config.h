#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>
#include "parsing/commandparser.h"

#include "synth.h"
#include "midicommand.h"

class Config
{
public:
    Config();

    void run_file(std::string path);
    void run(std::vector<Command> commands);
    void run(Command command);
    Synth* get_synth(std::string id);
    static void report_parameter_number_error(std::string command, size_t number, size_t found);

private:
    std::map<std::string, Synth*> synths;
    std::map<std::string, MIDICommand*> aliases;
    Synth* curr_synth = nullptr;
};

#endif // CONFIG_H
