#include "gmock/gmock.h"
#include "ASSERT_CURRENT_STATE.h"

#include "ScannerTestData.h"
#include "TestScanner.h"
#include "Scanner.h"
#include "ScannerStateCheckout.h"
#include "ScannerStateCheckin.h"
#include "TimestampSource.h"

#include "boost/date_time/gregorian/gregorian_types.hpp"
#include <string>

using namespace std;
using namespace testing;
using namespace boost::gregorian;

class ScannerStateCheckoutTest : public Test, public TestScanner
{
public:
    ScannerStateCheckout* state;

    virtual void SetUp() {
        state = new ScannerStateCheckout(scanner);
        scanner->setCurrentState(state);
    }

    void checkout(const string& patronCardNumber, const string& holdingBarcode)
    {
        EXPECT_CALL(*holdingService(), existsWithBarcode(_)).WillOnce(Return(true));
        EXPECT_CALL(*holdingService(), isAvailable(_)).WillOnce(Return(true));
        EXPECT_CALL(*holdingService(), 
            checkOut(patronCardNumber, holdingBarcode, TimestampSource::now()));
        EXPECT_CALL(*display, showMessage(ScannerStateCheckout::MSG_SCANNED_HOLDING));
        state->scanHolding(holdingBarcode);
    }

    virtual void TearDown() {
    }    
};

TEST_F(ScannerStateCheckoutTest, DisplaysWarningWhenPatronCardScanned)
{
    EXPECT_CALL(*display, showMessage(ScannerStateCheckout::MSG_COMPLETE_CHECKOUT_FIRST));

    state->scanPatronCard(ScannerTestData::PATRON_JOE_CARD);
}

TEST_F(ScannerStateCheckoutTest, DisplaysWarningWhenInventoryCardScanned)
{
    EXPECT_CALL(*display, showMessage(ScannerStateCheckout::MSG_COMPLETE_CHECKOUT_FIRST));

    state->scanInventoryCard(Scanner::INVENTORY_CARD_NUMBER);
}

TEST_F(ScannerStateCheckoutTest, ChecksOutHoldingWhenHoldingBarcodeScanned)
{
    scanner->setPatronId(ScannerTestData::PATRON_JANE_CARD);
    EXPECT_CALL(*holdingService(), existsWithBarcode(_)).WillOnce(Return(true));
    EXPECT_CALL(*holdingService(), isAvailable(_)).WillOnce(Return(true));
    EXPECT_CALL(*holdingService(), 
        checkOut(ScannerTestData::PATRON_JANE_CARD, ScannerTestData::HOLDING_CATCH22_BARCODE, TimestampSource::now()));
    EXPECT_CALL(*display, showMessage(ScannerStateCheckout::MSG_SCANNED_HOLDING));

    state->scanHolding(ScannerTestData::HOLDING_CATCH22_BARCODE);
}

TEST_F(ScannerStateCheckoutTest, DisplayMessageWhenHoldingDoesNotExist)
{
    scanner->setPatronId(ScannerTestData::PATRON_JANE_CARD);
    EXPECT_CALL(*holdingService(), existsWithBarcode(_)).WillOnce(Return(false));
    EXPECT_CALL(*display, showMessage(ScannerStateCheckout::MSG_INVALID_HOLDING_ID));

    state->scanHolding(ScannerTestData::HOLDING_CATCH22_BARCODE);
}

TEST_F(ScannerStateCheckoutTest, ChangesStateToCheckinWhenDonePressed)
{
    state->pressDone();
    
    ASSERT_CURRENT_STATE<ScannerStateCheckin>(scanner);
}

TEST_F(ScannerStateCheckoutTest, DisplaysMessageWhenBranchIdScanned)
{
    EXPECT_CALL(*display, showMessage(ScannerStateCheckout::MSG_COMPLETE_CHECKOUT_FIRST));

    state->scanBranchCard(ScannerTestData::BRANCH_SOUTH_CARD);
}

TEST_F(ScannerStateCheckoutTest, DisplaysMessageWhenSameHoldingScannedTwice)
{
    InSequence forcesExpectationOrder;
    scanner->setPatronId(ScannerTestData::PATRON_JANE_CARD);
    checkout(ScannerTestData::PATRON_JANE_CARD, ScannerTestData::HOLDING_TRIAL_BARCODE);

    EXPECT_CALL(*holdingService(), existsWithBarcode(_)).WillOnce(Return(true));
    EXPECT_CALL(*holdingService(), isAvailable(_)).WillOnce(Return(false));
    EXPECT_CALL(*display, showMessage(ScannerStateCheckout::MSG_ALREADY_CHECKED_OUT));

    state->scanHolding(ScannerTestData::HOLDING_TRIAL_BARCODE);
}
