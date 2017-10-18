#ifndef HOLDING_H
#define HOLDING_H

#include "Branch.h"

#include <string>
#include <vector>

#include "boost/date_time/gregorian/gregorian_types.hpp"

enum class Condition : int { New = 0, Read = 1, Damaged = 2 };

class Holding {
public:
    Holding();
    explicit Holding(const std::string& barcode);
    Holding(const std::string& classification, unsigned short copyNumber);
    virtual ~Holding();

    static std::string constructBarcode(
        const std::string& classification, const int& copyNumber);

    bool operator==(const Holding& rhs) const;
    bool operator!=(const Holding& rhs) const;
    bool operator<(const Holding& rhs) const;

    Branch currentBranch() const;
    unsigned short copyNumber() const;
    std::string barcode() const;
    boost::gregorian::date lastCheckedOutOn() const;
    boost::gregorian::date dueDate() const;
    bool isAvailable() const;
    std::string classification() const;
    Condition condition() const;

    void transfer(Branch&);
    void checkOut(boost::gregorian::date);
    void checkIn(boost::gregorian::date, const Branch&);
    void updateCondition(Condition);

private:
    std::string mClassification;
    unsigned short mCopyNumber;
    Branch mBranch;
    boost::gregorian::date mLastCheckedOutOn;
    Condition mCondition{Condition::New};
};

typedef std::vector<Holding>::iterator HoldingIterator;

#endif
