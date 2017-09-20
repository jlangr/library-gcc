#include "gmock/gmock.h"
#include "Soundex.h"

using namespace testing;

// Instructions for exercise:
//
// 1. Activate the topmost (disabled) test.
// 2. Build & run tests. 
//    Ensure the newest test fails. If it does not, you must:
//    a) Disable the topmost test.
//    b) Simplify your solution for the prior test.
// 3. Write just enough code, no more.
// 4. Build and ensure all tests pass.
// 5. Factor the code to be as clean as possible.
// 6. Build and ensure all tests pass.
// Repeat steps 1-6 until all tests are enabled and passing.
//
// See the end of this file for soundex rules on which the tests are based.
// Follow any additional instructions appearing in test comments.
// Warning: adding or renaming any tests will likely generate a fatal exception.

class SoundexTest: public Test
{
public:
    Soundex soundex;
};

// Soundex cases verified by http://stevemorse.org/census/soundex.html

TEST_F(SoundexTest, DISABLED_PadsSingleLetterWithZeros)
{
    ASSERT_THAT(soundex.Convert("A"), Eq("A000"));
}

TEST_F(SoundexTest, DISABLED_RetainsFirstLetter)
{
    ASSERT_THAT(soundex.Convert("B"), Eq("B000"));
}

TEST_F(SoundexTest, DISABLED_ConvertsHardSoundsUsingLookupTable)
{
    // should we really have more than one case per test?
    ASSERT_THAT(soundex.Convert("Ab"), Eq("A100"));
    //ASSERT_THAT(soundex.Convert("Am"), Eq("A500"));
}

TEST_F(SoundexTest, DISABLED_PadsWithZerosToEnsureThreeDigits)
{
    ASSERT_THAT(soundex.Convert("Af"), Eq("A100"));
}

TEST_F(SoundexTest, DISABLED_DoesNotAppendZerosIfAlreadyFourCharacters)
{
    // See note in ConvertsHardSoundsUsingLookupTable,
    // and change that test accordingly.
    ASSERT_THAT(soundex.Convert("Arml"), Eq("A654"));
}

TEST_F(SoundexTest, DISABLED_LimitsLengthToFourCharacters)
{
    ASSERT_THAT(soundex.Convert("Armlrml"), Eq("A654"));
}

TEST_F(SoundexTest, DISABLED_IgnoresSoftSounds)
{
    // should we really have more than one assert per test?
    ASSERT_THAT(soundex.Convert("Aaei"), Eq("A000"));
    //ASSERT_THAT(soundex.Convert("Aouy"), Eq("A000"));
    //ASSERT_THAT(soundex.Convert("Ahwe"), Eq("A000"));
}

TEST_F(SoundexTest, DISABLED_IgnoresDuplicateHardSounds)
{
    // This first assertion is designed to pass immediately.
    // What is the value of including it (or not)?
    ASSERT_THAT(soundex.Digit('c'), Eq(soundex.Digit('g')));

    ASSERT_THAT(soundex.Convert("Acgbm"), Eq("A215"));
}

TEST_F(SoundexTest, DISABLED_HardSoundNotIgnoredIfVowelPrecedesIt)
{
    ASSERT_THAT(soundex.Digit('c'), Eq(soundex.Digit('g')));
    ASSERT_THAT(soundex.IsVowel('o'), Eq(true));

    ASSERT_THAT(soundex.Convert("Acogbm"), Eq("A221"));
    // If you receive an error that the following test is passing:
    // Had enough? Enable the following test, stop here, and see the notes at the bottom of the tests.
    // Or, for extra credit: Find a way to simplify your solution to pass only this penultimate test.
}

TEST_F(SoundexTest, DISABLED_HardSoundIgnoredIfSoftConsonantPrecedesIt)
{
    // Note that alternate specifications allow this to convert to A221
    ASSERT_THAT(soundex.IsSoftConsonant('w'), Eq(true));

    ASSERT_THAT(soundex.Convert("Acwgbm"), Eq("A215"));
}

// Finished--congratulations!
// What tests are missing? Make a list.
// If you still have time, implement them one by one.

/*
Rules for American Soundex
Source: http://en.wikipedia.org/wiki/Soundex

The Soundex code for a name consists of a letter followed by three numerical digits: the letter is the first letter of the name, and the digits encode the remaining consonants. Similar sounding consonants share the same digit so, for example, the labial consonants B, F, P, and V are each encoded as the number 1.
The correct value can be found as follows:
Retain the first letter of the name and drop all other occurrences of a, e, i, o, u, y, h, w.
Replace consonants with digits as follows (after the first letter):
b, f, p, v => 1
c, g, j, k, q, s, x, z => 2
d, t => 3
l => 4
m, n => 5
r => 6
Two adjacent letters (in the original name) with the same number are coded as a single number;
also two letters with the same number separated by 'h' or 'w' are coded as a single number, 
whereas such letters separated by a vowel are coded twice. This rule also applies to the first letter.
Continue until you have one letter and three numbers. If you run out of letters, fill in 0s until there are three numbers.
*/
