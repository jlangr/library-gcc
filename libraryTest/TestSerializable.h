#pragma once

#include <string>
#include <fstream>

#include "Serializable.h"
#include "StreamLineReader.h"

class TestSerializable: public Serializable {
public:
    TestSerializable() 
        : mName("")
        , mId("") {}

    TestSerializable(const std::string& name, const std::string& id)
        : mName(name)
        , mId(id) {}

    virtual ~TestSerializable() {}

    std::string name() { 
        return mName; 
    }

    virtual std::string id() const { 
        return mId; 
    }
    
    virtual void load(std::istream& input) {
        StreamLineReader reader(&input);
        reader.read(mName);
        reader.read(mId);
    }

    virtual TestSerializable* clone() const {
        return new TestSerializable(mName, mId);
    }

    virtual void writeOn(std::ostream& output) {
        output << mName << std::endl << mId << std::endl;
    }

    bool operator==(const TestSerializable& other) const {
        return mId == other.mId && mName == other.mName;
    }

private:
    std::string mName;
    std::string mId;
};
