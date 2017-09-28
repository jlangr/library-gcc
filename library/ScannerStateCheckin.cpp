#include "ScannerStateCheckin.h"
#include "ScannerStateCheckout.h"
#include "ScannerStateInventory.h"
#include "Scanner.h"
#include "HoldingService.h"
#include "TimestampSource.h"

#include "boost/date_time/gregorian/gregorian_types.hpp"
#include <string>
#include <iostream>

using namespace std;
using namespace boost::gregorian;

const string ScannerStateCheckin::MSG_WAITING_FOR_RETURNS("Waiting for returns");

ScannerStateCheckin::ScannerStateCheckin(Scanner* scanner)
    : ScannerState(scanner) {}

ScannerStateCheckin::~ScannerStateCheckin(void) {}

void ScannerStateCheckin::pressDone() {
    showMessage(ScannerStateCheckin::MSG_WAITING_FOR_RETURNS);
}

void ScannerStateCheckin::scanHolding(const string& barcode) {
    holdingService()->checkIn(barcode, TimestampSource::now(), branchId());
}

void ScannerStateCheckin::scanBranchCard(const string& branchId) {
    setBranchId(branchId);
}

void ScannerStateCheckin::scanPatronCard(const string& patronId) {
    setPatronId(patronId);
    setState<ScannerStateCheckout>();
}

void ScannerStateCheckin::scanInventoryCard(const string&) {
    setState<ScannerStateInventory>();
}
