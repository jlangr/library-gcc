#include "gmock/gmock.h"

#include "TestScanner.h"

#include "ScannerTestData.h"
#include "ScannerStateWaiting.h"
#include "ScannerStateCheckin.h"
#include "ASSERT_CURRENT_STATE.h"

#include "Scanner.h"

#include <string>

using namespace std;
using namespace testing;

class ScannerStateWaitingTest : public Test, public TestScanner 
{
public:
    ScannerState* state;
    
    virtual void SetUp() {
        state = new ScannerStateWaiting(scanner);
    }

    virtual void TearDown() {
        delete state;
    }
};

TEST_F(ScannerStateWaitingTest, DisplaysWarningMessageWhenDonePressed) 
{
    EXPECT_CALL(*display, showMessage(ScannerStateWaiting::MSG_SCAN_BRANCH_ID_FIRST));

    state->pressDone();
}

TEST_F(ScannerStateWaitingTest, DisplaysWarningMessageWhenPatronCardScanned) 
{
    EXPECT_CALL(*display, showMessage(ScannerStateWaiting::MSG_SCAN_BRANCH_ID_FIRST));

    state->scanPatronCard(ScannerTestData::PATRON_JOE_CARD);
}

TEST_F(ScannerStateWaitingTest, DisplaysWarningMessageWhenInventoryCardScanned) 
{
    EXPECT_CALL(*display, showMessage(ScannerStateWaiting::MSG_SCAN_BRANCH_ID_FIRST));

    state->scanInventoryCard(Scanner::INVENTORY_CARD_NUMBER);
}

TEST_F(ScannerStateWaitingTest, DisplaysWarningMessageWhenHoldingScanned) 
{
    EXPECT_CALL(*display, showMessage(ScannerStateWaiting::MSG_SCAN_BRANCH_ID_FIRST));

    state->scanHolding(ScannerTestData::HOLDING_CATCH22_BARCODE);
}

TEST_F(ScannerStateWaitingTest, SetsStateToCheckinWhenBranchScanned) 
{
    state->scanBranchCard(ScannerTestData::BRANCH_SOUTH_CARD);

    ASSERT_CURRENT_STATE<ScannerStateCheckin>(scanner);
}

TEST_F(ScannerStateWaitingTest, StoresBranchWhenBranchScanned)
{
    state->scanBranchCard(ScannerTestData::BRANCH_SOUTH_CARD);

    ASSERT_THAT(scanner->branchId(), Eq(ScannerTestData::BRANCH_SOUTH_CARD));
}
