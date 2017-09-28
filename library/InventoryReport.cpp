#include "InventoryReport.h"

#include "Catalog.h"
#include "Holding.h"
#include "ClassificationService.h"
#include "Book.h"
#include "Branch.h"

#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

const unsigned int InventoryReport::SPACING(2);
const unsigned int InventoryReport::TITLE_LENGTH(24);
const unsigned int InventoryReport::BRANCH_LENGTH(16);
const unsigned int InventoryReport::AUTHOR_LENGTH(24);
const unsigned int InventoryReport::YEAR_LENGTH(6);
const unsigned int InventoryReport::ISBN_LENGTH(10);

InventoryReport::InventoryReport(Catalog* catalog)
	: mCatalog(catalog)
	, mIsbnApi(new LibraryOfCongressAPI()) {}

InventoryReport::~InventoryReport(void) {
    delete mIsbnApi;
}

std::string InventoryReport::generate() {
    ClassificationService classificationService;

    vector<Record> records;

    vector<Holding>* holdings = Catalog::holdings();
    for (vector<Holding>::iterator it = holdings->begin();
        it != holdings->end();
        it++) {
        Holding holding = *it;
        Book book = classificationService.retrieveDetails(holding.classification());
        if (book.type() == Book::TYPE_BOOK) {
            Record record(book, holding.currentBranch().name(), mIsbnApi);
            records.push_back(record);
        }
    }

    sort(records.begin(), records.end());

    stringstream buffer;
    appendHeader(buffer);
    appendColumnHeaders(buffer);
    for (vector<Record>::iterator it = records.begin(); it != records.end();it++)
         append(buffer, *it);
    return buffer.str();
}

void InventoryReport::appendHeader(stringstream& buffer) {
    buffer << "Inventory" << endl;
    buffer << endl;
}

void InventoryReport::appendColumnHeaders(stringstream& buffer) {
    buffer << pad(TITLE_LENGTH + SPACING, "Title")
        << pad(BRANCH_LENGTH + SPACING, "Branch")
        << pad(AUTHOR_LENGTH + SPACING, "Author")
        << pad(YEAR_LENGTH + SPACING, "Year")
        << pad(ISBN_LENGTH + SPACING, "ISBN");
    buffer << endl;

    buffer << underlines(TITLE_LENGTH, SPACING);
    buffer << underlines(BRANCH_LENGTH, SPACING);
    buffer << underlines(AUTHOR_LENGTH, SPACING);
    buffer << underlines(YEAR_LENGTH, SPACING);
    buffer << underlines(ISBN_LENGTH, SPACING);
    buffer << endl;
}

void InventoryReport::append(stringstream& buffer, Record& record) {
    buffer << pad(TITLE_LENGTH, record.title);
    buffer << pad(SPACING);
    buffer << pad(BRANCH_LENGTH, record.branch);
    buffer << pad(SPACING);
    buffer << pad(AUTHOR_LENGTH, record.author);
    buffer << pad(SPACING);
    stringstream year;
    year << record.year;
    buffer << pad(YEAR_LENGTH, year.str());
    buffer << pad(SPACING);
    buffer << pad(ISBN_LENGTH, record.isbn);
    buffer << endl;
}

// TODO: copy over these better implementations to template project!
string InventoryReport::pad(unsigned int totalLength, const string& text) {
    //stringstream buffer(text, ios::out | ios::ate);
    return text + string(totalLength - text.length(), ' ');
}

string InventoryReport::underlines(unsigned int count, unsigned int spacing) {
    return pad(count + spacing, string(count, '-'));
}
