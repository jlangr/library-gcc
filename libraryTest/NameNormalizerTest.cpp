#include "gmock\gmock.h"

#include "NameNormalizer.h"

using namespace testing;
using namespace std;

TEST(ANameNormalizer, DISABLED_ReturnsAnEmptyStringWhenGivenSame)
{
    ASSERT_THAT(NormalizedName{""}.AsString(), Eq(""));
}

TEST(ANameNormalizer, DISABLED_SimplyReturnsASingleWordName)
{
    ASSERT_THAT(NormalizedName{"Plato"}.AsString(), Eq("Plato"));
}

TEST(ANameNormalizer, DISABLED_SwapsFirstAndLastNames)
{
    ASSERT_THAT(NormalizedName{"Haruki Murakami"}.AsString(), Eq("Murakami, Haruki"));
}

TEST(ANameNormalizer, DISABLED_TrimsWhitespace)
{
    ASSERT_THAT(NormalizedName{"  Big Boi   "}.AsString(), Eq("Boi, Big"));
}

TEST(ANameNormalizer, DISABLED_ReplacesMiddleNameWithInitial)
{
    ASSERT_THAT(NormalizedName{"Henry David Thoreau"}.AsString(), Eq("Thoreau, Henry D."));
}

TEST(ANameNormalizer, DISABLED_DoesNotInitializeOneLetterMiddleName)
{
    ASSERT_THAT(NormalizedName{"Harry S Truman"}.AsString(), Eq("Truman, Harry S"));
}

TEST(ANameNormalizer, DISABLED_InitializesEachOfMultipleMiddleNames)
{
    ASSERT_THAT(NormalizedName{"Julia Scarlett Elizabeth Louis-Dreyfus"}.AsString(), Eq("Louis-Dreyfus, Julia S. E."));
}

TEST(ANameNormalizer, DISABLED_AppendsSuffixesToEnd)
{
    ASSERT_THAT(NormalizedName{"Martin Luther King, Jr."}.AsString(), Eq("King, Martin L., Jr."));
}

TEST(ANameNormalizer, DISABLED_ThrowsWhenNameContainsTwoCommas)
{
    ASSERT_THROW(NormalizedName{"Thurston, Howell, III"}, InvalidNameException);
}
