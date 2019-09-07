#include <iostream>
#include "parsing/commandparser.h"

int main()
{
    std::vector<Command> commands = CommandParser::parse_commands(CommandParser::get_commands_file("D:\\Prog\\MIDIProg\\data\\dss-1.cmd"));

    for(Command s : commands)
    {
        std::cout << s.name << std::endl;
        for(std::map<std::string,std::string>::iterator it = s.parameters.begin(); it != s.parameters.end(); ++it) {
            std::cout << "    " << it->first << " : " << it->second << std::endl;
        }
    }

    return 0;
}
