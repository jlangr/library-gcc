#include "Scanner.h"
#include "DisplayListener.h"
#include "ScannerStateCheckin.h"
#include "ScannerStateWaiting.h"
#include "BarcodeUtil.h"
#include "HoldingService.h"

#include <string>
#include <iostream>

using namespace std;

const string Scanner::INVENTORY_CARD_NUMBER("i999999");
const string Scanner::MSG_INVALID_BARCODE("Barcode not recognized.");

Scanner::Scanner(DisplayListener* display, service::HoldingService* holdingService)
    : mDisplay(display)
    , mBranchId("")
    , mCurrentState(0)
    , mPatronId("")
    , mHoldingService(holdingService) {
    setCurrentState(new ScannerStateWaiting(this));
}

Scanner::~Scanner() {
    if (mCurrentState) {
        delete mCurrentState;
    }
}

void Scanner::setCurrentState(ScannerState* state) {
    if (mCurrentState) {
        delete mCurrentState;
    }
    mCurrentState = state;
}

ScannerState* Scanner::currentState() {
    return mCurrentState;
}

void Scanner::scan(const std::string& barcode) {
    if (barcode == INVENTORY_CARD_NUMBER)
        currentState()->scanInventoryCard(INVENTORY_CARD_NUMBER);
    else if (BarcodeUtil::isBranchId(barcode))
        currentState()->scanBranchCard(barcode);
    else if (BarcodeUtil::isPatronId(barcode))
        currentState()->scanPatronCard(barcode);
    else if (BarcodeUtil::isHoldingBarcode(barcode))
        currentState()->scanHolding(barcode);
    else
        showMessage(MSG_INVALID_BARCODE);
}

void Scanner::setBranchId(const string& branchId) {
    mBranchId = branchId;
}

string Scanner::branchId() {
    return mBranchId;
}

void Scanner::setPatronId(const string& patronId) {
    mPatronId = patronId;
}

string Scanner::patronId() {
    return mPatronId;
}

void Scanner::showMessage(const std::string& message) {
    mDisplay->showMessage(message);
}

void Scanner::pressDone() {
    currentState()->pressDone();
}

service::HoldingService* Scanner::holdingService() {
    return mHoldingService;
}
