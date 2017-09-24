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

short BranchService::branchCount() const
{
    return mBranchAccess.size();
}

void BranchService::add(Branch& branch)
{
    mBranchAccess.save(branch);
}

string BranchService::add(const string& name, const string& address)
{
    if (existsWithName(name))
        throw DuplicateBranchNameException();

    stringstream out;
    out << mBranchAccess.size() + 1;
    string id(out.str());

    Branch branch(id, name);
    branch.setAddress(address);
    mBranchAccess.save(branch);
    return id;
}

bool BranchService::find(Branch& branch) const
{
    return mBranchAccess.find(branch);
}

bool BranchService::existsWithName(const string& name) const
{
    return mBranchAccess.existsWithName(name);
}

/* static */ void BranchService::deleteAll()
{
    BranchAccess access;
    access.deleteAll();
}
