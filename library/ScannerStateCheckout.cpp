#include "ScannerStateCheckout.h"

#include <string>

#include "Scanner.h"
#include "ScannerStateCheckin.h"
#include "TimestampSource.h"

using namespace std;

const string ScannerStateCheckout::MSG_COMPLETE_CHECKOUT_FIRST("Please complete checking out the current patron.");
const string ScannerStateCheckout::MSG_SCANNED_HOLDING("Checked out holding.");
const string ScannerStateCheckout::MSG_INVALID_HOLDING_ID("Holding barcode not recognized.");
const string ScannerStateCheckout::MSG_ALREADY_CHECKED_OUT("Holding already checked out.");

ScannerStateCheckout::ScannerStateCheckout(Scanner* scanner)
    : ScannerState(scanner)
{
}

ScannerStateCheckout::~ScannerStateCheckout(void)
{
}

void ScannerStateCheckout::pressDone()
{
    setState<ScannerStateCheckin>();
}

void ScannerStateCheckout::scanHolding(const string& barcode)
{
    if (!holdingService()->existsWithBarcode(barcode))
    {
        showMessage(ScannerStateCheckout::MSG_INVALID_HOLDING_ID);
        return;
    }

    if (!holdingService()->isAvailable(barcode))
    {
        showMessage(ScannerStateCheckout::MSG_ALREADY_CHECKED_OUT);
        return;
    }

    holdingService()->checkOut(patronId(), barcode, TimestampSource::Now());
    showMessage(ScannerStateCheckout::MSG_SCANNED_HOLDING);
}

void ScannerStateCheckout::scanBranchCard(const string& barcode)
{    
    showMessage(ScannerStateCheckout::MSG_COMPLETE_CHECKOUT_FIRST);
}

void ScannerStateCheckout::scanPatronCard(const string& patronId)
{
    showMessage(ScannerStateCheckout::MSG_COMPLETE_CHECKOUT_FIRST);
}

void ScannerStateCheckout::scanInventoryCard(const string&)
{
    showMessage(ScannerStateCheckout::MSG_COMPLETE_CHECKOUT_FIRST);
}
