#include "PatronService.h"
#include "PatronAccess.h"
#include "Patron.h"

#include <vector>

using namespace std;

PatronService::PatronService() 
{
}

PatronService::~PatronService(void)
{
}

/* static */ void PatronService::DeleteAll()
{
    PatronAccess::deleteAll();
}

vector<Patron> PatronService::GetAll() const
{
    return mPatronAccess.getAll();
}

void PatronService::Add(const string& name, int id)
{
    Patron patron(name, id);
    Add(patron);
}

void PatronService::Add(const Patron& patron)
{
    mPatronAccess.save(patron);
}

void PatronService::Update(const Patron& patron)
{
    mPatronAccess.update(patron);
}

bool PatronService::Find(Patron& patron) const
{
    return mPatronAccess.find(patron);
}

short PatronService::PatronCount() const
{
    return mPatronAccess.size();
}
