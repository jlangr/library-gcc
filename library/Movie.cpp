#include "Movie.h"
#include <string>
#include "PriceCode.h"

Movie::Movie(const std::string& title, int priceCode)
	: mTitle(title)
	, mPriceCode(priceCode)
{
}

Movie::~Movie()
{
}

std::string Movie::title() const
{
	return mTitle;
}

int Movie::priceCode() const
{
	return mPriceCode;
}

void Movie::setPriceCode(int priceCode)
{
   mPriceCode = priceCode;
}
