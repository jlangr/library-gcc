#ifndef SCANNER_H
#define SCANNER_H

#include <string>

#include "HoldingService.h"

class DisplayListener;
class ScannerState;

class Scanner {
public:
    const static std::string INVENTORY_CARD_NUMBER;
    const static std::string MSG_INVALID_BARCODE;

    Scanner(DisplayListener*, service::HoldingService*);
    virtual ~Scanner();

	void scan(const std::string& barcode);
	void pressDone();

    void showMessage(const std::string& message);
    ScannerState* currentState();
    void setCurrentState(ScannerState* state);

    std::string branchId();
    void setBranchId(const std::string&);
    std::string patronId();
    void setPatronId(const std::string&);

    service::HoldingService* holdingService();

private:
    DisplayListener* mDisplay;
    std::string mBranchId;
    ScannerState* mCurrentState;
    std::string mPatronId;
    service::HoldingService* mHoldingService;
};

#endif
