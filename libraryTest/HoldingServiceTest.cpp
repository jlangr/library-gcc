#include "gmock/gmock.h"

#include "HoldingService.h"
#include "Branch.h"
#include "BranchService.h"
#include "ClassificationData.h"
#include "Patron.h"
#include "PatronService.h"
#include "HoldingBarcode.h"

#include "boost/date_time/gregorian/gregorian_types.hpp"

using namespace std;
using namespace testing;
using namespace ClassificationData;
using namespace boost::gregorian;
using namespace service;

class HoldingServiceTest : public Test
{
public:
    Branch* branch1;
    Branch* branch2;
    PatronService patronService;
    BranchService branchService;
    HoldingService holdingService;
    date* arbitraryDate;

    virtual void SetUp()
    {
        HoldingService::deleteAll();
        PatronService::deleteAll();
        BranchService::deleteAll();

        arbitraryDate = new date(2013, Jan, 1);

        branch1 = new Branch("1", "branch1");
        branch2 = new Branch("2", "branch2");
        branchService.add(*branch1);
        branchService.add(*branch2);
    }

    virtual void TearDown()
    {
        delete branch1;
        delete branch2;

        HoldingService::deleteAll();
        PatronService::deleteAll();
        BranchService::deleteAll();
    }

    // TODO change to have patron service return object
    Patron FindPatronWithId(string id)
    {
        Patron patron("", id);
        patronService.find(patron);
        return patron;
    }

    void CheckOut(HoldingBarcode& barcode, Branch* branch, string patronCardNumber = "p1000")
    {
        patronService.add(Patron{"", patronCardNumber});
        holdingService.addAtBranch(branch->id(), barcode.asString());
        holdingService.checkOut(patronCardNumber, barcode.asString(), *arbitraryDate);
    }
};

TEST_F(HoldingServiceTest, SizeInitiallyZero)
{
    ASSERT_THAT(holdingService.inventorySize(), Eq(0));
}

TEST_F(HoldingServiceTest, SizeIncrementedOnAddRegardlessOfBranch)
{
    holdingService.addAtBranch(branch1->id(), HoldingBarcode(THE_TRIAL_CLASSIFICATION, 1).asString());
    ASSERT_THAT(holdingService.inventorySize(), Eq(1));

    holdingService.addAtBranch(branch2->id(), HoldingBarcode(THE_TRIAL_CLASSIFICATION, 2).asString());
    ASSERT_THAT(holdingService.inventorySize(), Eq(2));
}

TEST_F(HoldingServiceTest, DeleteAllSetsSizeToZero)
{
    holdingService.addAtBranch(branch1->id(), HoldingBarcode(THE_TRIAL_CLASSIFICATION, 1).asString());
    holdingService.addAtBranch(branch2->id(), HoldingBarcode(THE_TRIAL_CLASSIFICATION, 2).asString());

    HoldingService::deleteAll();

    ASSERT_THAT(holdingService.inventorySize(), Eq(0));
}

TEST_F(HoldingServiceTest, AddInitializesBranch)
{
    auto barcode{HoldingBarcode(THE_TRIAL_CLASSIFICATION, 1).asString()};
    holdingService.addAtBranch(branch1->id(), barcode);

    auto holding = holdingService.findByBarCode(barcode);

    ASSERT_THAT(holding.currentBranch(), Eq(*branch1));
}

TEST_F(HoldingServiceTest, RetrievesAddedHolding)
{
    auto barcode{HoldingBarcode(THE_TRIAL_CLASSIFICATION, 1).asString()};

    holdingService.addAtBranch(branch1->id(), barcode);

    auto holding{holdingService.findByBarCode(barcode)};
    ASSERT_THAT(holding.barcode(), StrEq(barcode));
}

TEST_F(HoldingServiceTest, ExistsReturnsFalseWhenNotFound)
{
    ASSERT_THAT(holdingService.existsWithBarcode("xxx:1"), Eq(false));
}

TEST_F(HoldingServiceTest, ExistsReturnsTrueWhenNotFound)
{
    auto barcode{Holding::constructBarcode(CATCH22_CLASSIFICATION, 1)};
    holdingService.addAtBranch(branch1->id(), barcode);

    auto found{holdingService.existsWithBarcode(barcode)};

    ASSERT_THAT(found, Eq(true));
}

TEST_F(HoldingServiceTest, IsAvailableReturnsTrueWhenHoldingAvailable)
{
    auto barcode{Holding::constructBarcode(CATCH22_CLASSIFICATION, 1)};
    holdingService.addAtBranch(branch1->id(), barcode);

    auto isAvailable{holdingService.isAvailable(barcode)};

    ASSERT_THAT(isAvailable, Eq(true));
}

TEST_F(HoldingServiceTest, IsAvailableReturnsFalseWhenHoldingCheckedOut)
{
    holdingService.addAtBranch(branch1->id(), HoldingBarcode(CATCH22_CLASSIFICATION, 1).asString());
    HoldingBarcode barcode(THE_TRIAL_CLASSIFICATION, 1);
    CheckOut(barcode, branch1);

    auto isAvailable{holdingService.isAvailable(barcode.asString())};

    ASSERT_THAT(isAvailable, Eq(false));
}

TEST_F(HoldingServiceTest, FindByClassificationReturnsEmptyWhenNoMatch)
{
    set<Holding> holdings;

    holdingService.findByClassification(THE_TRIAL_CLASSIFICATION, holdings);

    ASSERT_THAT(holdings.empty(), Eq(true));
}

TEST_F(HoldingServiceTest, FindByClassificationReturnsMultipleMatches)
{
    holdingService.addAtBranch(branch1->id(), HoldingBarcode(THE_TRIAL_CLASSIFICATION, 1).asString());
    holdingService.addAtBranch(branch1->id(), HoldingBarcode(THE_TRIAL_CLASSIFICATION, 2).asString());
    holdingService.addAtBranch(branch1->id(), HoldingBarcode(CATCH22_CLASSIFICATION, 1).asString());

    set<Holding> holdings;
    holdingService.findByClassification(THE_TRIAL_CLASSIFICATION, holdings);

    Holding trialCopy1(THE_TRIAL_CLASSIFICATION, 1);
    Holding trialCopy2(THE_TRIAL_CLASSIFICATION, 2);
    ASSERT_THAT(holdings, Eq(set<Holding>{ trialCopy1, trialCopy2 }));
}

TEST_F(HoldingServiceTest, Transfer)
{
    auto barcode{Holding::constructBarcode(CATCH22_CLASSIFICATION, 1)};
    holdingService.addAtBranch(branch1->id(), barcode);

    holdingService.transfer(barcode, branch1->id());

    ASSERT_THAT(holdingService.findByBarCode(barcode).currentBranch(), Eq(*branch1));
}

TEST_F(HoldingServiceTest, CheckedOutHoldingUnavailable)
{
    auto barcode{HoldingBarcode{CATCH22_CLASSIFICATION, 1}.asString()};
    holdingService.addAtBranch(branch1->id(), barcode);
    patronService.add(Patron{"", "p1001"});

    holdingService.checkOut("p1001", barcode, *arbitraryDate);

    auto retrieved{holdingService.findByBarCode(barcode)};
    ASSERT_THAT(retrieved.isAvailable(), Eq(false));
}

TEST_F(HoldingServiceTest, CheckedOutBooksAddedToPatron)
{
    holdingService.addAtBranch(branch1->id(), HoldingBarcode(CATCH22_CLASSIFICATION, 1).asString());
    auto barcode{HoldingBarcode(CATCH22_CLASSIFICATION, 1).asString()};
    patronService.add(Patron{"", "p1001"});

    holdingService.checkOut("p1001", HoldingBarcode(CATCH22_CLASSIFICATION, 1).asString(), *arbitraryDate);

    Holding holding(HoldingBarcode(CATCH22_CLASSIFICATION, 1).asString());
    ASSERT_THAT(FindPatronWithId("p1001").holdings(),
        Eq(set<Holding>{holding}));
}

TEST_F(HoldingServiceTest, CheckInUpdatesHoldingBranch)
{
    HoldingBarcode barcode(THE_TRIAL_CLASSIFICATION, 1);
    CheckOut(barcode, branch1);

    holdingService.checkIn(barcode.asString(), *arbitraryDate + date_duration(1), branch2->id());

    ASSERT_THAT(holdingService.findByBarCode(barcode.asString()).currentBranch(), Eq(*branch2));
}

TEST_F(HoldingServiceTest, CheckInUpdatesPatronHoldings)
{
    HoldingBarcode barcode(THE_TRIAL_CLASSIFICATION, 1);
    string patronId("5");
    CheckOut(barcode, branch1, patronId);

    holdingService.checkIn(barcode.asString(), *arbitraryDate + date_duration(1), branch2->id());

    ASSERT_THAT(FindPatronWithId(patronId).holdings().size(), Eq(0));
}

TEST_F(HoldingServiceTest, CheckInEarlyDoesNotUpdatePatronFineBalance)
{
    HoldingBarcode barcode(THE_TRIAL_CLASSIFICATION, 1);
    string patronCardNumber("p5");
    CheckOut(barcode, branch1, patronCardNumber);

    holdingService.checkIn(barcode.asString(), *arbitraryDate + date_duration(1), branch2->id());

    ASSERT_THAT(FindPatronWithId(patronCardNumber).fineBalance(), Eq(0));
}

TEST_F(HoldingServiceTest, CheckInLateUpdatesPatronFineBalance)
{
    HoldingBarcode barcode(THE_TRIAL_CLASSIFICATION, 1);
    string patronCardNumber("p5");
    CheckOut(barcode, branch1, patronCardNumber);
    date_duration oneDayLate(Book::BOOK_CHECKOUT_PERIOD + 1);

    holdingService.checkIn(barcode.asString(), *arbitraryDate + oneDayLate, branch2->id());

    ASSERT_THAT(FindPatronWithId(patronCardNumber).fineBalance(), Eq(Book::BOOK_DAILY_FINE));
}
