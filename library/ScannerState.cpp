#include "ScannerState.h"

#include "HoldingService.h"

using namespace std;

void ScannerState::showMessage(const string& message)
{
    mScanner->showMessage(message);
}

string ScannerState::branchId() const
{
    return mScanner->branchId();
}

void ScannerState::setBranchId(const string& id)
{
    mScanner->setBranchId(id);
}

string ScannerState::patronId() const
{
    return mScanner->patronId();
}

void ScannerState::setPatronId(const string& id)
{
    mScanner->setPatronId(id);
}

service::HoldingService* ScannerState::holdingService() const
{
    return mScanner->holdingService();
}
