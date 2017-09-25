#ifndef SCANNER_STATE_INVENTORY_H
#define SCANNER_STATE_INVENTORY_H

#include <string>

#include "ScannerState.h"

class Scanner;

class ScannerStateInventory: public ScannerState
{
public:
    ScannerStateInventory(Scanner*);
    ~ScannerStateInventory(void);

    void scanHolding(const std::string&);
    void scanPatronCard(const std::string&);
    void scanInventoryCard(const std::string&);
    void scanBranchCard(const std::string&);
    void pressDone();

    static const std::string MSG_COMPLETE_INVENTORY;
    static const std::string MSG_BRANCH_CHANGED;
    static const std::string MSG_HOLDING_ADDED;
};

#endif
