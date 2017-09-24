#include "BranchService.h"

#include "Branch.h"

#include <string>
#include <sstream>

using namespace std;

BranchService::BranchService(void)
{
}

BranchService::~BranchService(void)
{
}

short BranchService::BranchCount() const
{
    return mBranchAccess.size();
}

void BranchService::Add(Branch& branch)
{
    mBranchAccess.save(branch);
}

string BranchService::Add(const string& name, const string& address)
{
    if (ExistsWithName(name))
        throw DuplicateBranchNameException();

    stringstream out;
    out << mBranchAccess.size() + 1;
    string id(out.str());

    Branch branch(id, name);
    branch.setAddress(address);
    mBranchAccess.save(branch);
    return id;
}

bool BranchService::Find(Branch& branch) const
{
    return mBranchAccess.find(branch);
}

bool BranchService::ExistsWithName(const string& name) const
{
    return mBranchAccess.existsWithName(name);
}

/* static */ void BranchService::DeleteAll()
{
    BranchAccess access;
    access.deleteAll();
}
