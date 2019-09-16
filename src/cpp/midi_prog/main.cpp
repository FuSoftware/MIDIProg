#include <iostream>
#include "parsing/commandparser.h"
#include "interpreter.h"
#include "config.h"
#include "rtmidi/RtMidi.h"
#include <chrono>

void probe()
{

    RtMidiIn  *midiin = nullptr;
    RtMidiOut *midiout = nullptr;
    // RtMidiIn constructor
    try {
        midiin = new RtMidiIn();
    }
    catch ( RtMidiError &error ) {
        error.printMessage();
        exit( EXIT_FAILURE );
    }
    // Check inputs.
    unsigned int nPorts = midiin->getPortCount();
    std::cout << "\nThere are " << nPorts << " MIDI input sources available.\n";
    std::string portName;
    for ( unsigned int i=0; i<nPorts; i++ ) {
        try {
            portName = midiin->getPortName(i);
        }
        catch ( RtMidiError &error ) {
            error.printMessage();
            goto cleanup;
        }
        std::cout << "  Input Port #" << i+1 << ": " << portName << '\n';
    }
    // RtMidiOut constructor
    try {
        midiout = new RtMidiOut();
    }
    catch ( RtMidiError &error ) {
        error.printMessage();
        exit( EXIT_FAILURE );
    }
    // Check outputs.
    nPorts = midiout->getPortCount();
    std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";
    for ( unsigned int i=0; i<nPorts; i++ ) {
        try {
            portName = midiout->getPortName(i);
        }
        catch (RtMidiError &error) {
            error.printMessage();
            goto cleanup;
        }
        std::cout << "  Output Port #" << i+1 << ": " << portName << '\n';
    }
    std::cout << '\n';
    // Clean up
    cleanup:
        delete midiin;
        delete midiout;
}

long test_command_parsing()
{
    auto start_time = std::chrono::high_resolution_clock::now();
    std::vector<Command> commands = CommandParser::parse_commands(CommandParser::get_commands_file("/home/fuguet/Prog/MIDIProg/data/dss-1.cmd"));
    auto end_time = std::chrono::high_resolution_clock::now();

    for(Command s : commands)
    {
        auto p = s.getParameters();
        std::cout << s.getName() << std::endl;
        for(std::map<std::string,std::string>::iterator it = p.begin(); it != p.end(); ++it) {
            std::cout << "    " << it->first << " : " << it->second << std::endl;
        }
    }

    return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
}

void test_command_parsing_n(long n)
{
    long total = 0;
    for(long i=0; i<n; i++)
    {
        total += test_command_parsing();
    }
    std::cout << "Ran " << n << " iterations in " << total / 1000 << " ms (" << total / n << "us/it)" << std::endl;
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
    test_command_parsing_n(500);
    return 0;
}
