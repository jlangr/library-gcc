#include "gmock/gmock.h"

#include <string>
#include <vector>
#include <map>

using namespace testing;
using namespace std;

vector<pair<string,unsigned int>> conversions = {
    make_pair("M", 1000),
    make_pair("CM", 900),
    make_pair("D", 500),
    make_pair("CD", 400),
    make_pair("C", 100),
    make_pair("XC", 90),
    make_pair("L", 50),
    make_pair("XL", 40),
    make_pair("X", 10),
    make_pair("IX", 9),
    make_pair("V", 5),
    make_pair("IV", 4),
    make_pair("I", 1)
};

string convert(unsigned int arabic) {
    string roman = "";
    for_each (conversions.begin(), conversions.end(),
        [&] (pair<string, unsigned int> conversion) {
            auto romanDigit = conversion.first;
            auto arabicDigit = conversion.second;
            while (arabic >= arabicDigit) {
                roman += romanDigit;
                arabic -= arabicDigit;
            }
        });
    return roman;
}


TEST(ARomanConverter, ConvertsStuff) {
    ASSERT_THAT(convert(1), Eq("I"));
    ASSERT_THAT(convert(2), Eq("II"));
    ASSERT_THAT(convert(3), Eq("III"));
    ASSERT_THAT(convert(4), Eq("IV"));
    ASSERT_THAT(convert(5), Eq("V"));
    ASSERT_THAT(convert(9), Eq("IX"));
    ASSERT_THAT(convert(10), Eq("X"));
    ASSERT_THAT(convert(20), Eq("XX"));
    ASSERT_THAT(convert(40), Eq("XL"));
    ASSERT_THAT(convert(50), Eq("L"));
    ASSERT_THAT(convert(90), Eq("XC"));
    ASSERT_THAT(convert(100), Eq("C"));
    ASSERT_THAT(convert(400), Eq("CD"));
    ASSERT_THAT(convert(500), Eq("D"));
    ASSERT_THAT(convert(900), Eq("CM"));
    ASSERT_THAT(convert(1000), Eq("M"));
    ASSERT_THAT(convert(3894), Eq("MMMDCCCXCIV"));
}
