#include "PatronService.h"
#include "PatronAccess.h"
#include "Patron.h"

#include <vector>

using namespace std;

PatronService::PatronService() {}

PatronService::~PatronService(void) {}

/* static */ void PatronService::deleteAll() {
    PatronAccess::deleteAll();
}

vector<Patron> PatronService::getAll() const {
    return mPatronAccess.getAll();
}

void PatronService::add(const string& name, const string& cardNumber, const string& creditCardNumber) {
    Patron patron(name, cardNumber);
    add(patron);
}

void PatronService::add(const Patron& patron) {
    if (hasGoodCredit(patron))
        mPatronAccess.save(patron);
}

void PatronService::setCreditVerifier(CreditVerifier* verifier) {
    mCreditVerifier = verifier;
}

bool PatronService::hasGoodCredit(const Patron& patron) const {
    if (mCreditVerifier == nullptr) return true;
    return mCreditVerifier->creditScore(patron.creditCardNumber()) 
        >= CreditVerifier::MinimumForGoodCredit;
}

void PatronService::update(const Patron& patron) {
    mPatronAccess.update(patron);
}

bool PatronService::find(Patron& patron) const {
    return mPatronAccess.find(patron);
}

Patron PatronService::findByCardNumber(const string& cardNumber) const {
    return mPatronAccess.findByCardNumber(cardNumber);
}

short PatronService::patronCount() const {
    return mPatronAccess.size();
}
