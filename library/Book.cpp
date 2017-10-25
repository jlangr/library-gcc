#include "Book.h"

using std::string;

Book::Book() : mYear(0) {}

Book::Book(
    const string& title,
    const string& author,
    const unsigned int year,
    const string& classification,
    unsigned int type)
    : mTitle(title)
    , mAuthor(author)
    , mClassification(classification)
    , mYear(year)
    , mType(type) {}

Book::~Book() {}

Book& Book::operator=(const Book& rhs) {
    if (this == &rhs) return *this;

    mTitle = rhs.mTitle;
    mAuthor = rhs.mAuthor;
    mYear = rhs.mYear;
    mClassification = rhs.mClassification;
    mType = rhs.mType;

    return *this;
}

bool Book::operator==(const Book& other) const {
    return mTitle == other.mTitle &&
        mAuthor == other.mAuthor &&
        mYear == other.mYear &&
        mClassification == other.mClassification &&
        mType == other.mType;
}

bool Book::operator!=(const Book& other) const {
    return !(*this == other);
}

bool Book::operator<(const Book& rhs) const {
    return mClassification < rhs.mClassification;
}

unsigned int Book::year() const {
    return mYear;
}

string Book::classification() const {
    return mClassification;
}

string Book::title() const {
    return mTitle;
}

string Book::author() const {
    return mAuthor;
}

unsigned int Book::type() const {
    return mType;
}
