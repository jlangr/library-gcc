#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <string>
#include <memory>
#include <map>
#include <vector>

#include "Serializable.h"

typedef bool(*MatcherFunction)(Serializable&, const std::string&);

template <class T>
class Persistence
{
public:
    Persistence(const std::string& table) : mTable(table) {}
    Persistence() : mTable{""} {}
    virtual ~Persistence(void) {}

    virtual unsigned int size() const=0;
    virtual void add(const T&)=0;
    virtual void clear()=0;
    virtual std::unique_ptr<T> get(const std::string& id) const=0;
    virtual bool matches(MatcherFunction, const std::string&) const=0;
    virtual void findAllMatching(MatcherFunction, const std::string&, std::vector<Serializable*>& matchesToPopulate) const=0;

protected:
    std::string mTable;
};

#endif
