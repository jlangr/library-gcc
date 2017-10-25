#include "Catalog.h"
#include "Holding.h"
#include "ClassificationData.h"

#include "gmock/gmock.h"

#include <set>
#include <vector>
#include <iostream>

using namespace std;
using namespace ClassificationData;
using namespace testing;

class CatalogTest : public Test {
public:
    Catalog catalog;
    Holding* theTrialHolding;
    Holding* catch22Holding;
    Holding* catch22HoldingCopy2;

    virtual void SetUp() {
        Catalog::deleteAll();
        theTrialHolding = new Holding(THE_TRIAL_CLASSIFICATION, 1);
        catch22Holding = new Holding(CATCH22_CLASSIFICATION, 1);
        catch22HoldingCopy2 = new Holding(CATCH22_CLASSIFICATION, 2);
    }

    virtual void TearDown() {
        delete theTrialHolding;
        delete catch22Holding;
        delete catch22HoldingCopy2;
        Catalog::deleteAll();
    }
};

TEST_F(CatalogTest, IsEmptyOnCreation) {
    ASSERT_THAT(catalog.size(), Eq(0u));
}

TEST_F(CatalogTest, AddIncrementsCount) {
    catalog.add(*theTrialHolding);

    ASSERT_THAT(catalog.size(), Eq(1u));
}

TEST_F(CatalogTest, ContainsAnswersFalseWhenNotFound) {
    ASSERT_THAT(catalog.contains("123:1"), Eq(false));
}

TEST_F(CatalogTest, AddedHoldingCanBeRetrieved) {
    catalog.add(*theTrialHolding);
    auto barcode = Holding::constructBarcode(
      theTrialHolding->classification(), theTrialHolding->copyNumber());

    ASSERT_THAT(catalog.contains(barcode), Eq(true));
}

TEST_F(CatalogTest, FindByBarCodePopulatesMembers) {
    Branch west("1", "West");
    theTrialHolding->transfer(west);
    catalog.add(*theTrialHolding);

    catalog.findByBarCode(theTrialHolding->barcode());

    ASSERT_THAT(theTrialHolding->currentBranch(), Eq(west));
}

TEST_F(CatalogTest, FindByClassificationAnswersMatchingHoldings) {
    catalog.add(*theTrialHolding);
    catalog.add(*catch22Holding);
    catalog.add(*catch22HoldingCopy2);

    set<Holding> holdings;
    catalog.findByClassification(catch22Holding->classification(), holdings);

    ASSERT_THAT(holdings, Eq(set<Holding>{ *catch22Holding, *catch22HoldingCopy2 }));
}

TEST_F(CatalogTest, UpdatesHolding) {
    catalog.add(*theTrialHolding);
    
    Holding changedHolding{theTrialHolding->classification(), 1};
    changedHolding.updateCondition("Damaged");
    catalog.update(changedHolding);

    Holding holding{catalog.findByBarCode(theTrialHolding->barcode())};
    ASSERT_THAT(holding.condition(), Eq("Damaged"));
}

TEST_F(CatalogTest, ThrowsOnUpdateWhenHoldingNotFound) {
    Holding changedHolding{theTrialHolding->classification(), 1};
    ASSERT_THROW(catalog.update(changedHolding), runtime_error);
}
