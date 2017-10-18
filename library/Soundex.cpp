#include "Soundex.h"

const unsigned int Soundex::MAX_LENGTH(4);
const string Soundex::VOWELS("aeiouy");
const string Soundex::SOFT_CONSONANTS("hw");
const string Soundex::SOFT_SOUNDS(Soundex::VOWELS + Soundex::SOFT_CONSONANTS);
