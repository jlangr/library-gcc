#ifndef KEYED_FILE_PERSISTENCE_H
#define KEYED_FILE_PERSISTENCE_H

#include <string>
#include <memory>

#include "Persistence.h"
#include "Serializable.h"

template <class T>
class KeyedFilePersistence: public Persistence<T>
{
public:
    KeyedFilePersistence() : Persistence<T>("") {}
    KeyedFilePersistence(const std::string& table) 
        : Persistence<T>(table) 
    {
    }

    virtual ~KeyedFilePersistence(void) 
    {
    }

    unsigned int size() const 
    { 
        return 0; 
    }

    virtual void clear()
    {
    }

    void add(const T& object) 
    { 
    }

    std::unique_ptr<T> get(const std::string& id) const
    {
        return std::unique_ptr<T>(nullptr);
    }

    virtual bool matches(MatcherFunction matches, const std::string& name) const
    {
        return false;
    }

    virtual void findAllMatching(MatcherFunction matches, const std::string& name, std::vector<Serializable*>& matchesToPopulate) const
    {
    }

private:
    std::map<std::string,Serializable*> mData;
};

#endif
