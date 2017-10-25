#ifndef PATRON_H
#define PATRON_H

#include <string>
#include <set>
#include <ostream>

#include "Holding.h"

class Patron {
public:
    Patron(const std::string& name="", const std::string& cardNumber="p0");

    std::set<Holding> holdings() const;
    std::string name() const;
    std::string cardNumber() const;
    unsigned int fineBalance() const;
    void addFine(int amount);
    void remit(int amount);
    void borrow(const Holding&);
    void returnHolding(const Holding&);

    bool operator==(const Patron&) const;
    bool operator!=(const Patron&) const;

private:
    std::set<Holding> mHoldings;
    std::string mName;
    std::string mCardNumber;
    int mBalance;
};

std::ostream& operator<<(std::ostream&, Patron&);

#endif
