#include "Catalog.h"
#include "Holding.h"

#include <set>
#include <string>

using namespace std;

vector<Holding>* Catalog::mHoldings(NULL);

Catalog::Catalog() {}

Catalog::~Catalog() {}

vector<Holding>* Catalog::holdings()
{
    if (!mHoldings)
        mHoldings = new vector<Holding>();
    return mHoldings;
}

unsigned int Catalog::size() const
{
    return Catalog::holdings()->size();
}

void Catalog::add(Holding& holding)
{
    Catalog::holdings()->push_back(holding);
}

void Catalog::update(Holding& holding)
{
    vector<Holding>* holdings = Catalog::holdings();
    HoldingIterator it = find(holdings->begin(), holdings->end(), holding);
    // TODO: throw if not found? need a test!
    *it = holding;
}

void Catalog::findByClassification(
    const string& classification, set<Holding>& holdingsCollector) const
{
    vector<Holding> holdings = *Catalog::holdings();
    for (auto it = holdings.begin(); it != holdings.end(); it++)
        if (classification == it->classification())
            holdingsCollector.insert(*it);
}

bool Catalog::contains(const string& barcode) const {
    return find(Catalog::holdings()->begin(), Catalog::holdings()->end(), 
        Holding{barcode}) != Catalog::holdings()->end();

}

Holding Catalog::findByBarCode(const string& barcode) const
{
    return *find_if(Catalog::holdings()->begin(), Catalog::holdings()->end(), 
        [&](const Holding& h) { return barcode == h.barcode(); });

}

void Catalog::deleteAll()
{
    if (mHoldings)
    {
        delete mHoldings;
        mHoldings = NULL;
    }
}
