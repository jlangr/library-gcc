#include "gmock/gmock.h"

#include "StreamLineReader.h"

#include <iostream>
#include <sstream>
#include <string>
#include <memory>

using namespace std;
using namespace testing;

class StreamLineReaderTest: public Test
{
public:
    void SetUp()
    {
    }

    void TearDown()
    {
    }

    template <typename T>
    auto_ptr<istream> CreateInputStream(T text)
    {
        ostringstream output;
        output << text << endl;
        auto_ptr<istream> input(new istringstream(output.str()));
        return input;
    }
};

TEST_F(StreamLineReaderTest, CanReadLineOfText)
{
    auto_ptr<istream> input = CreateInputStream<const string&>("hello");
    StreamLineReader reader(input.get());
    string text;

    reader.Read(text);

    ASSERT_THAT(text, Eq("hello"));
}

TEST_F(StreamLineReaderTest, CanReadLineWithUnsignedInt)
{
    auto_ptr<istream> input = CreateInputStream<unsigned int>(42);
    StreamLineReader reader(input.get());
    unsigned int number;

    reader.Read(number);

    ASSERT_THAT(number, Eq(42));
}

TEST_F(StreamLineReaderTest, SetsUnsignedIntToZeroOnConvertFail)
{
    auto_ptr<istream> input = CreateInputStream<const string&>("dsadf");
    StreamLineReader reader(input.get());
    unsigned int number;

    reader.Read(number);

    ASSERT_THAT(number, Eq(0));
}
