#include "BranchAccess.h"
#include "Branch.h"

#include "Persistence.h"
#include "KeyedMemoryPersistence.h"

#include <memory>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>

using namespace std;

BranchAccess::BranchAccess(shared_ptr<Persistence<Branch>> persister)
    : mPersister(persister)
{
}

BranchAccess::BranchAccess()
    : mPersister(new KeyedMemoryPersistence<Branch>(BranchAccess::dataFileName()))
{
}

BranchAccess::~BranchAccess()
{
}

string BranchAccess::dataFileName()
{
    return "BranchAccess.txt";
}

bool matchBranchByName(Serializable& each, const string& name)
{
    return (dynamic_cast<Branch&>(each)).name() == name;
}

bool BranchAccess::existsWithName(const string& name) const
{
    return mPersister->matches(matchBranchByName, name);
}

bool BranchAccess::find(Branch& branch) const
{
    unique_ptr<Branch> retrieved = mPersister->get(branch.id());
    if (retrieved.get() == NULL)
    {
        return false;
    }
    branch = *retrieved;
    return true;
}

int BranchAccess::size() const
{
    return mPersister->size();
}

void BranchAccess::save(const Branch& branch)
{
    mPersister->add(branch);
}

void BranchAccess::deleteAll()
{
    mPersister->clear();
}
