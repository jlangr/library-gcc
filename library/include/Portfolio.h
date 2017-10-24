#ifndef Portfolio_h
#define Portfolio_h

#include <string>
#include <set>
#include <unordered_map>

class Portfolio {
public:
    bool empty() {
        return 0 == uniqueSymbolCount();
    }

    void purchase(const std::string& symbol, unsigned int someShares) {
        throwsOnNonPositiveShares(someShares);
        _holdings[symbol] = shares(symbol) + someShares;
    }

    unsigned int uniqueSymbolCount() const {
        return _holdings.size();
    }

    unsigned int shares(const std::string& symbol) const {
        if (0 == _holdings.count(symbol))
            return 0;
        return _holdings.at(symbol);
    }

private:
    std::unordered_map<std::string, unsigned int> _holdings;

    void throwsOnNonPositiveShares(unsigned int shares) const {
        if (0 == shares) throw std::runtime_error("zeroshares");
    }
};

#endif
