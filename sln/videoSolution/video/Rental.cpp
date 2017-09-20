#include "Rental.h"
#include "Movie.h"

Rental::Rental(const Movie& movie, int daysRented)
	: mMovie(movie)
	, mDaysRented(daysRented)
{
}

Rental::~Rental()
{
}

int Rental::daysRented() const
{
	return mDaysRented;
}

const Movie& Rental::movie() const
{
	return mMovie;
}

double Rental::Charge() const
{
    return movie().Charge(daysRented());
}
