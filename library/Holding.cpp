#include "Holding.h"
#include "Book.h"
#include "Branch.h"
#include "ClassificationService.h"
#include "InvalidBarcodeException.h"
#include "StringUtil.h"

#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "boost/date_time/gregorian/gregorian_types.hpp"

using namespace boost::gregorian;
using namespace std;

Holding::Holding(const string& barcode)
    : mBranch(Branch::CHECKED_OUT)
    , mLastCheckedOutOn()
{
    if (barcode.find(":") == string::npos)
    {
        throw InvalidBarcodeException();
    }
    vector<string> barcodeParts = stringutil::split(barcode, ':');
    string classification = barcodeParts[0];
    mCopyNumber = atoi(barcodeParts[1].c_str());
    mClassification = classification;
}

Holding::Holding(const string& classification, unsigned short copyNumber)
    : mClassification(classification)
    , mCopyNumber(copyNumber)
    , mBranch(Branch::CHECKED_OUT)
    , mLastCheckedOutOn()
{
}

Holding::Holding()
    : mClassification("")
    , mCopyNumber(1)
    , mBranch(Branch::CHECKED_OUT)
    , mLastCheckedOutOn()
{
}

Holding::~Holding()
{
}

bool Holding::operator==(const Holding& rhs) const
{
    return barcode() == rhs.barcode();
}

bool Holding::operator<(const Holding& rhs) const
{
    return barcode() < rhs.barcode();
}

bool Holding::operator!=(const Holding& rhs) const
{
    return !(*this == rhs);
}

string Holding::classification() const
{
    return mClassification;
}

unsigned short Holding::copyNumber() const
{
    return mCopyNumber;
}

Branch Holding::currentBranch() const
{
    return mBranch;
}

void Holding::transfer(Branch& branch)
{
    mBranch = branch;
}

string Holding::barcode() const
{
    return Holding::constructBarcode(mClassification, mCopyNumber);
}

/* static */ string Holding::constructBarcode(
    const string& classification, const int& copyNumber)
{
    stringstream buffer;
    buffer << classification << ":" << copyNumber;
    return buffer.str();
}

void Holding::checkOut(date checkOutDate)
{
    mLastCheckedOutOn = checkOutDate;
    mBranch = Branch::CHECKED_OUT;
}

void Holding::checkIn(date checkInDate, const Branch& branch)
{
    mBranch = branch;
}

date Holding::lastCheckedOutOn() const
{
    return mLastCheckedOutOn;
}

date Holding::dueDate() const
{
    // should this go into HoldingService?

    // figure out how long the book can be held
    int period = 0;

    ClassificationService svc;
    Book book = svc.retrieveDetails(mClassification);
    switch (book.type()) {
        case Book::TYPE_BOOK:
            period = Book::BOOK_CHECKOUT_PERIOD;
            break;
        case Book::TYPE_MOVIE:
            period = Book::MOVIE_CHECKOUT_PERIOD;
            break;
        case Book::TYPE_NEW_RELEASE:
            period = Book::NEW_RELEASE_CHECKOUT_PERIOD;
            break;
        default:
            period = Book::BOOK_CHECKOUT_PERIOD;
            break;
    }
    return mLastCheckedOutOn + date_duration(period);
}

bool Holding::isAvailable() const
{
    return Branch::CHECKED_OUT != mBranch;
}
