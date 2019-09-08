#include "parameter.h"
#include <cmath>
#include <iomanip>
#include <sstream>

Parameter::Parameter(std::string key, std::string name, double size) : key(key), size(size), name(name)
{

}


long Parameter::characters()
{
    return static_cast<long>(round(this->size * 2.0));
}

std::string Parameter::midi(long value)
{
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(this->characters()) << std::hex << value;
    return stream.str();
}

std::string Parameter::getName()
{
    return this->name;
}

std::string Parameter::getKey()
{
    return this->key;
}

double Parameter::getSize()
{
    return this->size;
}

