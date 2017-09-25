#include "Branch.h"
#include "StreamLineReader.h"

#include <string>
#include <istream>
#include <ostream>
#include <sstream>

using namespace std;

Branch Branch::CHECKED_OUT("99", "-checked out-");

Branch::Branch()
    : mId("")
    , mName("")
{
}

Branch::Branch(const std::string& id, const std::string& name)
    : mId(id)
    , mName(name)
{
}

Branch::~Branch()
{
}

Branch* Branch::clone() const
{
    Branch* branch = new Branch(mId, mName);
    branch->setAddress(mAddress);
    return branch;
}

void Branch::load(istream& input)
{
    StreamLineReader reader(&input);
    reader.read(mId);
    reader.read(mName);
    reader.read(mAddress);
}

void Branch::writeOn(ostream& output)
{
    output
        << mId << endl
        << mName << endl
        << mAddress << endl;
}

std::string Branch::id() const
{
    return mId;
}

std::string Branch::name() const
{
    return mName;
}

std::string Branch::address() const
{
    return mAddress;
}

void Branch::setAddress(const std::string& address)
{
    mAddress = address;
}

bool Branch::operator==(const Branch& other) const
{
    return mId == other.mId;
}

bool Branch::operator!=(const Branch& other) const
{
    return !(*this == other);
}
