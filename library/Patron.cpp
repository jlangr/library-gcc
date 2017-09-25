#include "Patron.h"
#include "Holding.h"

#include <string>
#include <vector>
#include <sstream>

using namespace std;

Patron::Patron(const string& name, int id)
    : mName(name)
    , mId(id)
    , mBalance(0)
{
}

Patron::Patron(const string& name, const string& cardNumber)
    : mName(name)
    , mBalance(0)
{
    string idPortion = cardNumber.substr(1);
    istringstream(idPortion) >> mId;
}

string Patron::cardNumber() const
{
    ostringstream text;
    text << "p" << mId;
    return text.str();
}

std::ostream& operator<<(std::ostream& stream, Patron& patron)
{
    return stream << patron.name() << " (" << patron.cardNumber() << ")";
}

string Patron::name() const
{
    return mName;
}

int Patron::Id() const
{
    return mId;
}

int Patron::fineBalance() const
{
    return mBalance;
}

void Patron::addFine(int amount)
{
    mBalance += amount;
}

void Patron::remit(int amount)
{
    mBalance -= amount;
}

set<Holding> Patron::holdings() const
{
    return mHoldings;
}

void Patron::borrow(const Holding& holding)
{
    mHoldings.insert(holding);
}

void Patron::returnHolding(const Holding& holding)
{
    mHoldings.erase(holding);
}

bool Patron::operator==(const Patron& rhs) const
{
    return mId == rhs.mId;
}

bool Patron::operator!=(const Patron& rhs) const
{
    return !(*this == rhs);
}
