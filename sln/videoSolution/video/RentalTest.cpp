#include "gtest/gtest.h"

#include "Rental.h"
#include "Movie.h"
#include "PriceCode.h"

using namespace testing;

TEST(Rental, Create)
{
	Movie movie("title", PriceCode::REGULAR);
	Rental rental(movie, 3);
	ASSERT_EQ(3, rental.daysRented());
}
