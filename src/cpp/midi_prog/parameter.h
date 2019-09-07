#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>

class Parameter
{
public:
    Parameter() {}
    Parameter(std::string name, double size);

    long characters();
    std::string midi(long value);

private:
    double size;
    std::string name;
};

#endif // PARAMETER_H
