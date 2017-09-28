#include "gmock/gmock.h"

#include "Branch.h"
#include "BranchService.h"

using std::string;
using namespace testing;

class BranchServiceTest: public Test {
public:
    Branch* eastBranch;
    Branch* westBranch;
    BranchService service;

    virtual void SetUp() {
        BranchService::deleteAll();
        eastBranch = new Branch("1", "east");
        westBranch = new Branch("2", "west");
    }

    virtual void TearDown() {
        delete eastBranch;
        delete westBranch;
        BranchService::deleteAll();
    }
};

TEST_F(BranchServiceTest, AddReturnsGeneratedId) {
    string id = service.add("newname", "address");

    ASSERT_THAT(id, Gt("0"));
}

TEST_F(BranchServiceTest, AddGeneratesUniqueId) {
    string id1 = service.add("newname1", "address");
    string id2 = service.add("newname2", "address");

    ASSERT_THAT(id1, Ne(id2));
}

TEST_F(BranchServiceTest, AddThrowsWhenNameNotUnique) {
    service.add("samename", "address1");

    ASSERT_THROW(service.add("samename", "address2"), DuplicateBranchNameException);
}

TEST_F(BranchServiceTest, CountInitiallyZero) {
    ASSERT_THAT(service.branchCount(), Eq(0));
}

TEST_F(BranchServiceTest, DeleteAllRemovesAnyAddedBranches) {
    service.add(*eastBranch);
    service.add(*westBranch);

    BranchService::deleteAll();

    ASSERT_THAT(service.find(*eastBranch), Eq(false));
    ASSERT_THAT(service.find(*westBranch), Eq(false));
}

TEST_F(BranchServiceTest, DeleteAllSetsCountToZero) {
    service.add(*eastBranch);
    service.add(*westBranch);

    BranchService::deleteAll();
    
    ASSERT_THAT(service.branchCount(), Eq(0));
}

TEST_F(BranchServiceTest, FindAnswersFalseForNonexistentBranch) {
    ASSERT_THAT(service.find(*eastBranch), Eq(false));
}

TEST_F(BranchServiceTest, FindAnswersTrueForAddedBranch) {
    service.add(*eastBranch);
    
    ASSERT_THAT(service.find(*eastBranch), Eq(true));
}

TEST_F(BranchServiceTest, FindRetrievesById) {
    service.add(*eastBranch);

    Branch retrieved(eastBranch->id(), "");
    service.find(retrieved);

    ASSERT_THAT(retrieved.name(), StrEq(eastBranch->name()));
}

TEST_F(BranchServiceTest, AddBranchIncrementsCount) {
    service.add(*eastBranch);
    ASSERT_THAT(service.branchCount(), Eq(1));

    service.add(*westBranch);
    ASSERT_THAT(service.branchCount(), Eq(2));
}

TEST_F(BranchServiceTest, PersistsAcrossServiceInstances) {
    service.add(*eastBranch);

    BranchService anotherServiceInstance;
    ASSERT_THAT(anotherServiceInstance.find(*eastBranch), Eq(true));
    ASSERT_THAT(anotherServiceInstance.branchCount(), Eq(1));
}
