#include "PatronAccess.h"
#include "Patron.h"
#include "PatronNotFoundException.h"

#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

vector<Patron>* PatronAccess::mPatrons(NULL);

PatronAccess::PatronAccess()
{
}

PatronAccess::~PatronAccess()
{
}

void PatronAccess::save(const Patron& patron)
{
    PatronAccess::patrons()->push_back(patron);
}

void PatronAccess::update(const Patron& patron)
{
    *locate(patron) = patron;
}

std::vector<Patron>::iterator PatronAccess::locate(const Patron& patron) const
{
    return std::find(PatronAccess::patrons()->begin(),
        PatronAccess::patrons()->end(),
        patron);
}

bool PatronAccess::find(Patron& patron) const
{
    vector<Patron>::iterator it = locate(patron);
    if (it == end())
    {
        return false;
    }
    patron = *it;
    return true;
}

struct PatronAccessFindByName : public binary_function<Patron, std::string, bool>
{
    bool operator ()(Patron& patron, const string& name) const
    {
        return (patron.name() == name);
    }
};

Patron& PatronAccess::findByName(const string& name) const
{
    vector<Patron>::iterator it =
        find_if(begin(), end(), bind2nd(PatronAccessFindByName(), name));
    if (it == end())
    {
        throw PatronNotFoundException();
    }
    return *it;
}

vector<Patron>::iterator PatronAccess::begin() const
{
    return PatronAccess::patrons()->begin();
}

vector<Patron>::iterator PatronAccess::end() const
{
    return PatronAccess::patrons()->end();
}

int PatronAccess::size() const
{
    return PatronAccess::patrons()->size();
}

vector<Patron> PatronAccess::getAll() const
{
    return *patrons();
}

/* static */ vector<Patron>* PatronAccess::patrons()
{
    if (!mPatrons)
    {
        mPatrons = new vector<Patron>();
    }
    return mPatrons;
}

/* static */ void PatronAccess::deleteAll()
{
    if (mPatrons)
    {
        delete mPatrons;
        mPatrons = NULL;
    }
}
