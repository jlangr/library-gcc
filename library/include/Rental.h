#ifndef RENTAL_H
#define RENTAL_H

#include "Movie.h"

class Rental
{
public:
	explicit Rental(const Movie& movie, int daysRented);
	virtual ~Rental();
	int daysRented() const;
	const Movie& movie() const;

private:
	Movie mMovie;
	int mDaysRented;
};

#endif
