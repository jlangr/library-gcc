#ifndef Account_H
#define Account_H

#include <string>
#include <vector>
#include <sstream>

class Account {
public:
    int balance() { return _balance; }

    void log(int oldBalance, int newBalance) {
        std::stringstream s;
        s << "previous balance: " << oldBalance << " / new balance " << newBalance;
        _logMessages.push_back(s.str());
    }

    void deposit(int amount) {
        auto newBalance = _balance + amount;
        log(_balance, newBalance);
        _balance = newBalance;
    }

private:
    int _balance{0};
    std::vector<std::string> _logMessages;
};

#endif
