#ifndef BRANCH_H
#define BRANCH_H

#include "Serializable.h"

#include <string>
#include <vector>
#include <ostream>
#include <istream>
#include <iostream>

class Branch : public Serializable {
public:
    Branch();
    Branch(const std::string& id, const std::string& name = "");
    virtual ~Branch();

    static Branch CHECKED_OUT;

    virtual void writeOn(std::ostream& output);
    virtual void load(std::istream& input);
    virtual Branch* clone() const;
    std::string id() const;
    std::string name() const;
    void changeAddress(const std::string&);
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
