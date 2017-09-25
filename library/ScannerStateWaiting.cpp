#include "ScannerStateWaiting.h"
#include "ScannerStateCheckin.h"
#include "Scanner.h"

#include <string>

using namespace std;

const string ScannerStateWaiting::MSG_SCAN_BRANCH_ID_FIRST("Please scan a branch ID before continuing.");

ScannerStateWaiting::ScannerStateWaiting(Scanner* scanner)
    : ScannerState(scanner)
{
}

ScannerStateWaiting::~ScannerStateWaiting(void)
{
}

void ScannerStateWaiting::scanBranchCard(const string& branchId) 
{
    setState<ScannerStateCheckin>();
    setBranchId(branchId);
}

void ScannerStateWaiting::scanHolding(const string&)
{
    showInvalidOperationMessage();
}

void ScannerStateWaiting::scanPatronCard(const string&)
{
    showInvalidOperationMessage();
}

void ScannerStateWaiting::scanInventoryCard(const string&)
{
    showInvalidOperationMessage();
}

void ScannerStateWaiting::pressDone() 
{
    showInvalidOperationMessage();
}

void ScannerStateWaiting::showInvalidOperationMessage()
{
    showMessage(ScannerStateWaiting::MSG_SCAN_BRANCH_ID_FIRST);
}
