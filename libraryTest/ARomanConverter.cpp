#include "gmock/gmock.h"
#include <string>
#include <vector>

using namespace testing;

std::vector<std::pair<unsigned int, std::string>> conversions{
    {1000, "M"},
    {900, "CM"},
    {500, "D"},
    {400, "CD"},
    {100, "C"},
    {90, "XC"},
    {50, "L"},
    {40, "XL"},
    {10, "X"},
    {9, "IX"},
    {5, "V"},
    {4, "IV"},
    {1, "I"}
};

std::string convert(unsigned int arabic) {
    std::string roman{""};

    for_each(conversions.begin(), conversions.end(),
            [&](std::pair<unsigned int, std::string> conversion) {
        auto arabicDigit{conversion.first};
        auto romanDigit{conversion.second};
        while (arabic >= arabicDigit) {
            roman += romanDigit;
            arabic -= arabicDigit;
        }
    });
    return roman;
}

TEST(ARomanConverter, convertsStuff) {
    ASSERT_THAT(convert(1), Eq("I"));
    ASSERT_THAT(convert(2), Eq("II"));
    ASSERT_THAT(convert(3), Eq("III"));
    ASSERT_THAT(convert(4), Eq("IV"));
    ASSERT_THAT(convert(5), Eq("V"));
    ASSERT_THAT(convert(9), Eq("IX"));
    ASSERT_THAT(convert(10), Eq("X"));
    ASSERT_THAT(convert(11), Eq("XI"));
    ASSERT_THAT(convert(20), Eq("XX"));
    ASSERT_THAT(convert(40), Eq("XL"));
    ASSERT_THAT(convert(50), Eq("L"));
    ASSERT_THAT(convert(90), Eq("XC"));
    ASSERT_THAT(convert(100), Eq("C"));
    ASSERT_THAT(convert(400), Eq("CD"));
    ASSERT_THAT(convert(500), Eq("D"));
    ASSERT_THAT(convert(900), Eq("CM"));
    ASSERT_THAT(convert(1000), Eq("M"));
    ASSERT_THAT(convert(3444), Eq("MMMCDXLIV"));
}
