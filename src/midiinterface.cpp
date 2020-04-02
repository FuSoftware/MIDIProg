#include "midiinterface.h"
#include <thread>
#include <chrono>


MIDIInterface::MIDIInterface()
{
    this->in.ignoreTypes( false, false, false );
}

void MIDIInterface::setPort(unsigned int port)
{
    this->out.closePort();
    this->out.openPort(port);

    this->in.closePort();
    this->in.openPort(port);
}

void MIDIInterface::listPorts()
{
    unsigned int nPorts = this->in.getPortCount();
    std::cout << "\nThere are " << nPorts << " MIDI input sources available.\n";
    std::string portName;
    for ( unsigned int i=0; i<nPorts; i++ ) {
        portName = this->in.getPortName(i);
        std::cout << "  Input Port #" << i+1 << ": " << portName << '\n';
    }

    // Check outputs.
    nPorts = this->out.getPortCount();
    std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";
    for ( unsigned int i=0; i<nPorts; i++ ) {
        portName = this->out.getPortName(i);
        std::cout << "  Output Port #" << i+1 << ": " << portName << '\n';
    }
    std::cout << '\n';
}

void MIDIInterface::send(std::vector<unsigned char> data)
{
    this->out.sendMessage(&data);
}

void MIDIInterface::waitMidi()
{
    std::vector<unsigned char> message;
    size_t nBytes, i;
    double stamp;
    bool received = false;
    while ( true ) {
        stamp = this->in.getMessage(&message);
        nBytes = message.size();
        for ( i=0; i<nBytes; i++ )
        {
          std::cout << std::hex << static_cast<int>(message[i]) << " " << std::dec;
        }

        if ( nBytes > 0 )
        {
            received = true;
            std::cout << " | Stamp = " << stamp << std::endl;
        }
        else if (nBytes == 0 && received)
        {
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
}
