#include "gmock/gmock.h"

#include "NameNormalizer.h"

using namespace testing;
using namespace std;

TEST(ANameNormalizer, ReturnsAnEmptyStringWhenGivenSame) {
    ASSERT_THAT(NormalizedName{""}.AsString(), StrEq(""));
}

TEST(ANameNormalizer, SimplyReturnsASingleWordName) {
    ASSERT_THAT(NormalizedName{"Plato"}.AsString(), StrEq("Plato"));
}

TEST(ANameNormalizer, SwapsFirstAndLastNames) {
    ASSERT_THAT(NormalizedName{"Haruki Murakami"}.AsString(), StrEq("Murakami, Haruki"));
}

TEST(ANameNormalizer, TrimsWhitespace) {
    ASSERT_THAT(NormalizedName{"  Big Boi   "}.AsString(), StrEq("Boi, Big"));
}

TEST(ANameNormalizer, ReplacesMiddleNameWithInitial) {
    ASSERT_THAT(NormalizedName{"Henry David Thoreau"}.AsString(), StrEq("Thoreau, Henry D."));
}

TEST(ANameNormalizer, DoesNotInitializeOneLetterMiddleName) {
    ASSERT_THAT(NormalizedName{"Harry S Truman"}.AsString(), StrEq("Truman, Harry S"));
}

TEST(ANameNormalizer, InitializesEachOfMultipleMiddleNames) {
    ASSERT_THAT(NormalizedName{"Julia Scarlett Elizabeth Louis-Dreyfus"}.AsString(), StrEq("Louis-Dreyfus, Julia S. E."));
}

TEST(ANameNormalizer, AppendsSuffixesToEnd) {
    ASSERT_THAT(NormalizedName{"Martin Luther King, Jr."}.AsString(), StrEq("King, Martin L., Jr."));
}

TEST(ANameNormalizer, ThrowsWhenNameContainsTwoCommas) {
    ASSERT_THROW(NormalizedName{"Thurston, Howell, III"}, InvalidNameException);
}
