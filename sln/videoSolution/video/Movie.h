#ifndef D_Movie_h
#define D_Movie_h
#include <string>

#include "PriceCode.h"
#include "Price.h"

class Movie
{
public:
    explicit Movie(const std::string& title, int priceCode);
    virtual ~Movie();

    std::string title() const;
    Price* mPrice;
    int priceCode() const;
    void setPriceCode(int priceCode);
    double Charge(int daysRented) const;
    Price* CreatePrice(int priceCode);

private:
	std::string mTitle;
	int mPriceCode;
};

#endif  // D_Movie_h
