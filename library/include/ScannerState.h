#ifndef SCANNER_STATE_H
#define SCANNER_STATE_H

#include <string>

#include "HoldingService.h"
#include "Scanner.h"

class ScannerState
{
public:
    ScannerState(Scanner* scanner)
        : mScanner(scanner)
    {
    }

    virtual ~ScannerState()
    {
    }

    virtual void scanHolding(const std::string& barcode)=0;
    virtual void scanBranchCard(const std::string& barcode)=0;
    virtual void scanInventoryCard(const std::string& barcode)=0;
    virtual void scanPatronCard(const std::string& barcode)=0;
    virtual void pressDone()=0;

protected:
    template <typename T> void setState();

    void showMessage(const std::string& message);
    std::string branchId() const;
    void setBranchId(const std::string& id);
    std::string patronId() const;
    void setPatronId(const std::string& id);
    service::HoldingService* holdingService() const;

private:
    Scanner* mScanner;
};

template <typename T>
void ScannerState::setState()
{
    mScanner->setCurrentState(new T(mScanner));
}

#endif
