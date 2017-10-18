#ifndef PATRON_SERVICE_H
#define PATRON_SERVICE_H

#include "PatronAccess.h"

#include <vector>

class Patron;

class PatronService {
public:
    PatronService();
    virtual ~PatronService(void);

    void add(const std::string& name, const std::string& cardNumber);
    void add(const Patron&);
    bool find(Patron&) const;
    Patron findByCardNumber(const std::string& cardNumber) const;
    short patronCount() const;
    void update(const Patron&);
    std::vector<Patron> getAll() const; // bad!
    static void deleteAll();

private:
    PatronAccess mPatronAccess;
};

#endif
