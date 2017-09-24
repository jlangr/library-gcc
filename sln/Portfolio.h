#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <string>
#include <set>
#include <unordered_map>
#include <exception>
#include <numeric>

#include "StockService.h"

using namespace std;

class Portfolio {
public:
    bool empty() const {
        return 0 == size();
    }

    void purchase(const string& symbol, unsigned int shares) {
        if (0 == shares) throw std::runtime_error("hey");
        _holdings[symbol] = shares + this->shares(symbol);
    }

    size_t size() const {
        return _holdings.size();
    }

    unsigned int shares(const string& symbol) const {
        auto it{_holdings.find(symbol)};
        if (it == _holdings.end()) return 0;
        return it->second;
    }

    unsigned int value() const {
        return accumulate(_holdings.begin(), _holdings.end(), 0,
                [&](unsigned int total, pair<const string&, unsigned int> holding) {
                    auto symbol = holding.first;
                    return total + _stockService->currentPrice(symbol) * shares(symbol);
                    });
    }

    void stockService(StockService* service) {
        _stockService = service;
    }

private:
    unordered_map<std::string, unsigned int> _holdings;
    StockService* _stockService{nullptr};
};

#endif
