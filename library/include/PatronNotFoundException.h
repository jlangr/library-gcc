#ifndef PATRON_NOT_FOUND_EXCEPTION_H
#define PATRON_NOT_FOUND_EXCEPTION_H

#include <exception>

class PatronNotFoundException: public std::exception {
public:
    PatronNotFoundException(void) {}
    ~PatronNotFoundException() {};
};

#endif
