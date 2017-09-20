#include "gmock/gmock.h"

#include "VectorWriter.h"
#include "VectorReader.h"
#include "Serializable.h"
#include "StreamLineReader.h"
#include "TestSerializable.h"

using namespace std;
using namespace testing;

class VectorReaderTest : public Test
{
public:
};

TEST_F(VectorReaderTest, CanRead)
{
    vector<TestSerializable> objects =
    { TestSerializable("a", "10"),
    TestSerializable("b", "42") };

    VectorWriter<TestSerializable> writer("test.dat");
    writer.WriteAll(objects);

    VectorReader<TestSerializable> reader("test.dat");
    vector<TestSerializable> loadedObjects = reader.Load();

    ASSERT_THAT(loadedObjects, Eq(objects));
}
