#include <iostream>
#include "parsing/commandparser.h"
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
    c.load_synth("dss-1");
}

int main()
{
    test_config();
    return 0;
}
