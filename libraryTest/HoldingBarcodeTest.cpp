#include "gmock/gmock.h"

#include "HoldingBarcode.h"
#include "InvalidBarcodeException.h"

using namespace testing;

TEST(AHoldingBarcode, AnswersItsStringRepresentation) {
    ASSERT_THAT(HoldingBarcode("abc", 2).asString(), StrEq("abc:2"));
}

TEST(AHoldingBarcode, ThrowsWhenConstructedWithBarcodeWithNoColon) {
    ASSERT_THROW(HoldingBarcode("A"), InvalidBarcodeException);
}

TEST(AHoldingBarcode, BarcodeParseReturnsClassification) {
    ASSERT_THAT(HoldingBarcode("A123:3").classification(), StrEq("A123"));
}

TEST(AHoldingBarcode, CanExtractCopyNumberWhenCreatedWithBarcode) {
    ASSERT_THAT(HoldingBarcode("A234:42").copyNumber(), Eq(42u));
}
