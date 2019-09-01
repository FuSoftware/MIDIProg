#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>

enum ConfigCommand {
    SOURCE,
    DEFINE_SYNTH,
    DEFINE_COMMAND,
    SET_MANUFACTURER,
    SET_NAME,
    SET_SYSEX,
    SET_PARAMETER,
    SET_ALIAS,
    UNKNOWN = -1
};

class Synth;
class MIDICommand;

class Config
{
public:
    Config();

    void run_file(std::string path);
    void run(std::string line);
    void load_synth(std::string id);
    static ConfigCommand resolve_command(std::string &command);
    static void report_parameter_number_error(std::string command, size_t number, size_t found);

private:
    std::map<std::string, Synth> synths;
    std::map<std::string, MIDICommand> aliases;
    MIDICommand* curr_commands;
    Synth* curr_synth;
};

#endif // CONFIG_H
