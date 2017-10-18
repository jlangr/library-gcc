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

void PatronService::add(const string& name, const string& cardNumber) {
    Patron patron(name, cardNumber);
    add(patron);
}

void PatronService::add(const Patron& patron) {
    mPatronAccess.save(patron);
}

void PatronService::update(const Patron& patron) {
    mPatronAccess.update(patron);
}

bool PatronService::find(Patron& patron) const {
    return mPatronAccess.find(patron);
}

short PatronService::patronCount() const {
    return mPatronAccess.size();
}
