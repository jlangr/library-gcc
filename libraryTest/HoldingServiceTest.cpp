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
        HoldingService::DeleteAll();
        PatronService::DeleteAll();
        BranchService::DeleteAll();

        arbitraryDate = new date(2013, Jan, 1);

        branch1 = new Branch("1", "branch1");
        branch2 = new Branch("2", "branch2");
        branchService.Add(*branch1);
        branchService.Add(*branch2);
    }

    virtual void TearDown()
    {
        delete branch1;
        delete branch2;

        HoldingService::DeleteAll();
        PatronService::DeleteAll();
        BranchService::DeleteAll();
    }

    // TODO change to have patron service return object
    Patron FindPatronWithId(string id)
    {
        Patron patron("", id);
        patronService.Find(patron);
        return patron;
    }

    void CheckOut(HoldingBarcode& barcode, Branch* branch, string patronCardNumber = "p1000")
    {
        patronService.Add(Patron{"", patronCardNumber});
        holdingService.AddAtBranch(branch->Id(), barcode.AsString());
        holdingService.CheckOut(patronCardNumber, barcode.AsString(), *arbitraryDate);
    }
};

TEST_F(HoldingServiceTest, SizeInitiallyZero)
{
    ASSERT_THAT(holdingService.InventorySize(), Eq(0));
}

TEST_F(HoldingServiceTest, SizeIncrementedOnAddRegardlessOfBranch)
{
    holdingService.AddAtBranch(branch1->Id(), HoldingBarcode(THE_TRIAL_CLASSIFICATION, 1).AsString());
    ASSERT_THAT(holdingService.InventorySize(), Eq(1));

    holdingService.AddAtBranch(branch2->Id(), HoldingBarcode(THE_TRIAL_CLASSIFICATION, 2).AsString());
    ASSERT_THAT(holdingService.InventorySize(), Eq(2));
}

TEST_F(HoldingServiceTest, DeleteAllSetsSizeToZero)
{
    holdingService.AddAtBranch(branch1->Id(), HoldingBarcode(THE_TRIAL_CLASSIFICATION, 1).AsString());
    holdingService.AddAtBranch(branch2->Id(), HoldingBarcode(THE_TRIAL_CLASSIFICATION, 2).AsString());

    HoldingService::DeleteAll();

    ASSERT_THAT(holdingService.InventorySize(), Eq(0));
}

TEST_F(HoldingServiceTest, AddInitializesBranch)
{
    auto barcode{HoldingBarcode(THE_TRIAL_CLASSIFICATION, 1).AsString()};
    holdingService.AddAtBranch(branch1->Id(), barcode);

    auto holding = holdingService.FindByBarCode(barcode);

    ASSERT_THAT(holding.CurrentBranch(), Eq(*branch1));
}

TEST_F(HoldingServiceTest, RetrievesAddedHolding)
{
    auto barcode{HoldingBarcode(THE_TRIAL_CLASSIFICATION, 1).AsString()};

    holdingService.AddAtBranch(branch1->Id(), barcode);

    auto holding{holdingService.FindByBarCode(barcode)};
    ASSERT_THAT(holding.Barcode(), Eq(barcode));
}

TEST_F(HoldingServiceTest, ExistsReturnsFalseWhenNotFound)
{
    ASSERT_THAT(holdingService.ExistsWithBarcode("xxx:1"), Eq(false));
}

TEST_F(HoldingServiceTest, ExistsReturnsTrueWhenNotFound)
{
    auto barcode{Holding::ConstructBarcode(CATCH22_CLASSIFICATION, 1)};
    holdingService.AddAtBranch(branch1->Id(), barcode);

    auto found{holdingService.ExistsWithBarcode(barcode)};

    ASSERT_THAT(found, Eq(true));
}

TEST_F(HoldingServiceTest, IsAvailableReturnsTrueWhenHoldingAvailable)
{
    auto barcode{Holding::ConstructBarcode(CATCH22_CLASSIFICATION, 1)};
    holdingService.AddAtBranch(branch1->Id(), barcode);

    auto isAvailable{holdingService.IsAvailable(barcode)};

    ASSERT_THAT(isAvailable, Eq(true));
}

TEST_F(HoldingServiceTest, IsAvailableReturnsFalseWhenHoldingCheckedOut)
{
    holdingService.AddAtBranch(branch1->Id(), HoldingBarcode(CATCH22_CLASSIFICATION, 1).AsString());
    HoldingBarcode barcode(THE_TRIAL_CLASSIFICATION, 1);
    CheckOut(barcode, branch1);

    auto isAvailable{holdingService.IsAvailable(barcode.AsString())};

    ASSERT_THAT(isAvailable, Eq(false));
}

TEST_F(HoldingServiceTest, FindByClassificationReturnsEmptyWhenNoMatch)
{
    set<Holding> holdings;

    holdingService.FindByClassification(THE_TRIAL_CLASSIFICATION, holdings);

    ASSERT_THAT(holdings.empty(), Eq(true));
}

TEST_F(HoldingServiceTest, FindByClassificationReturnsMultipleMatches)
{
    holdingService.AddAtBranch(branch1->Id(), HoldingBarcode(THE_TRIAL_CLASSIFICATION, 1).AsString());
    holdingService.AddAtBranch(branch1->Id(), HoldingBarcode(THE_TRIAL_CLASSIFICATION, 2).AsString());
    holdingService.AddAtBranch(branch1->Id(), HoldingBarcode(CATCH22_CLASSIFICATION, 1).AsString());

    set<Holding> holdings;
    holdingService.FindByClassification(THE_TRIAL_CLASSIFICATION, holdings);

    Holding trialCopy1(THE_TRIAL_CLASSIFICATION, 1);
    Holding trialCopy2(THE_TRIAL_CLASSIFICATION, 2);
    ASSERT_THAT(holdings, Eq(set<Holding>{ trialCopy1, trialCopy2 }));
}

TEST_F(HoldingServiceTest, Transfer)
{
    auto barcode{Holding::ConstructBarcode(CATCH22_CLASSIFICATION, 1)};
    holdingService.AddAtBranch(branch1->Id(), barcode);

    holdingService.Transfer(barcode, branch1->Id());

    ASSERT_THAT(holdingService.FindByBarCode(barcode).CurrentBranch(), Eq(*branch1));
}

TEST_F(HoldingServiceTest, CheckedOutHoldingUnavailable)
{
    auto barcode{HoldingBarcode{CATCH22_CLASSIFICATION, 1}.AsString()};
    holdingService.AddAtBranch(branch1->Id(), barcode);
    patronService.Add(Patron{"", "p1001"});

    holdingService.CheckOut("p1001", barcode, *arbitraryDate);

    auto retrieved{holdingService.FindByBarCode(barcode)};
    ASSERT_THAT(retrieved.IsAvailable(), Eq(false));
}

TEST_F(HoldingServiceTest, CheckedOutBooksAddedToPatron)
{
    holdingService.AddAtBranch(branch1->Id(), HoldingBarcode(CATCH22_CLASSIFICATION, 1).AsString());
    auto barcode{HoldingBarcode(CATCH22_CLASSIFICATION, 1).AsString()};
    patronService.Add(Patron{"", "p1001"});

    holdingService.CheckOut("p1001", HoldingBarcode(CATCH22_CLASSIFICATION, 1).AsString(), *arbitraryDate);

    Holding holding(HoldingBarcode(CATCH22_CLASSIFICATION, 1).AsString());
    ASSERT_THAT(FindPatronWithId("p1001").Holdings(),
        Eq(set<Holding>{holding}));
}

TEST_F(HoldingServiceTest, CheckInUpdatesHoldingBranch)
{
    HoldingBarcode barcode(THE_TRIAL_CLASSIFICATION, 1);
    CheckOut(barcode, branch1);

    holdingService.CheckIn(barcode.AsString(), *arbitraryDate + date_duration(1), branch2->Id());

    ASSERT_THAT(holdingService.FindByBarCode(barcode.AsString()).CurrentBranch(), Eq(*branch2));
}

TEST_F(HoldingServiceTest, CheckInUpdatesPatronHoldings)
{
    HoldingBarcode barcode(THE_TRIAL_CLASSIFICATION, 1);
    string patronId("5");
    CheckOut(barcode, branch1, patronId);

    holdingService.CheckIn(barcode.AsString(), *arbitraryDate + date_duration(1), branch2->Id());

    ASSERT_THAT(FindPatronWithId(patronId).Holdings().size(), Eq(0));
}

TEST_F(HoldingServiceTest, CheckInEarlyDoesNotUpdatePatronFineBalance)
{
    HoldingBarcode barcode(THE_TRIAL_CLASSIFICATION, 1);
    string patronCardNumber("p5");
    CheckOut(barcode, branch1, patronCardNumber);

    holdingService.CheckIn(barcode.AsString(), *arbitraryDate + date_duration(1), branch2->Id());

    ASSERT_THAT(FindPatronWithId(patronCardNumber).FineBalance(), Eq(0));
}

TEST_F(HoldingServiceTest, CheckInLateUpdatesPatronFineBalance)
{
    HoldingBarcode barcode(THE_TRIAL_CLASSIFICATION, 1);
    string patronCardNumber("p5");
    CheckOut(barcode, branch1, patronCardNumber);
    date_duration oneDayLate(Book::BOOK_CHECKOUT_PERIOD + 1);

    holdingService.CheckIn(barcode.AsString(), *arbitraryDate + oneDayLate, branch2->Id());

    ASSERT_THAT(FindPatronWithId(patronCardNumber).FineBalance(), Eq(Book::BOOK_DAILY_FINE));
}
