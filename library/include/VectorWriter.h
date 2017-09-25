#ifndef VECTOR_WRITER_H
#define VECTOR_WRITER_H

#include <vector>
#include <fstream>

template <typename T> // T should be a derivative of Serializable
class VectorWriter
{
public:
    VectorWriter(const std::string& filename)
        : mFilename(filename)
    {
    }

    virtual ~VectorWriter(void) 
    {
    }

    virtual void writeAll(std::vector<T>& objects)
    {
        // TODO: introduce raii-writer to ensure file close
        std::ofstream output(mFilename.c_str());
        for (auto it = objects.begin(); it != objects.end(); it++)
            it->writeOn(output);
        output.flush();
        output.close();
    }

private:
    std::string mFilename;
};

#endif
