#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>

class Parameter
{
public:
    Parameter() {}
    Parameter(const Parameter &p){
        this->key = p.key;
        this->name = p.name;
        this->size = p.size;
    }

    Parameter(std::string key, std::string name, double size);

    long characters();
    std::string midi(long value);
    std::string getName();
    std::string getKey();
    double getSize();

private:
    std::string key;
    double size;
    std::string name;
};

#endif // PARAMETER_H
