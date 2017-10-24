#ifndef CREDIT_VERIFIER_H
#define CREDIT_VERIFIER_H

#include <string>

class CreditVerifier {
public:
    static const unsigned int MinimumForGoodCredit{650};
    virtual unsigned int creditScore(const std::string& cardNumber) = 0;
};

#endif
