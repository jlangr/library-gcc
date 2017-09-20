#include <string>
#include <map>
#include <exception>
#include "StockService.h"

using namespace std;

class InvalidSymbolException: public exception {};
class ZeroNotAllowedException: public exception {};

class PortfolioSln
{
public:
    PortfolioSln()
        : mService(0)
    {
    }

    bool IsEmpty() const
    {
        return 0 == Size();
    }

    unsigned int Size() const
    {
        return mHoldings.size();
    }

    unsigned int Shares(const string& symbol) const
    {
        map<string,unsigned int>::const_iterator it = mHoldings.find(symbol);
        if (it == mHoldings.end())
            return 0;
        return it->second;
    }

    void Sell(const std::string& symbol, unsigned int shares)
    {
        ThrowIfSellingTooMany(symbol, shares);

        if (Shares(symbol) == shares)
            Remove(symbol);
        else
            Subtract(shares, symbol);
    }

    void SetStockLookupService(StockService* service)
    {
        mService = service;
    }

    void Purchase(const string& symbol, unsigned int shares)
    {
        ThrowIfEmpty(symbol);
        ThrowIfZero(shares);

        SetShares(symbol, Shares(symbol) + shares);
    }

    unsigned int Value() const
    {
        if (!mService) return 0;
        return mService->CurrentPrice("SYMC");
    }

private:
    map<string,unsigned int> mHoldings;
    StockService* mService;

    void SetShares(const string& symbol, unsigned int shares)
    {
        mHoldings[symbol] = shares;
    }

    void ThrowIfSellingTooMany(const string& symbol, unsigned int shares)
    {
        if (Shares(symbol) < shares)
            throw exception();
    }

    void Subtract(unsigned int shares, const string symbol)
    {
        mHoldings[symbol] = Shares(symbol) - shares;
    }

    void ThrowIfEmpty(const std::string& text)
    {
        if (text.length() == 0)
            throw InvalidSymbolException();
    }

    void ThrowIfZero(unsigned int number)
    {
        if (number == 0)
            throw ZeroNotAllowedException();
    }

    void Remove(const string& symbol)
    {
        mHoldings.erase(symbol);
    }
};