#include "gmock/gmock.h"

#include "HoldingBarcode.h"

using namespace testing;

TEST(HoldingBarcodeTest, StringRepresentation)
{
    ASSERT_THAT(HoldingBarcode("abc", 2).asString(), StrEq("abc:2"));
}
