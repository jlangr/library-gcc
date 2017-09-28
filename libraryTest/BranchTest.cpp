#include "gmock/gmock.h"

#include "Branch.h"

#include <sstream>
#include <memory>

using namespace std;
using namespace testing;

TEST(BranchTest, CreateInitializesMembers) {
    Branch branch("5", "south");

    ASSERT_THAT(branch.name(), StrEq("south"));
    ASSERT_THAT(branch.id(), StrEq("5"));
}

TEST(BranchTest, CloneCopiesAllMembers) {
    Branch branch("17", "north");
    branch.setAddress("123 B Street");

    unique_ptr<Branch>clone(branch.clone());

    ASSERT_THAT(clone->id(), StrEq(branch.id()));
    ASSERT_THAT(clone->name(), StrEq(branch.name()));
    ASSERT_THAT(clone->address(), StrEq(branch.address()));
}

TEST(BranchTest, CreateDefaultsName) {
    Branch branch("10");

    ASSERT_THAT(branch.name(), StrEq(""));
}

TEST(BranchTest, EqualityAnswersTrueOnIdMatch) {
    Branch branch1("1", "a");
    Branch branch1copy("1", "b");

    ASSERT_THAT(branch1 == branch1copy, Eq(true));
}

TEST(BranchTest, InequalityAnswersFalseOnIdMismatch) {
    Branch branch1("1", "a");
    Branch branch2("2", "a");

    ASSERT_THAT(branch1 != branch2, Eq(true));
}

TEST(BranchTest, CanLoadFromSerialized) {
    Branch branch("20", "xyz");
    branch.setAddress("101 Main St, Laurel, MD");
    unique_ptr<ostringstream> o(new ostringstream(ios::out | ios::binary));
    branch.writeOn(*o);
    unique_ptr<istream> i(new istringstream(o->str(), ios::in | ios::binary));

    Branch loaded;
    loaded.load(*i);

    ASSERT_THAT(loaded.id(), StrEq("20"));
    ASSERT_THAT(loaded.name(), StrEq("xyz"));
    ASSERT_THAT(loaded.address(), StrEq("101 Main St, Laurel, MD"));
}
