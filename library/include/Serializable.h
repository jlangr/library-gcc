#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <string>
#include <iostream>

class Serializable {
public:
    virtual void load(std::istream& input)=0;
    virtual void writeOn(std::ostream& output)=0;
    virtual std::string id() const=0;
    virtual Serializable* clone() const=0;
};

#endif

