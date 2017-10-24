#ifndef PATRON_SERVICE_H
#define PATRON_SERVICE_H

#include "PatronAccess.h"
#include "CreditVerifier.h"

#include <vector>

class Patron;

class PatronService {
public:
    PatronService();
    virtual ~PatronService(void);

    void add(const std::string& name, const std::string& cardNumber, const std::string& creditCardNumber);
    void add(const Patron&);
    bool find(Patron&) const;
    Patron findByCardNumber(const std::string& cardNumber) const;
    short patronCount() const;
    void update(const Patron&);
    std::vector<Patron> getAll() const; // bad!
    static void deleteAll();
    void setCreditVerifier(CreditVerifier*);

private:
    PatronAccess mPatronAccess;
    CreditVerifier* mCreditVerifier{nullptr};

    bool hasGoodCredit(const Patron&) const;
};

#endif
