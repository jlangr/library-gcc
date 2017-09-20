#include "gmock\gmock.h"

#include <string>

using namespace testing;
using namespace std;

string convert(int n)
{
    stringstream s;
    vector<pair<int, string>> conversions{
        make_pair(10, "X"),
        make_pair(5, "V"),
        make_pair(1, "I")
    };
    for (const auto& arabicToRoman : conversions) {
        int arabic = arabicToRoman.first;
        string roman = arabicToRoman.second;
        while (n >= arabic) {
            s << roman;
            n -= arabic;
        }
    }
    return s.str();
}

TEST(ScratchRoman, Convert)
{
    ASSERT_THAT(convert(1), Eq("I"));
    ASSERT_THAT(convert(2), Eq("II"));
    ASSERT_THAT(convert(3), Eq("III"));
    ASSERT_THAT(convert(5), Eq("V"));
    ASSERT_THAT(convert(10), Eq("X"));
    ASSERT_THAT(convert(11), Eq("XI"));
    ASSERT_THAT(convert(31), Eq("XXXI"));
}