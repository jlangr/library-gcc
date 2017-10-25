#include "PatronService.h"
#include "Patron.h"
#include "Holding.h"
#include "ClassificationData.h"

#include "gmock/gmock.h"

using namespace ClassificationData;
using namespace testing;
using namespace std;

class PatronServiceTest : public Test {
public:
    static const string CARD_NUMBER;
    PatronService service;
    Patron* joe;
    Patron* jane;

    virtual void SetUp() {
        PatronService::deleteAll();
        joe = new Patron("Joe", "p1");
        jane = new Patron("Jane", "p2");
    }

    virtual void TearDown() {
        delete jane;
        delete joe;
        PatronService::deleteAll();
    }
};

TEST_F(PatronServiceTest, CountInitiallyZero) {
    ASSERT_THAT(service.patronCount(), Eq(0));
}

TEST_F(PatronServiceTest, AddUsingAttributes) {
    service.add("Suresh", "p20");

    Patron retrieved("", "p20");
    service.find(retrieved);
    ASSERT_THAT(retrieved.name(), StrEq("Suresh"));
}

TEST_F(PatronServiceTest, AddIncrementsCount) {
    service.add(*joe);
    ASSERT_THAT(service.patronCount(), Eq(1));

    service.add(*jane);
    ASSERT_THAT(service.patronCount(), Eq(2));
}

TEST_F(PatronServiceTest, DeleteAllSetsCountToZero) {
    service.add(*joe);
    service.add(*jane);

    PatronService::deleteAll();

    ASSERT_THAT(service.patronCount(), Eq(0));
}

TEST_F(PatronServiceTest, DeleteAllRemovesAnyAddedPatrons) {
    service.add(*joe);
    service.add(*jane);

    PatronService::deleteAll();

    ASSERT_THAT(service.patronCount(), Eq(0));
}

TEST_F(PatronServiceTest, FindAnswerFalseForNonexistentPatron) {
    ASSERT_THAT(service.find(*joe), Eq(false));
}

TEST_F(PatronServiceTest, FindAnswersTrueForAddedPatron) {
    service.add(*joe);

    bool found = service.find(*joe);

    ASSERT_THAT(found, Eq(true));
}

TEST_F(PatronServiceTest, FindRetrieves) {
    service.add(*joe);
    Patron retrieved("dummy name", joe->cardNumber());

    service.find(retrieved);

    ASSERT_THAT(retrieved.name(), StrEq(joe->name()));
}

TEST_F(PatronServiceTest, RetrievesPatronByCardNumber) {
    service.add(*joe);

    Patron retrieved = service.findByCardNumber(joe->cardNumber());

    ASSERT_THAT(retrieved.name(), StrEq(joe->name()));
}

TEST_F(PatronServiceTest, MembersFullyPopulatedInFoundPatron) {
    joe->addFine(20);
    Holding theTrial(THE_TRIAL_CLASSIFICATION, 1);
    joe->borrow(theTrial);
    service.add(*joe);
    Patron retrieved("", joe->cardNumber());

    service.find(retrieved);

    ASSERT_THAT(retrieved.fineBalance(), Eq(20u));
    ASSERT_THAT(retrieved.holdings(), Eq(set<Holding>{ theTrial }));
}
