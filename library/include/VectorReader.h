#ifndef VECTOR_READER_H
#define VECTOR_READER_H

#include <string>
#include <fstream>
#include <vector>
#include <memory>

template <typename T>
class VectorReader {
public:
    VectorReader(const std::string& name) : mName(name) {}
    virtual ~VectorReader(void) {}
    
    virtual std::vector<T> load() const {
        std::ifstream mStream(mName.c_str());

        std::vector<T> objects;

        while (mStream) {
            T object;
            object.load(mStream);
            if (object.id() != "") objects.push_back(object);
        }
        mStream.close();
        return objects;
    }

    std::string name() const { 
        return mName; 
    }

private:
    std::string mName;
    std::ifstream* mStream;
};

#endif
