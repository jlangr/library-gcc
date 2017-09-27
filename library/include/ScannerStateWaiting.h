#ifndef SCANNER_STATE_WAITING_H
#define SCANNER_STATE_WAITING_H

#include <string>

#include "ScannerState.h"

class Scanner;

class ScannerStateWaiting: public ScannerState {
public:
    const static std::string MSG_SCAN_BRANCH_ID_FIRST;

    ScannerStateWaiting(Scanner*);
    ~ScannerStateWaiting(void);

    void scanHolding(const std::string&);
    void scanPatronCard(const std::string&);
    void scanInventoryCard(const std::string&);
    void scanBranchCard(const std::string&);
    void pressDone();

private:
    Scanner* mScanner;

    void showInvalidOperationMessage();
};

#endif
