#include "PersistenceTest.h"

#include "gmock/gmock.h"

#include <memory>
#include "KeyedMemoryPersistence.h"
#include "TestSerializable.h"

using namespace std;
using namespace testing;

TEST_P(PersistenceTest, IsEmptyOnCreation) {
    ASSERT_THAT(persister->size(), Eq(0u));
}

TEST_P(PersistenceTest, SizeSetToOneOnFirstAdd) {
    persister->add(*objectWithId1);

    ASSERT_THAT(persister->size(), Eq(1u));
}

TEST_P(PersistenceTest, SizeIncrementsWithEachAdd) {
    persister->add(*objectWithId1);
    persister->add(*objectWithId2);

    ASSERT_THAT(persister->size(), Eq(2u));
}

TEST_P(PersistenceTest, ReturnsNullPointerWhenItemNotFound) {
    auto found = persister->get("1");

    TestSerializable* serializable = found.get();

    ASSERT_THAT(serializable, IsNull());
}

TEST_P(PersistenceTest, AddedItemCanBeRetrievedById) {
    persister->add(*objectWithId1);

    ASSERT_THAT(*persister->get("1"), Eq(*objectWithId1));
}

TEST_P(PersistenceTest, GetAnswersNullWhenNoMatchingEntries) {
    ASSERT_THAT(persister->get("1").get(), IsNull());
};

TEST_P(PersistenceTest, RetrievedItemIsNewInstance) {
    persister->add(*objectWithId1);

    ASSERT_THAT(objectWithId1 == persister->get("1").get(), Eq(false));
}

TEST_P(PersistenceTest, CanPersistMultipleObjects) {
    persister->add(*objectWithId1);
    persister->add(*objectWithId2);

    ASSERT_THAT(*(persister->get("1")), Eq(*objectWithId1));
    ASSERT_THAT(*(persister->get("2")), Eq(*objectWithId2));
}

bool NameMatcher(Serializable& each, const string& name) {
    return (dynamic_cast<TestSerializable&>(each)).name() == name;
}

TEST_P(PersistenceTest, MatchesAnswersTrueWithMatchingEntries) {
    persister->add(*objectWithId1);
    persister->add(*objectWithId2);
    string object1Name = objectWithId1->name();

    bool exists = persister->matches(NameMatcher, object1Name);

    ASSERT_THAT(exists, Eq(true));
};

TEST_P(PersistenceTest, MatchesAnswersFalseWhenNoMatchingEntries) {
    bool exists = persister->matches(NameMatcher, "don't match anything");

    ASSERT_THAT(exists, Eq(false));
};

TEST_P(PersistenceTest, FindAllMatching)  {
    TestSerializable coolidge("Calvin", "1");
    TestSerializable langr("Jeff", "2");
    TestSerializable lynne("Jeff", "3");
    persister->add(coolidge);
    persister->add(langr);
    persister->add(lynne);

    vector<Serializable*> matches;
    persister->findAllMatching(NameMatcher, "Jeff", matches);

    ASSERT_THAT(matches.size(), Eq(2u));
};
