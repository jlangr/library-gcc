#pragma once

#include <string>
#include <list>
#include <exception>

#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>

#include "StringUtil.h"

// TODO delete!
using namespace std;
using namespace stringutil;

class InvalidNameException : public std::exception {};

class NormalizedName
{
public:
    NormalizedName(const std::string& name)
    {
        ThrowWhenContainsMoreThanOneComma(name);
        SplitToNameAndSuffix(trim(name));
    }

    void ThrowWhenContainsMoreThanOneComma(const std::string& name)
    {
        if (count(name.begin(), name.end(), ',') > 1)
            throw InvalidNameException();
    }

    void SplitToNameAndSuffix(const std::string& inputName)
    {
        size_t indexOfComma{ inputName.find(",") };
        if (indexOfComma != string::npos) {
            name = inputName.substr(0, indexOfComma);
            suffix = inputName.substr(indexOfComma);
        }
        else
        {
            name = inputName;
            suffix = "";
        }
    }

    string Initials(list<string> nameParts)
    {
        std::stringstream s;
        for (auto namePart : nameParts)
            s << ' ' << Initial(namePart);
        return s.str();
    }

    string Initial(const string& namePart)
    {
        if (namePart.length() == 1)
            return namePart;
        stringstream s;
        s << namePart[0] << ".";
        return s.str();
    }

    std::string AsString()
    {
        vector<string> parts = split(name, ' ');
        if (1 == parts.size())
            return name;

        list<string> partsList(parts.begin(), parts.end());
        string lastName = partsList.back();
        partsList.pop_back();
        string firstName = partsList.front();
        partsList.pop_front();
        return lastName + ", " + firstName + Initials(partsList) + suffix;
    }

private:
    std::string name;
    std::string suffix;
};