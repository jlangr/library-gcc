#ifndef KEYED_MEMORY_PERSISTENCE_H
#define KEYED_MEMORY_PERSISTENCE_H

#include <string>
#include <memory>
#include <map>
#include <algorithm>

#include "Persistence.h"
#include "Serializable.h"

template <class T>
class KeyedMemoryPersistence: public Persistence<T>
{
public:
    KeyedMemoryPersistence(const std::string& table) : Persistence<T>(table) {}
    ~KeyedMemoryPersistence(void) {}

    static void ClearAll()
    {
        mData.clear();
    }    
    
    virtual void Clear()
    {
        KeyedMemoryPersistence::ClearAll();
    }

    unsigned int Size() const 
    { 
        return mData.size(); 
    }

    virtual void Add(T& object) 
    { 
        mData[object.Id()] = object.Clone();
        // TODO need a Remove (that also does a delete on this object);
    }

    std::unique_ptr<T> Get(const std::string& id) const
    {
        std::map<std::string,Serializable*>::const_iterator it = mData.find(id);
        // TODO!!!!
//        if (it == mData.end())
//            return std::unique_ptr<T>(NULL);
        T* existing = static_cast<T*>(it->second);
        T* copy = existing->Clone();
        return std::unique_ptr<T>(copy);
    }


    // TODO: can we use find_if?
    //DataIterator it = std::find_if(mData.begin(), mData.end(), std::bind2nd(f, value));

    virtual bool Matches(MatcherFunction matches, const std::string& name) const
    {
        for (std::map<std::string,Serializable*>::const_iterator it = mData.begin();
            it != mData.end();
            it++)
        {
            Serializable* object = it->second;
            if (matches(*object, name))
                return true;
        }
        return false;
    }

    virtual void FindAllMatching(MatcherFunction matches, const std::string& name, std::vector<Serializable*>& matchesToPopulate) const
    {
        for (std::map<std::string,Serializable*>::const_iterator it = mData.begin();
            it != mData.end();
            it++)
        {
            Serializable* object = it->second;
            if (matches(*object, name))
                matchesToPopulate.push_back(object);
        }
    }

private:
    static std::map<std::string,Serializable*> mData;
    typedef std::map<std::string,Serializable*>::iterator DataIterator;
};

template <class T>
std::map<std::string,Serializable*> KeyedMemoryPersistence<T>::mData;

#endif
