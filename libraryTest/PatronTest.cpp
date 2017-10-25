#include "gmock/gmock.h"

#include "Patron.h"
#include "Holding.h"
#include "ClassificationData.h"

#include <string>
#include <sstream>

using namespace std;
using namespace ClassificationData;
using namespace testing;

class PatronTest : public Test
{
public:
    Patron* jane;
    Holding* theTrialHolding;
    Holding* catch22Holding;

    virtual void SetUp()
    {
        jane = new Patron("Jane", "p1");
        theTrialHolding = new Holding(THE_TRIAL_CLASSIFICATION, 1);
        catch22Holding = new Holding(CATCH22_CLASSIFICATION, 1);
    }

    virtual void TearDown()
    {
        delete jane;
        delete theTrialHolding;
        delete catch22Holding;
    }
};

TEST_F(PatronTest, PrintableRepresentation)
{
    Patron joe("Joe", "p1");
    stringstream stream;

    stream << joe;

    ASSERT_THAT(stream.str(), StrEq("Joe (p1)"));
}

TEST_F(PatronTest, CreateDefaultsCardNumber)
{
    Patron john("john");

    ASSERT_THAT(john.cardNumber(), Eq("p0"));
}

TEST_F(PatronTest, AddFineUpdatesFineBalance)
{
    jane->addFine(10);
    ASSERT_THAT(jane->fineBalance(), Eq(10u));
}

TEST_F(PatronTest, AddFineAccumulatesIntoBalance)
{
    jane->addFine(10);
    jane->addFine(30);

    ASSERT_THAT(jane->fineBalance(), Eq(40u));
}

TEST_F(PatronTest, RemitFineSubtractsFromBalance)
{
    jane->addFine(40);

    jane->remit(15);

    ASSERT_THAT(jane->fineBalance(), Eq(25u));
}

TEST_F(PatronTest, HoldingsContainsBorrowedBooks)
{
    jane->borrow(*theTrialHolding);
    jane->borrow(*catch22Holding);

    ASSERT_THAT(jane->holdings(), Eq(set<Holding>{ *theTrialHolding, *catch22Holding }));
}

TEST_F(PatronTest, HoldingsDoesNotContainReturnedBooks)
{
    jane->borrow(*theTrialHolding);
    jane->borrow(*catch22Holding);

    jane->returnHolding(*theTrialHolding);

    ASSERT_THAT(jane->holdings(), Eq(set<Holding>{ *catch22Holding }));
}

TEST_F(PatronTest, Equality)
{
    Patron patron1("a", "p1");
    Patron patron1copy("a", "p1");

    ASSERT_THAT(patron1 == patron1copy, Eq(true));
}
