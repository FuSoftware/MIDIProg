#ifndef MIDIINTERFACE_H
#define MIDIINTERFACE_H

#include "rtmidi/RtMidi.h"
#include <vector>


class MIDIInterface
{
public:
    MIDIInterface();

    void setPort(unsigned int port);
    void send(std::vector<unsigned char> data);
    void waitMidi();

private:
    RtMidiOut out;
    RtMidiIn in;
};

#endif // MIDIINTERFACE_H
