#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <vector>
#include <string>
#include <unordered_map>
#include <regex>
#include "utils.h"

class Command {
public:
    Command(){}
    Command(std::string name): name(name) {}

    void addParameter(std::string k, std::string v);
    std::string getParameter(std::string key);
    std::string getParameter(size_t index);
    bool hasParameter(std::string p);
    bool hasNumberedParameter(std::string p, size_t index);
    std::string getNumberedParameter(std::string p, size_t index);
    std::string getName();
    void setName(std::string name);
    std::map<std::string, std::string> getParameters();

private:
    std::string name;
    std::map<std::string, std::string> parameters;
    std::vector<std::string> values;
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

    static std::regex r_params;
    static std::regex r_comm;

private:
};

#endif // CONFIGPARSER_H
