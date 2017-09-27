#ifndef SCANNER_STATE_SOUNDEX_H
#define SCANNER_STATE_SOUNDEX_H

#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std; // tsk tsk

class Soundex {
public:
    const static unsigned int MAX_LENGTH;
    const static string SOFT_SOUNDS;
    const static string SOFT_CONSONANTS;
    const static string VOWELS;

    Soundex(void) {
        initializeConsonantToDigitTable();
    }
    virtual ~Soundex(void) {}

    string convert(const string& name) {
        return "";
    }

    // +++ do not change any of these helper methods +++
    char digit(char consonant) const {
        map<char, char>::const_iterator it = consonantIndices.find(consonant);
        if (it == consonantIndices.end())
            return '0';
        return it->second;
    }

    bool isSoftSound(char letter) const {
        return SOFT_SOUNDS.find(letter) != string::npos;
    }

    bool isSoftConsonant(char letter) const {
        return SOFT_CONSONANTS.find(letter) != string::npos;
    }

    bool isVowel(char letter) const {
        return VOWELS.find(letter) != string::npos;
    }
    // ^^^ do not change any of the above helper methods ^^^


private:
    map<char, char> consonantIndices;

    void initializeConsonantToDigitTable() {
        consonantIndices['b'] = '1';
        consonantIndices['f'] = '1';
        consonantIndices['p'] = '1';
        consonantIndices['v'] = '1';
        consonantIndices['c'] = '2';
        consonantIndices['g'] = '2';
        consonantIndices['j'] = '2';
        consonantIndices['k'] = '2';
        consonantIndices['q'] = '2';
        consonantIndices['s'] = '2';
        consonantIndices['x'] = '2';
        consonantIndices['z'] = '2';
        consonantIndices['d'] = '3';
        consonantIndices['t'] = '3';
        consonantIndices['l'] = '4';
        consonantIndices['m'] = '5';
        consonantIndices['n'] = '5';
        consonantIndices['r'] = '6';
    }
};

#endif
