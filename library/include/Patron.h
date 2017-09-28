#ifndef PATRON_H
#define PATRON_H

#include <string>
#include <set>
#include <ostream>

#include "Holding.h"

class Patron {
public:
    Patron(const std::string& name = "", int id = 0);
    Patron(const std::string& name, const std::string& cardNumber);

    std::set<Holding> holdings() const;
    std::string name() const;
    int id() const;
    std::string cardNumber() const;
    int fineBalance() const;
    void addFine(int amount);
    void remit(int amount);
    void borrow(const Holding&);
    void returnHolding(const Holding&);

    bool operator==(const Patron&) const;
    bool operator!=(const Patron&) const;

private:
    std::set<Holding> mHoldings;
    std::string mName;
    std::string mCreditCardNumber;
    int mId;
    int mBalance;
};

std::ostream& operator<<(std::ostream&, Patron&);

#endif
