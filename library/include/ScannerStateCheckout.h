#ifndef SCANNER_STATE_CHECKOUT_H
#define SCANNER_STATE_CHECKOUT_H

#include "ScannerState.h"

class Scanner;

#include <string>

class ScannerStateCheckout : public ScannerState
{
public:
    ScannerStateCheckout(Scanner*);
    ~ScannerStateCheckout(void);

    virtual void scanHolding(const std::string& barcode);
    virtual void scanBranchCard(const std::string& barcode);
    virtual void scanInventoryCard(const std::string& barcode);
    virtual void scanPatronCard(const std::string& barcode);
    virtual void pressDone();
    
    static const std::string MSG_COMPLETE_CHECKOUT_FIRST;
    static const std::string MSG_SCANNED_HOLDING;
    static const std::string MSG_INVALID_HOLDING_ID;
    static const std::string MSG_ALREADY_CHECKED_OUT;
private:
    Scanner* mScanner;
};

#endif
