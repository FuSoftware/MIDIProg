#include <iostream>
#include "parsing/commandparser.h"
#include "interpreter.h"
#include "config.h"

void test_command_parsing()
{
    std::vector<Command> commands = CommandParser::parse_commands(CommandParser::get_commands_file("D:\\Prog\\MIDIProg\\data\\dss-1.cmd"));

    for(Command s : commands)
    {
        auto p = s.getParameters();
        std::cout << s.getName() << std::endl;
        for(std::map<std::string,std::string>::iterator it = p.begin(); it != p.end(); ++it) {
            std::cout << "    " << it->first << " : " << it->second << std::endl;
        }
    }
}

void test_config()
{
    Config c;
    c.run_file("D:\\Prog\\MIDIProg\\data\\config.cmd");
}

void test_interpreter()
{
    Interpreter i;
    i.run_file("/home/fuguet/Prog/MIDIProg/data/run.cmd");
}

int main()
{
    test_interpreter();
    return 0;
}
