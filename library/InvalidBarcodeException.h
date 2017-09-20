#ifndef INVALID_BARCODE_EXCEPTION_H
#define INVALID_BARCODE_EXCEPTION_H

#include <exception>

class InvalidBarcodeException: public std::exception {
public:
    InvalidBarcodeException(void) {};
    ~InvalidBarcodeException() {};
};

#endif
