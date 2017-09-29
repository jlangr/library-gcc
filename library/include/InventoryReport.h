#ifndef INVENTORY_REPORT_H
#define INVENTORY_REPORT_H

#include "Catalog.h"
#include "Book.h"

#include "Catalog.h"
#include "Book.h"

#include <string>
#include <exception>
#include <sstream>

class LibraryOfCongressAPI {
public:
    virtual std::string GetISBN(const std::string& classification) {
        throw std::runtime_error(std::string{"connection currently unavailable, please try later"});
    }
};

struct Record
{
    Record(Book book, const std::string& branchName, LibraryOfCongressAPI* isbnApi)
        : title(book.title())
        , branch(branchName)
        , author(book.author())
        , year(book.year()) {
        isbn = isbnApi->GetISBN(book.classification());
    }

    bool operator<(const Record& rhs) const {
        if (author != rhs.author) 
            return author < rhs.author;
        if (year != rhs.year) 
            return year < rhs.year;
        return title < rhs.title;
    }

    std::string title;
    std::string branch;
    std::string author;
    unsigned short year;
    std::string isbn;
};

class InventoryReport {
public:
    static const std::string NEWLINE;
    static const unsigned int SPACING;
    static const unsigned int TITLE_LENGTH;
    static const unsigned int BRANCH_LENGTH;
    static const unsigned int AUTHOR_LENGTH;
    static const unsigned int YEAR_LENGTH;
    static const unsigned int ISBN_LENGTH;
    
    InventoryReport(Catalog*);
    ~InventoryReport(void);
    std::string generate();
    void appendHeader(std::stringstream&);
    void appendColumnHeaders(std::stringstream&);
    void append(std::stringstream&, Record&);
    std::string underlines(unsigned int count, unsigned int spacing);
    std::string pad(unsigned int totalLength, const std::string& text="");
private:
    Catalog* mCatalog;
    LibraryOfCongressAPI mIsbnApi;
};

#endif
