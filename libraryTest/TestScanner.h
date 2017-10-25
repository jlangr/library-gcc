#pragma once

#include "gmock/gmock.h"

#include "Scanner.h"
#include "ScannerState.h"
#include "DisplayListener.h"
#include "Holding.h"
#include "HoldingService.h"

#include "boost/date_time/gregorian/gregorian_types.hpp"
#include <string>

class MockDisplayListener: public DisplayListener {
public:
    virtual ~MockDisplayListener() {}
    MOCK_METHOD1(showMessage, void(const std::string& text));
};

class MockHoldingService: public service::HoldingService {
public:
    MOCK_METHOD3(checkIn, void(const std::string& barCode, boost::gregorian::date, const std::string& branchId));
    MOCK_METHOD3(checkOut, void(const std::string& patronCardNumber, const std::string& barCode, boost::gregorian::date));
    MOCK_CONST_METHOD1(existsWithBarcode, bool(const std::string& barCode));
    MOCK_CONST_METHOD1(isAvailable, bool(const std::string& barCode));
    MOCK_METHOD2(addAtBranch, void(const std::string& branchId, const std::string& barcode));
};

class TestScanner {
public:
    Scanner* scanner;
    MockDisplayListener* display;
    MockHoldingService* _holdingService;

    TestScanner() {
        display = new MockDisplayListener;
        _holdingService = new MockHoldingService;
        scanner = new Scanner(display, _holdingService);
    }

    virtual ~TestScanner() {
        delete scanner;
        delete _holdingService;
        delete display;
    }

    MockHoldingService* holdingService() {
         return dynamic_cast<MockHoldingService*>(scanner->holdingService());
    }
};
