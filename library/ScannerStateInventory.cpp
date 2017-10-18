#include "ScannerStateInventory.h"

#include "Scanner.h"
#include "ScannerStateCheckin.h"

#include <string>
#include <sstream>

using namespace std;

const string ScannerStateInventory::MSG_COMPLETE_INVENTORY("Please complete inventory first.");
const string ScannerStateInventory::MSG_BRANCH_CHANGED("Branch changed to ");
const string ScannerStateInventory::MSG_HOLDING_ADDED("Added holding ");

ScannerStateInventory::ScannerStateInventory(Scanner* scanner)
    : ScannerState(scanner) {}

ScannerStateInventory::~ScannerStateInventory(void) {}

void ScannerStateInventory::scanHolding(const string& barcode) {
    holdingService()->addAtBranch(branchId(), barcode);

    showMessage(ScannerStateInventory::MSG_HOLDING_ADDED + barcode);
}

void ScannerStateInventory::scanPatronCard(const string&) {
    showMessage(ScannerStateInventory::MSG_COMPLETE_INVENTORY);
}

void ScannerStateInventory::scanInventoryCard(const string&) {
    showMessage(ScannerStateInventory::MSG_COMPLETE_INVENTORY);
}

void ScannerStateInventory::scanBranchCard(const string& branchId) {
    setBranchId(branchId);
    showMessage(ScannerStateInventory::MSG_BRANCH_CHANGED + branchId);
}

void ScannerStateInventory::pressDone() {
    setState<ScannerStateCheckin>();
}
