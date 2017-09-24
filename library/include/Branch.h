#ifndef BRANCH_H
#define BRANCH_H

#include "Serializable.h"

#include <string>
#include <vector>
#include <ostream>
#include <istream>
#include <iostream>

class Branch : public Serializable
{
public:
    Branch();
    Branch(const std::string& id, const std::string& name = "");
    virtual ~Branch();

    static Branch CHECKED_OUT;

    virtual void WriteOn(std::ostream& output);
    virtual void Load(std::istream& input);
    virtual Branch* Clone() const;
    std::string Id() const;
    std::string name() const;
    // TODO: change to 'changeAddress'
    void setAddress(const std::string&);
    std::string address() const;
    bool operator==(const Branch& other) const;
    bool operator!=(const Branch& other) const;

private:
    std::string mId;
    std::string mName;
    std::string mAddress;
};

typedef std::vector<Branch>::iterator BranchIterator;

#endif
