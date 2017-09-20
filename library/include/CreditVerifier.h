#ifndef CREDIT_VERIFIER_H
#define CREDIT_VERIFIER_H

#include <string>

class CreditVerifier
{
public:
    virtual bool Verify(const std::string& cardNumber) = 0;
};

#endif
