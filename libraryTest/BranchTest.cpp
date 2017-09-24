#include "gmock/gmock.h"

#include "Branch.h"

#include <sstream>
#include <memory>

using namespace std;
using namespace testing;

TEST(BranchTest, CreateInitializesMembers)
{
    Branch branch("5", "south");

    ASSERT_THAT(branch.name(), Eq("south"));
    ASSERT_THAT(branch.Id(), Eq("5"));
}

TEST(BranchTest, CloneCopiesAllMembers)
{
    Branch branch("17", "north");
    branch.setAddress("123 B Street");

    unique_ptr<Branch>clone(branch.Clone());

    ASSERT_THAT(clone->Id(), Eq(branch.Id()));
    ASSERT_THAT(clone->name(), Eq(branch.name()));
    ASSERT_THAT(clone->address(), Eq(branch.address()));
}

TEST(BranchTest, CreateDefaultsName)
{
    Branch branch("10");

    ASSERT_THAT(branch.name(), Eq(""));
}

TEST(BranchTest, EqualityAnswersTrueOnIdMatch)
{
    Branch branch1("1", "a");
    Branch branch1copy("1", "b");

    ASSERT_THAT(branch1 == branch1copy, Eq(true));
}

TEST(BranchTest, InequalityAnswersFalseOnIdMismatch)
{
    Branch branch1("1", "a");
    Branch branch2("2", "a");

    ASSERT_THAT(branch1 != branch2, Eq(true));
}

TEST(BranchTest, CanLoadFromSerialized)
{
    Branch branch("20", "xyz");
    branch.setAddress("101 Main St, Laurel, MD");
    unique_ptr<ostringstream> o(new ostringstream(ios::out | ios::binary));
    branch.WriteOn(*o);
    unique_ptr<istream> i(new istringstream(o->str(), ios::in | ios::binary));

    Branch loaded;
    loaded.Load(*i);

    ASSERT_THAT(loaded.Id(), Eq("20"));
    ASSERT_THAT(loaded.name(), Eq("xyz"));
    ASSERT_THAT(loaded.address(), Eq("101 Main St, Laurel, MD"));
}
