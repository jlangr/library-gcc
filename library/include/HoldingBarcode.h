#ifndef HOLDING_BARCODE_H
#define HOLDING_BARCODE_H

#include <string>
#include <sstream>
#include <cstdlib>

#include "StringUtil.h"
#include "InvalidBarcodeException.h"

class HoldingBarcode {
public:
    HoldingBarcode(const std::string& barcode) {
        if (barcode.find(":") == std::string::npos) {
            throw InvalidBarcodeException();
        }
        std::vector<std::string> barcodeParts = stringutil::split(barcode, ':');
        std::string classification = barcodeParts[0];
        mCopyNumber = atoi(barcodeParts[1].c_str());
        mClassification = classification;
    }

    HoldingBarcode(const std::string& classification, unsigned int copyNumber) 
        : mClassification(classification)
        , mCopyNumber(copyNumber) {}
    
    ~HoldingBarcode(void) {}

    std::string asString() const {
        std::stringstream buffer;
        buffer << mClassification << ":" << mCopyNumber;
        return buffer.str();
    }

    std::string classification() const { 
        return mClassification; 
    }
    
    unsigned int copyNumber() const { 
        return mCopyNumber; 
    }

private:
    std::string mClassification;
    unsigned int mCopyNumber;
};

#endif
