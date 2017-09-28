#include "gmock/gmock.h"
#include "ASSERT_CURRENT_STATE.h"

#include "ScannerTestData.h"

#include "TestScanner.h"
#include "Scanner.h"
#include "ScannerStateCheckin.h"
#include "ScannerStateInventory.h"
#include "ScannerStateCheckout.h"
#include "TimestampSource.h"

#include "boost/date_time/gregorian/gregorian_types.hpp"
#include <string>

using namespace std;
using namespace testing;
using namespace boost::gregorian;

class ScannerStateCheckinTest : public Test, public TestScanner {
public:
    ScannerStateCheckin* state;

    virtual void SetUp() {
        state = new ScannerStateCheckin(scanner);
        scanner->setCurrentState(state);
    }

    virtual void TearDown() {
    }
};

TEST_F(ScannerStateCheckinTest, DisplaysWarningMessageWhenCompletePressed) {
    EXPECT_CALL(*display, showMessage(ScannerStateCheckin::MSG_WAITING_FOR_RETURNS));

    state->pressDone();
}

TEST_F(ScannerStateCheckinTest, ChangesStateToInventoryWhenInventoryCardScanned) {
    state->scanInventoryCard("");

    ASSERT_CURRENT_STATE<ScannerStateInventory>(scanner);
}

TEST_F(ScannerStateCheckinTest, ChangesStateToCheckoutWhenPatronCardScanned) {
    state->scanPatronCard(ScannerTestData::PATRON_JOE_CARD);

    ASSERT_CURRENT_STATE<ScannerStateCheckout>(scanner);
}

TEST_F(ScannerStateCheckinTest, StoresPatronIdWhenScanned) {
    state->scanPatronCard(ScannerTestData::PATRON_JOE_CARD);

    ASSERT_THAT(scanner->patronId(), Eq(ScannerTestData::PATRON_JOE_CARD));
}

TEST_F(ScannerStateCheckinTest, ChangesBranchWhenBranchIdScanned) {
    scanner->setBranchId(ScannerTestData::BRANCH_SOUTH_CARD);

    state->scanBranchCard(ScannerTestData::BRANCH_WEST_CARD);

    ASSERT_THAT(scanner->branchId(), Eq(ScannerTestData::BRANCH_WEST_CARD));
}

TEST_F(ScannerStateCheckinTest, ChecksInBookWhenBarcodeScanned) {
    scanner->setBranchId(ScannerTestData::BRANCH_SOUTH_CARD);
    EXPECT_CALL(*holdingService(), 
        checkIn(Eq(ScannerTestData::HOLDING_CATCH22_BARCODE), TimestampSource::now(), ScannerTestData::BRANCH_SOUTH_CARD));

    state->scanHolding(ScannerTestData::HOLDING_CATCH22_BARCODE);
}
