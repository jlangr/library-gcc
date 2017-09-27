#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include "PriceCode.h"

class Movie {
public:
	explicit Movie(const std::string& title, int priceCode);
	virtual ~Movie();
	std::string title() const;
	int priceCode() const;
   void setPriceCode(int priceCode);

private:
	std::string mTitle;
	int mPriceCode;
};

#endif
