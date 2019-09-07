#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <vector>
#include <string>
#include <map>

struct Command {
    std::string name;
    std::map<std::string, std::string> parameters;

    bool hasParameter(std::string p)
    {
        std::map<std::string, std::string>::iterator it = this->parameters.find(p);
        return it != this->parameters.end();
    }
};

class CommandParser
{
public:
    CommandParser();

    static std::vector<std::string> get_commands_file(std::string file);
    static std::vector<std::string> get_commands(std::string content);
    static std::vector<Command> parse_commands_file(std::string file);
    static std::vector<Command> parse_commands(std::vector<std::string> content);
    static Command parse_command(std::string content);

private:
};

#endif // CONFIGPARSER_H
