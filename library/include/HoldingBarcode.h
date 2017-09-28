#ifndef HOLDING_BARCODE_H
#define HOLDING_BARCODE_H

#include <string>
#include <sstream>

class HoldingBarcode {
public:
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
