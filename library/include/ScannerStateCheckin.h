#ifndef SCANNER_STATE_CHECKIN_H
#define SCANNER_STATE_CHECKIN_H

#include <string>

#include "Scanner.h"
#include "ScannerState.h"

class ScannerStateCheckin: public ScannerState {
public:
    ScannerStateCheckin(Scanner*);
    virtual ~ScannerStateCheckin(void);

    void pressDone();
    void scanHolding(const std::string&);
    void scanPatronCard(const std::string&);
    void scanInventoryCard(const std::string&);
    void scanBranchCard(const std::string&);

    static const std::string MSG_WAITING_FOR_RETURNS;

private:
    Scanner* mScanner;
};

#endif
