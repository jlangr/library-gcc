#ifndef PATRON_SERVICE_H
#define PATRON_SERVICE_H

#include "PatronAccess.h"

#include <vector>

class Patron;

class PatronService
{
public:
    PatronService();
    virtual ~PatronService(void);

    void Add(const std::string& name, int id);
    void Add(const Patron& patron);
    bool Find(Patron& patron) const;
    short PatronCount() const;
    void Update(const Patron& patron);
    std::vector<Patron> GetAll() const; // bad!
    static void DeleteAll();

private:
    PatronAccess mPatronAccess;
};

#endif
