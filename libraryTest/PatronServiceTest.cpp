#include "PatronService.h"
#include "Patron.h"
#include "Holding.h"
#include "ClassificationData.h"

#include "gmock/gmock.h"

using namespace ClassificationData;
using namespace testing;
using namespace std;

class PatronServiceTest : public Test
{
public:
    static const string CARD_NUMBER;
    PatronService service;
    Patron* joe;
    Patron* jane;

    virtual void SetUp()
    {
        PatronService::deleteAll();
        joe = new Patron("Joe", 1);
        jane = new Patron("Jane", 2);
    }

    virtual void TearDown()
    {
        delete jane;
        delete joe;
        PatronService::deleteAll();
    }
};

TEST_F(PatronServiceTest, CountInitiallyZero)
{
    ASSERT_THAT(service.patronCount(), Eq(0));
}

TEST_F(PatronServiceTest, AddUsingAttributes)
{
    service.add("Suresh", 20);

    Patron retrieved("", 20);
    service.find(retrieved);
    ASSERT_THAT(retrieved.Name(), Eq("Suresh"));
}

TEST_F(PatronServiceTest, AddIncrementsCount)
{
    service.add(*joe);
    ASSERT_THAT(service.patronCount(), Eq(1));

    service.add(*jane);
    ASSERT_THAT(service.patronCount(), Eq(2));
}

TEST_F(PatronServiceTest, DeleteAllSetsCountToZero)
{
    service.add(*joe);
    service.add(*jane);

    PatronService::deleteAll();

    ASSERT_THAT(service.patronCount(), Eq(0));
}

TEST_F(PatronServiceTest, DeleteAllRemovesAnyAddedPatrons)
{
    service.add(*joe);
    service.add(*jane);

    PatronService::deleteAll();

    ASSERT_THAT(service.patronCount(), Eq(0));
}

TEST_F(PatronServiceTest, FindAnswerFalseForNonexistentPatron)
{
    ASSERT_THAT(service.find(*joe), Eq(false));
}

TEST_F(PatronServiceTest, FindAnswersTrueForAddedPatron)
{
    service.add(*joe);

    bool found = service.find(*joe);

    ASSERT_THAT(found, Eq(true));
}

TEST_F(PatronServiceTest, FindRetrieves)
{
    service.add(*joe);
    Patron retrieved("dummy name", joe->Id());

    service.find(retrieved);

    ASSERT_THAT(retrieved.Name(), Eq(joe->Name()));
}

TEST_F(PatronServiceTest, MembersFullyPopulatedInFoundPatron)
{
    joe->AddFine(20);
    Holding theTrial(THE_TRIAL_CLASSIFICATION, 1);
    joe->Borrow(theTrial);
    service.add(*joe);
    Patron retrieved("", joe->Id());

    service.find(retrieved);

    ASSERT_THAT(retrieved.FineBalance(), Eq(20));
    ASSERT_THAT(retrieved.Holdings(), Eq(set<Holding>{ theTrial }));
}
