#ifndef PATRON_H
#define PATRON_H

#include <string>
#include <set>
#include <ostream>

#include "Holding.h"
#include "CreditVerifier.h"

class Patron {
public:
    Patron(const std::string& name="", const std::string& cardNumber="p0", const std::string& creditCardNumber="");

    std::set<Holding> holdings() const;
    std::string name() const;
    std::string cardNumber() const;
    std::string creditCardNumber() const;
    int fineBalance() const;
    void addFine(int amount);
    void remit(int amount);
    void borrow(const Holding&);
    void returnHolding(const Holding&);
    void setCreditVerifier(CreditVerifier*);

    bool operator==(const Patron&) const;
    bool operator!=(const Patron&) const;

private:
    std::set<Holding> mHoldings;
    std::string mName;
    std::string mCardNumber;
    std::string mCreditCardNumber;
    int mBalance;

    bool hasGoodCredit(const Patron&) const;
    CreditVerifier* mCreditVerifier;
};

std::ostream& operator<<(std::ostream&, Patron&);

#endif
