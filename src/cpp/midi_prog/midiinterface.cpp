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
