#ifndef NAME_NORMALIZER_H
#define NAME_NORMALIZER_H

#include <string>
#include <exception>
#include <algorithm>
#include <sstream>
#include <ostream>

#include "StringUtil.h"

using namespace std;

class InvalidNameException : public exception {};

class NormalizedName
{
public:
    NormalizedName(const string& name)
      : _name{name}
    {
      ThrowWhenContainingTooManyCommas();
    }

    ~NormalizedName() {}

    string AsString() const
    {
        auto name = stringutil::trim(_name);
        auto nameWithoutSuffix = RemoveSuffix(name);
        auto parts = stringutil::split(nameWithoutSuffix, ' ');
        if (1 == parts.size())
          return nameWithoutSuffix + Suffix(name); 
        
        return LastName(parts) + ", " + FirstName(parts) + MiddleInitials(parts) + Suffix(name);
    }
private:
    void ThrowWhenContainingTooManyCommas() {
      if (count(_name.begin(), _name.end(), ',') > 1)
        throw InvalidNameException();
    }

    string RemoveSuffix(const string& name) const {
      auto commaIndex = name.find(',');
      if (commaIndex == string::npos) return name;
      return name.substr(0, commaIndex);
    }

    string Suffix(const string& name) const {
      auto commaIndex = name.find(',');
      if (commaIndex == string::npos) return "";
      return name.substr(commaIndex);
    }

    string MiddleInitials(const vector<string>& parts) const {
      if (parts.size() <= 2) return "";
      return JoinInitials(parts);
    }

    string JoinInitials(const vector<string>& parts) const {
      stringstream s;
      for_each(parts.begin() + 1, parts.end() - 1, 
          [&](const string& part) { s << " " + Initial(part); });
      return s.str();
    }

    string MiddleInitial(const vector<string>& parts) const {
      if (parts.size() <= 2) return "";
      return " " + Initial(parts[1]);
    }

    string Initial(const string& part) const {
      if (part.size() == 1) return part;
      return string{part[0], '.'};
    }

    string LastName(vector<string> parts) const {
      return parts.back();
    }

    string FirstName(vector<string> parts) const {
      return parts[0];
    }


    string _name;
};

#endif
