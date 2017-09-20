#include "Catalog.h"
#include "Holding.h"

#include <set>
#include <string>

using namespace std;

vector<Holding>* Catalog::mHoldings(NULL);

Catalog::Catalog()
{
}

Catalog::~Catalog()
{
}

vector<Holding>* Catalog::Holdings()
{
    if (!mHoldings)
    {
        mHoldings = new vector<Holding>();
    }
    return mHoldings;
}

unsigned int Catalog::Size() const
{
    return Catalog::Holdings()->size();
}

void Catalog::Add(Holding& holding)
{
    Catalog::Holdings()->push_back(holding);
}

void Catalog::Update(Holding& holding)
{
  std::cout << "updating holding, available:" << holding.IsAvailable() << std::endl;
    vector<Holding>* holdings = Catalog::Holdings();
    HoldingIterator it = find(holdings->begin(), holdings->end(), holding);
    // TODO: throw if not found? need a test!
    *it = holding;

    auto h{FindByBarCode(holding.Barcode())};
  std::cout << "found holding, available:" << h.IsAvailable() << std::endl;
}

void Catalog::FindByClassification(
    const string& classification, set<Holding>& holdingsCollector) const
{
    vector<Holding> holdings = *Catalog::Holdings();
    for (auto it = holdings.begin(); it != holdings.end(); it++)
    {
        if (classification == it->Classification())
        {
            holdingsCollector.insert(*it);
        }
    }
}

bool Catalog::Contains(const string& barcode) const {
    // TODO condense this~
    Holding holding(barcode);
    vector<Holding>* holdings = Catalog::Holdings();
    auto it = find(holdings->begin(), holdings->end(), holding);
    if (it == Catalog::Holdings()->end())
        return false;
    return true;
}

// TODO simplify, can we use lambdas?
Holding Catalog::FindByBarCode(const string& barcode) const
{
    Holding holding(barcode);
    vector<Holding>* holdings = Catalog::Holdings();
    return *find(holdings->begin(), holdings->end(), holding);
}

void Catalog::DeleteAll()
{
    if (mHoldings)
    {
        delete mHoldings;
        mHoldings = NULL;
    }
}
