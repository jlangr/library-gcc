#ifndef STOCK_SERVICE_H
#define STOCK_SERVICE_H

#include <string>

class StockService
{
public:
    virtual unsigned int currentPrice(const std::string& symbol)=0;
};

#endif
