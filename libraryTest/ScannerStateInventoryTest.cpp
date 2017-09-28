#include "gmock/gmock.h"
#include "ASSERT_CURRENT_STATE.h"

#include "ScannerTestData.h"

#include "TestScanner.h"
#include "Scanner.h"
#include "ScannerStateInventory.h"
#include "ScannerStateCheckin.h"

#include <string>

using namespace std;
using namespace testing;

class ScannerStateInventoryTest : public Test, public TestScanner {
public:
    ScannerStateInventory* state;

    virtual void SetUp() {
        state = new ScannerStateInventory(scanner);
        scanner->setCurrentState(state);
    }

    virtual void TearDown() {
    }
};

TEST_F(ScannerStateInventoryTest, DisplaysWarningMessageWhenInventoryCardScanned) {
    EXPECT_CALL(*display, showMessage(ScannerStateInventory::MSG_COMPLETE_INVENTORY));

    state->scanInventoryCard(Scanner::INVENTORY_CARD_NUMBER);
}

TEST_F(ScannerStateInventoryTest, ChangesBranchWhenBranchIdScanned) {
    stringstream expected;
    expected << ScannerStateInventory::MSG_BRANCH_CHANGED << ScannerTestData::BRANCH_SOUTH_CARD;
    EXPECT_CALL(*display, showMessage(expected.str()));
    ASSERT_THAT(scanner->branchId(), Ne(ScannerTestData::BRANCH_SOUTH_CARD));

    state->scanBranchCard(ScannerTestData::BRANCH_SOUTH_CARD);

    ASSERT_THAT(scanner->branchId(), Eq(ScannerTestData::BRANCH_SOUTH_CARD));
}

TEST_F(ScannerStateInventoryTest, AddsNewHoldingWhenHoldingScanned)  {
    scanner->setBranchId(ScannerTestData::BRANCH_SOUTH_CARD);
    EXPECT_CALL(*display, showMessage(_));
    EXPECT_CALL(*holdingService(),
        addAtBranch(ScannerTestData::BRANCH_SOUTH_CARD, ScannerTestData::HOLDING_TRIAL_BARCODE));

    state->scanHolding(ScannerTestData::HOLDING_TRIAL_BARCODE);
}

TEST_F(ScannerStateInventoryTest, DisplaysHoldingAddedMessageWhenHoldingScanned)  {
    scanner->setBranchId(ScannerTestData::BRANCH_SOUTH_CARD);
    
    EXPECT_CALL(*display, 
        showMessage(ScannerStateInventory::MSG_HOLDING_ADDED + ScannerTestData::HOLDING_TRIAL_BARCODE));
    EXPECT_CALL(*holdingService(), addAtBranch(_, _));

    state->scanHolding(ScannerTestData::HOLDING_TRIAL_BARCODE);
}

TEST_F(ScannerStateInventoryTest, DisplaysErrorWhenDuplicateHoldingScanned) {
    // TODO new feature!
    // needs HoldingService to throw if holding already exists
}

TEST_F(ScannerStateInventoryTest, DisplayMessageWhenPatronScanned) {
    EXPECT_CALL(*display, showMessage(ScannerStateInventory::MSG_COMPLETE_INVENTORY));

    state->scanPatronCard(ScannerTestData::PATRON_JANE_CARD);
}

TEST_F(ScannerStateInventoryTest, ChangesStateToCheckinWhenDonePressed) {
    state->pressDone();
    
    ASSERT_CURRENT_STATE<ScannerStateCheckin>(scanner);
}
