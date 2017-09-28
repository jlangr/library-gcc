#ifndef BARCODE_UTIL_H
#define BARCODE_UTIL_H

#include <string>
#include <ctype.h>

using std::string;

class BarcodeUtil {
public:
    BarcodeUtil(void) {}
    ~BarcodeUtil(void) {}

    static bool isBranchId(const string& barcode) {
        return toupper(barcode[0]) == 'B';
    }

    static bool isPatronId(const string& barcode) {
        return toupper(barcode[0]) == 'P';
    }

    static bool isHoldingBarcode(const string& barcode) {
        return barcode.find(":") != string::npos;
    }
};

#endif
