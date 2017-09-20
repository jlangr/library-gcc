#pragma once

#include <string>
#include <exception>

#include "StockService.h"

using namespace std;

class InvalidSharesException : public exception {};

class Portfolio
{
public:
    Portfolio() {}
    ~Portfolio() {}

    void SetStockService(StockService* stockService)
    {
        this->stockService = stockService;
    }

    size_t Size() const {
        return holdings.size();
    }

    void Purchase(const string& symbol, unsigned int shareCount) {
        if ("" == symbol) throw 1;
        if (0 == shareCount) throw InvalidSharesException();
        holdings[symbol] = Shares(symbol) + shareCount;
    }

    unsigned int Shares(const string& symbol) const
    {
        auto it{ holdings.find(symbol) };
        if (it == holdings.end())
            return 0;
        return it->second;
    }

    unsigned int Value() const
    {
        unsigned int total{ 0 };
        for (auto pair : holdings) {
            auto symbol{ pair.first };
            auto shares{ pair.second };
            total += shares * stockService->CurrentPrice(symbol);
        }
        return total;
    }

private:
    map<string, unsigned int> holdings;
    StockService* stockService;
};