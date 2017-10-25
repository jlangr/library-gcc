#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ASSERT_CURRENT_STATE.h"

#include <string>

#include "Scanner.h"
#include "ScannerTestData.h"
#include "ScannerState.h"
#include "ScannerStateWaiting.h"
#include "TestScanner.h"
#include "DisplayListener.h"
#include "HoldingService.h"

using namespace std;
using namespace testing;

class MockState: public ScannerState {
public:
    MockState() : ScannerState(NULL) {}
    MOCK_METHOD0(pressDone, void());
    MOCK_METHOD1(scanHolding, void(const std::string& barcode));
    MOCK_METHOD1(scanBranchCard, void(const std::string& barcode));
    MOCK_METHOD1(scanInventoryCard, void(const std::string& barcode));
    MOCK_METHOD1(scanPatronCard, void(const std::string& barcode));
};

class ScannerTest : public Test, public TestScanner {
public:
    Scanner* scanner;
    MockState* state;
    MockDisplayListener* display;

    void SetUp() {
        display = new MockDisplayListener();
        scanner = new Scanner(display, NULL);
        state = new MockState();
        scanner->setCurrentState(state);
    }

    void TearDown() {
        delete scanner;
        delete display;
    }
};

TEST_F(ScannerTest, IsInWaitingModeByDefault) {
    Scanner scanner(NULL, NULL);

    ASSERT_CURRENT_STATE<ScannerStateWaiting>(scanner);
}

TEST_F(ScannerTest, PressDoneDelegatesToAppropriateState) {
    EXPECT_CALL(*state, pressDone());

    scanner->pressDone();
}

TEST_F(ScannerTest, ScanHoldingDelegatesToAppropriateState) {
    string barcode("A123:1");
    EXPECT_CALL(*state, scanHolding(barcode));

    scanner->scan(barcode);
}

TEST_F(ScannerTest, ScanInventoryCardDelegatesToAppropriateState) {
    EXPECT_CALL(*state, scanInventoryCard(Scanner::INVENTORY_CARD_NUMBER));

    scanner->scan(Scanner::INVENTORY_CARD_NUMBER);
}

TEST_F(ScannerTest, ScanBranchCardDelegatesToAppropriateState) {
    EXPECT_CALL(*state, scanBranchCard(ScannerTestData::BRANCH_SOUTH_CARD));

    scanner->scan(ScannerTestData::BRANCH_SOUTH_CARD);
}

TEST_F(ScannerTest, ScanPatronCardDelegatesToAppropriateState) {
    EXPECT_CALL(*state, scanPatronCard(ScannerTestData::PATRON_JANE_CARD));

    scanner->scan(ScannerTestData::PATRON_JANE_CARD);
}

TEST_F(ScannerTest, ScanUnrecognizedIdDisplaysMessage) {
    EXPECT_CALL(*display, showMessage(Scanner::MSG_INVALID_BARCODE));

    scanner->scan("234");
}
