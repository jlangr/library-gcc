#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "BranchAccess.h"
#include "Branch.h"

#include <cstdio>

#include "Persistence.h"

using namespace std;
using namespace testing;

class BranchAccessTest : public Test
{
public:
    BranchAccess access;
    BranchAccess access2;
    BranchAccess* branchAccess;

    std::shared_ptr<Persistence<Branch>> persister;

    vector<Branch> noBranches;
    Branch* eastBranch;

    virtual void SetUp()
    {
        branchAccess = new BranchAccess();
        branchAccess->deleteAll();

        eastBranch = new Branch("1", "east");

        access.deleteAll();
    }

    virtual void TearDown()
    {
        branchAccess->deleteAll();
        delete branchAccess;
        delete eastBranch;

        access.deleteAll();
    }
};

TEST_F(BranchAccessTest, SizeInitiallyZero)
{
    ASSERT_THAT(branchAccess->size(), Eq(0));
}

TEST_F(BranchAccessTest, SaveIncrementsSize)
{
    branchAccess->save(*eastBranch);

    ASSERT_THAT(branchAccess->size(), Eq(1));
}

TEST_F(BranchAccessTest, PersistsBranch)
{
    Branch branch("55", "WEST");
    branch.setAddress("address");
    access.save(branch);
    Branch retrieve("55");

    access2.find(retrieve);

    ASSERT_THAT(retrieve.address(), StrEq("address"));
}

TEST_F(BranchAccessTest, FindAnswersFalseForNonexistentBranch)
{
    Branch east("66");

    ASSERT_THAT(access.find(east), Eq(false));
}

TEST_F(BranchAccessTest, MultipleItemsPersistedCorrectly)
{
    access.save(Branch{"66", "EAST"});
    access.save(Branch{"77", "NORTH"});
    Branch east{"66"};
    Branch north{"77"};

    access2.find(east);
    access2.find(north);

    ASSERT_THAT(east.name(), StrEq("EAST"));
    ASSERT_THAT(north.name(), StrEq("NORTH"));
}
