#include "gmock/gmock.h"

#include "BarcodeUtil.h"

using namespace testing;

TEST(BarcodeUtilTest, BranchCodesStartWithB) {
    ASSERT_THAT(BarcodeUtil::isBranchId("b123"), Eq(true));
}

TEST(BarcodeUtilTest, IsBranchIdReturnsFalseWhenStartsWithOtherCharacter) {
    ASSERT_THAT(BarcodeUtil::isBranchId("p123"), Eq(false));
}

TEST(BarcodeUtilTest, IgnoresCaseWhenTestingFirstCharacterForBranch) {
    ASSERT_THAT(BarcodeUtil::isBranchId("B123"), Eq(true));
}

TEST(BarcodeUtilTest, PatronIdsStartWithP) {
    ASSERT_THAT(BarcodeUtil::isPatronId("p123"), Eq(true));
}

TEST(BarcodeUtilTest, IsPatronIdReturnsFalseWhenStartsWithOtherCharacter) {
    ASSERT_THAT(BarcodeUtil::isPatronId("b123"), Eq(false));
}

TEST(BarcodeUtilTest, IgnoresCaseWhenTestingFirstCharacterForPatron) {
    ASSERT_THAT(BarcodeUtil::isPatronId("P123"), Eq(true));
}

TEST(BarcodeUtilTest, HoldingBarcodesContainColon) {
    ASSERT_THAT(BarcodeUtil::isHoldingBarcode("qa123:1"), Eq(true));
}

TEST(BarcodeUtilTest, IsHoldingBarcodeReturnsFalseWhenNoColonContained) {
    ASSERT_THAT(BarcodeUtil::isHoldingBarcode("zz123 2"), Eq(false));
}
