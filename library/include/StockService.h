#ifndef STOCK_SERVICE_H
#define STOCK_SERVICE_H

#include <string>

class StockService
{
public:
    virtual unsigned int CurrentPrice(const std::string& symbol)=0;
};
