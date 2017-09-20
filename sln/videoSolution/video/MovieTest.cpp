#include "gtest/gtest.h"

#include "Movie.h"
#include "PriceCode.h"

using namespace testing;

TEST(Movie, Create)
{
	Movie movie("title", PriceCode::REGULAR);
	
    ASSERT_EQ("title", movie.title());
	ASSERT_EQ(PriceCode::REGULAR, movie.priceCode());
}

TEST(Movie, ChangePriceCode)
{
	Movie movie("a", PriceCode::NEW_RELEASE);
	movie.setPriceCode(PriceCode::CHILDRENS);

	ASSERT_EQ(PriceCode::CHILDRENS, movie.priceCode());
}

