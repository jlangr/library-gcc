#ifndef KEYED_MEMORY_PERSISTENCE_H
#define KEYED_MEMORY_PERSISTENCE_H

#include <string>
#include <memory>
#include <map>
#include <algorithm>

#include "Persistence.h"
#include "Serializable.h"

template <class T>
class KeyedMemoryPersistence: public Persistence<T> {
public:
    KeyedMemoryPersistence(const std::string& table) : Persistence<T>(table) {}
    ~KeyedMemoryPersistence(void) {}

    static void clearAll() {
        mData.clear();
    }    
    
    virtual void clear() {
        KeyedMemoryPersistence::clearAll();
    }

    unsigned int size() const { 
        return mData.size(); 
    }

    virtual void add(const T& object) { 
        mData[object.id()] = object.clone();
    }

    std::unique_ptr<T> get(const std::string& id) const {
        std::map<std::string,Serializable*>::const_iterator it = mData.find(id);
        if (it == mData.end())
            return std::unique_ptr<T>(nullptr);
        T* existing = static_cast<T*>(it->second);
        T* copy = existing->clone();
        return std::unique_ptr<T>(copy);
    }

    virtual bool matches(MatcherFunction matches, const std::string& name) const {
        auto it{std::find_if(mData.begin(), mData.end(),
                [&] (const std::pair<std::string,Serializable*>& p) {
                    Serializable* object = p.second;
                    return matches(*object, name);
                })};
        return it != mData.end();
    }

    virtual void findAllMatching(MatcherFunction matches, const std::string& name, std::vector<Serializable*>& matchesToPopulate) const {
        std::for_each(mData.begin(), mData.end(),
                [&] (const std::pair<std::string,Serializable*>& p) {
                    Serializable* object = p.second;
                    if (matches(*object, name))
                        matchesToPopulate.push_back(object);
                });
    }

private:
    static std::map<std::string,Serializable*> mData;
    typedef std::map<std::string,Serializable*>::iterator DataIterator;
};

template <class T>
std::map<std::string,Serializable*> KeyedMemoryPersistence<T>::mData;

#endif
