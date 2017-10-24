#include "Patron.h"
#include "Holding.h"

#include <string>
#include <vector>
#include <sstream>

using namespace std;

Patron::Patron(const string& name, const string& cardNumber, const string& creditCardNumber)
    : mName(name)
    , mBalance(0) 
    , mCardNumber(cardNumber)
    , mCreditCardNumber(creditCardNumber) {}

string Patron::cardNumber() const {
    return mCardNumber;
}

string Patron::creditCardNumber() const {
    return mCardNumber;
}

std::ostream& operator<<(std::ostream& stream, Patron& patron) {
    return stream << patron.name() << " (" << patron.cardNumber() << ")";
}

string Patron::name() const {
    return mName;
}

int Patron::fineBalance() const {
    return mBalance;
}

void Patron::addFine(int amount) {
    mBalance += amount;
}

void Patron::remit(int amount) {
    mBalance -= amount;
}

set<Holding> Patron::holdings() const {
    return mHoldings;
}

void Patron::borrow(const Holding& holding) {
    mHoldings.insert(holding);
}

void Patron::returnHolding(const Holding& holding) {
    mHoldings.erase(holding);
}

bool Patron::operator==(const Patron& rhs) const {
    return mCardNumber == rhs.mCardNumber;
}

bool Patron::operator!=(const Patron& rhs) const {
    return !(*this == rhs);
}
