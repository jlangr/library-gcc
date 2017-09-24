#include "HoldingService.h"
#include "Branch.h"
#include "Book.h"
#include "Patron.h"
#include "PatronService.h"
#include "BranchService.h"
#include "ClassificationService.h"

#include <set>
#include "boost/date_time/gregorian/gregorian_types.hpp"

using namespace std;
using boost::gregorian::date;
using namespace service;

HoldingService::HoldingService()
{
}

HoldingService::~HoldingService()
{
}

void HoldingService::DeleteAll()
{
    Catalog::deleteAll();
}

unsigned int HoldingService::InventorySize() const
{
    return mCatalog.size();
}

void HoldingService::FindByClassification(const string& classification, set<Holding>& holdings) const
{
    mCatalog.findByClassification(classification, holdings);
}

bool HoldingService::ExistsWithBarcode(const std::string& barcode) const
{
    return mCatalog.contains(barcode);
}

bool HoldingService::IsAvailable(const std::string& barcode) const
{
    return mCatalog.contains(barcode) && FindByBarCode(barcode).IsAvailable();
}

Holding HoldingService::FindByBarCode(const std::string& barcode) const
{
    return mCatalog.findByBarCode(barcode);
}

void HoldingService::AddAtBranch(const string& id, const string& barcode)
{
    Branch branch(id);
    mBranchService.find(branch);

    Holding holding(barcode);
    mCatalog.add(holding);
    Transfer(holding, branch);
}

void HoldingService::Transfer(Holding& holding, Branch& branch)
{
    holding.Transfer(branch);
    mCatalog.update(holding);
}

void HoldingService::Transfer(const string& barcode, const string& branchId)
{
    Branch branch(branchId);
    mBranchService.find(branch);

    auto holding = FindByBarCode(barcode);
    holding.Transfer(branch);
    mCatalog.update(holding);
}

void HoldingService::CheckOut(const string& patronCardNumber, const string& barcode, date date)
{
    auto holding = FindByBarCode(barcode);
    holding.CheckOut(date);
    mCatalog.update(holding);

    Patron patron("", patronCardNumber);
    mPatronService.Find(patron);

    patron.Borrow(holding);
    mPatronService.Update(patron);
}

void HoldingService::CheckIn(const string& barCode, date date, const string& branchId)
{
    Branch branch(branchId);
    mBranchService.find(branch);

    auto hld = FindByBarCode(barCode);

    vector<Patron> patrons;

    // set the holding to returned status
    set<Holding> holdings;
    hld.CheckIn(date, branch);
    mCatalog.update(hld);

    patrons = mPatronService.GetAll();

    Holding patHld;

    // locate the patron with the checked out book
    // could introduce a patron reference ID in the holding...
    Patron f;
    Patron p;
    vector<Patron>::const_iterator it;
    for (it = patrons.begin();
        it != patrons.end();
        it++)
    {
        p = *it;
        holdings = p.Holdings();
        set<Holding>::const_iterator it1;
        for (it1 = holdings.begin(); it1 != holdings.end(); it1++)
        {
            patHld = *it1;
            if (hld.Classification() == patHld.Classification())

                f = p;
        }
    }

    // remove the book from the patron
    f.ReturnHolding(hld);

    // check for late returns
    bool isLate = false;

    if (date > hld.DueDate()) // is it late?
        isLate = true;

    if (isLate) {
        int daysLate = 1; // calculate # of days past due

        ClassificationService service;
        Book book = service.retrieveDetails(hld.Classification());

        switch (book.type()) {
            case Book::TYPE_BOOK:
                f.AddFine(Book::BOOK_DAILY_FINE * daysLate);
                break;
            case Book::TYPE_MOVIE:
            {
                int fine = 100 + Book::MOVIE_DAILY_FINE * daysLate;
                if (fine > 1000)
                    fine = 1000;
                f.AddFine(fine);
            }
            break;
            case Book::TYPE_NEW_RELEASE:
                f.AddFine(Book::NEW_RELEASE_DAILY_FINE * daysLate);
                break;
        }
    }
    mPatronService.Update(f);
}
