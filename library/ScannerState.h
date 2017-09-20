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

    virtual void ScanHolding(const std::string& barcode)=0;
    virtual void ScanBranchCard(const std::string& barcode)=0;
    virtual void ScanInventoryCard(const std::string& barcode)=0;
    virtual void ScanPatronCard(const std::string& barcode)=0;
    virtual void PressDone()=0;

protected:
    template <typename T> void SetState();

    void ScannerState::ShowMessage(const std::string& message);
    std::string ScannerState::BranchId() const;
    void ScannerState::SetBranchId(const std::string& id);
    std::string ScannerState::PatronId() const;
    void ScannerState::SetPatronId(const std::string& id);
    service::HoldingService* ScannerState::HoldingService() const;

private:
    Scanner* mScanner;
};

template <typename T>
void ScannerState::SetState()
{
    mScanner->SetCurrentState(new T(mScanner));
}
