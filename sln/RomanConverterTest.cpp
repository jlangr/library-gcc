#include "gmock/gmock.h"

#include <string>
#include <sstream>

using namespace std;
using namespace testing;

unsigned int arabics[] = { 1000, 900, 50, 10, 5, 4, 1 };
string romans[] = { "M", "CM", "L", "X", "V", "IV", "I" };

string Convert(unsigned int arabic)
{
    stringstream roman;
    for (int i = 0; i < sizeof(arabics)/sizeof(int); i++)
    {
        while (arabic >= arabics[i])
        {
            roman << romans[i];
            arabic -= arabics[i];
        }
    }
    return roman.str();
}

TEST(RomanConverterTest, ConvertAll)
{
    ASSERT_THAT(Convert(1), Eq("I"));
    ASSERT_THAT(Convert(2), Eq("II"));
    ASSERT_THAT(Convert(3), Eq("III"));
    ASSERT_THAT(Convert(4), Eq("IV"));
    ASSERT_THAT(Convert(5), Eq("V"));
    ASSERT_THAT(Convert(7), Eq("VII"));
    ASSERT_THAT(Convert(10), Eq("X"));
    ASSERT_THAT(Convert(11), Eq("XI"));
    ASSERT_THAT(Convert(20), Eq("XX"));
    ASSERT_THAT(Convert(50), Eq("L"));
    ASSERT_THAT(Convert(88), Eq("LXXXVIII"));
    ASSERT_THAT(Convert(2987), Eq("MMCMLXXXVII"));
}
