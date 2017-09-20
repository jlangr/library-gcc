#include "gmock/gmock.h"
#include "Rental.h"
#include "Movie.h"
#include "PriceCode.h"

using namespace testing;

class RentalTest: public Test 
{
	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}
};

TEST_F(RentalTest, Create)
{
	Movie movie("title", PriceCode::REGULAR);
	Rental rental(movie, 3);
	ASSERT_THAT(rental.daysRented(), Eq(3));
}
