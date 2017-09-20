#ifndef D_Rental_h
#define D_Rental_h
#include "Movie.h"

class Rental
{
public:
	explicit Rental(const Movie& movie, int daysRented);
	virtual ~Rental();
	int daysRented() const;
	const Movie& movie() const;
    double Charge() const;

private:
	Movie mMovie;
	int mDaysRented;
};

#endif  // D_Rental_h
