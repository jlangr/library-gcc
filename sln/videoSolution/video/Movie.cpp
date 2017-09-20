#include <string>

#include "Movie.h"
#include "PriceCode.h"
#include "Price.h"

Movie::Movie(const std::string& title, int priceCode)
	: mTitle(title)
    , mPrice(0)
{
    setPriceCode(priceCode);
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
	return mPrice->Code();
}

void Movie::setPriceCode(int priceCode)
{
    if (mPrice)
        delete mPrice;
    
    mPrice = CreatePrice(priceCode);
}

Price* Movie::CreatePrice(int priceCode)
{
    switch(priceCode)
    {
        case PriceCode::NEW_RELEASE:
            return new NewRelease();

        case PriceCode::CHILDRENS:
            return new Childrens();

        case PriceCode::REGULAR:
        default:
            return new Regular();
    }
}

double Movie::Charge(int daysRented) const
{
    return mPrice->Charge(daysRented);
}
