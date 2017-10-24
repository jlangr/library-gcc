#ifndef Portfolio_h
#define Portfolio_h

#include <string>
#include <set>
#include <unordered_map>

#include "StockService.h"

using namespace std;

class Portfolio {
public:
    Portfolio(StockService* service)
        : _service{service} {}

    bool empty() {
        return 0 == uniqueSymbolCount();
    }

    void purchase(const string& symbol, unsigned int someShares) {
        throwsOnNonPositiveShares(someShares);
        _holdings[symbol] = shares(symbol) + someShares;
    }

    unsigned int uniqueSymbolCount() const {
        return _holdings.size();
    }

    unsigned int shares(const string& symbol) const {
        if (0 == _holdings.count(symbol))
            return 0;
        return _holdings.at(symbol);
    }

    unsigned int value() const {
        auto total{0};
        for_each(_holdings.begin(), _holdings.end(),
                [&](pair<string, unsigned int> holding) {
                    auto symbol{holding.first};
                    auto shares{holding.second};
                    total += _service->currentPrice(symbol) * shares;
                });
        return total;
    }

private:
    unordered_map<string, unsigned int> _holdings;
    StockService* _service{nullptr};

    void throwsOnNonPositiveShares(unsigned int shares) const {
        if (0 == shares) throw runtime_error("zeroshares");
    }

};

#endif
