#include "gmock/gmock.h"

#include "PatronAccess.h"
#include "Patron.h"
#include "PatronNotFoundException.h"

#include <vector>

using std::vector;
using namespace testing;

class PatronAccessTest : public Test {
public:
    PatronAccess access;

    virtual void SetUp() {
        PatronAccess::deleteAll();
    }

    virtual void TearDown() {
        PatronAccess::deleteAll();
    }
};

TEST_F(PatronAccessTest, SizeIsZeroWithNoPatrons) {
    ASSERT_THAT(access.size(), Eq(0));
}

TEST_F(PatronAccessTest, IncrementsSizeOnAdd) {
    Patron patron1("patron1");
    access.save(patron1);

    ASSERT_THAT(access.size(), Eq(1));
}

TEST_F(PatronAccessTest, FindAnswersFalseForNonexistentPatron) {
    Patron patron("nobody");
    ASSERT_THAT(access.find(patron), Eq(false));
}

TEST_F(PatronAccessTest, FindAnswerTrueForSavedPatron) {
    Patron patron1("patron1");
    access.save(patron1);

    Patron retrieved("patron1");
    ASSERT_THAT(access.find(retrieved), Eq(true));
}

TEST_F(PatronAccessTest, SaveIsPersistentAcrossAccessInstances) {
    Patron patron1("patron1");
    access.save(patron1);

    PatronAccess newAccess;
    Patron retrieved("patron1");
    ASSERT_THAT(newAccess.find(retrieved), Eq(true));
}

TEST_F(PatronAccessTest, SavePersistsAllAttributes) {
    std::shared_ptr<Patron> patron(new Patron("patron1"));
    access.save(*patron);

    PatronAccess newAccess;
    Patron& retrieved = newAccess.findByName("patron1");

    ASSERT_THAT(retrieved.name(), StrEq(patron->name()));
    ASSERT_THAT(retrieved.fineBalance(), Eq(patron->fineBalance()));
}

TEST_F(PatronAccessTest, FindByNameThrowsWhenNoNameMatches) {
    EXPECT_THROW(access.findByName("nobody"), PatronNotFoundException);
}

TEST_F(PatronAccessTest, FindByNameReturnsChronologicallyFirstMatch) {
    Patron match1("Langr", "p1");
    access.save(match1);
    Patron mismatch("Long", "p2");
    access.save(mismatch);
    Patron match2("Langr", "p3");
    access.save(match2);

    Patron found = access.findByName("Langr");

    ASSERT_THAT(found.cardNumber(), Eq("p1"));
}

TEST_F(PatronAccessTest, UpdatePersistsChanges) {
    auto cardNumber{"p10"};
    Patron patron1("x", cardNumber);
    access.save(patron1);
    int fine = 100;
    patron1.addFine(fine);

    access.update(patron1);

    Patron retrieved("", cardNumber);
    access.find(retrieved);
    ASSERT_THAT(retrieved.fineBalance(), Eq(fine));
}

TEST_F(PatronAccessTest, GetAllAnswersAllSavedPatrons) {
    Patron patron1("a", "p10");
    Patron patron2("b", "p20");
    access.save(patron1);
    access.save(patron2);

    vector<Patron> expected{ patron1, patron2 };

    ASSERT_THAT(access.getAll(), ContainerEq(expected));
}
