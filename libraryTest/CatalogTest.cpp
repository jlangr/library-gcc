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

class CatalogTest : public Test
{
public:
    Catalog catalog;
    Holding* theTrialHolding;
    Holding* catch22Holding;
    Holding* catch22HoldingCopy2;

    virtual void SetUp()
    {
        Catalog::deleteAll();
        theTrialHolding = new Holding(THE_TRIAL_CLASSIFICATION, 1);
        catch22Holding = new Holding(CATCH22_CLASSIFICATION, 1);
        catch22HoldingCopy2 = new Holding(CATCH22_CLASSIFICATION, 2);
    }

    virtual void TearDown()
    {
        delete theTrialHolding;
        delete catch22Holding;
        delete catch22HoldingCopy2;
        Catalog::deleteAll();
    }
};

TEST_F(CatalogTest, IsEmptyOnCreation)
{
    ASSERT_THAT(catalog.size(), Eq(0));
}

TEST_F(CatalogTest, AddIncrementsCount)
{
    catalog.add(*theTrialHolding);

    ASSERT_THAT(catalog.size(), Eq(1));
}

TEST_F(CatalogTest, ContainsAnswersFalseWhenNotFound)
{
    ASSERT_THAT(catalog.contains("123:1"), Eq(false));
}

TEST_F(CatalogTest, AddedHoldingCanBeRetrieved)
{
    catalog.add(*theTrialHolding);
    auto barcode{Holding::ConstructBarcode(
      theTrialHolding->Classification(), theTrialHolding->CopyNumber())};

    ASSERT_THAT(catalog.contains(barcode), Eq(true));
}

/*
TEST_F(CatalogTest, FindByBarCodePopulatesMembers)
{
    Branch west("1", "West");
    theTrialHolding->Transfer(west);
    catalog.add(*theTrialHolding);
    Holding holding(THE_TRIAL_CLASSIFICATION, 1);

    catalog.findByBarCode(holding);

    ASSERT_THAT(holding.CurrentBranch(), Eq(west));
}
*/

TEST_F(CatalogTest, FindByClassificationAnswersMatchingHoldings)
{
    catalog.add(*theTrialHolding);
    catalog.add(*catch22Holding);
    catalog.add(*catch22HoldingCopy2);

    set<Holding> holdings;
    catalog.findByClassification(CATCH22_CLASSIFICATION, holdings);

    ASSERT_THAT(holdings, Eq(set<Holding>{ *catch22Holding, *catch22HoldingCopy2 }));
}
