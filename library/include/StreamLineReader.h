#ifndef STREAM_LINE_READER_H
#define STREAM_LINE_READER_H

#include <istream>
#include <string>

class StreamLineReader
{
public:
    StreamLineReader(std::istream* input);
    ~StreamLineReader(void);
    void Read(std::string& stringMember);
    void Read(unsigned int& intMember);

private:
    std::istream* mInput;
};

#endif
