#include "gmock/gmock.h"
#include "Movie.h"
#include "PriceCode.h"

using namespace testing;

class MovieTest: public Test 
{
public:
	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}
};

TEST_F(MovieTest, Create)
{
	Movie movie("title", PriceCode::REGULAR);
	ASSERT_THAT(movie.title(), Eq("title"));
	ASSERT_THAT(movie.priceCode(), Eq(PriceCode::REGULAR));
}

TEST_F(MovieTest, ChangePriceCode)
{
	Movie movie("a", PriceCode::NEW_RELEASE);
	movie.setPriceCode(PriceCode::CHILDRENS);
	ASSERT_THAT(movie.priceCode(), Eq(PriceCode::CHILDRENS));
}
