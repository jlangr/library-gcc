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

    unsigned int Size() const 
    { 
        return 0; 
    }

    virtual void Clear()
    {
    }

    void Add(const T& object) 
    { 
    }

    std::unique_ptr<T> Get(const std::string& id) const
    {
        return std::unique_ptr<T>(nullptr);
    }

    virtual bool Matches(MatcherFunction matches, const std::string& name) const
    {
        return false;
    }

    virtual void FindAllMatching(MatcherFunction matches, const std::string& name, std::vector<Serializable*>& matchesToPopulate) const
    {
    }

private:
    std::map<std::string,Serializable*> mData;
};

#endif
