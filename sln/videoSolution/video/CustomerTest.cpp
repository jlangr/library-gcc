#include "gmock/gmock.h"

#include "time.h"
#include "Customer.h"

#include <string>
#include <iostream>
//#include "boost/timer.hpp"

using namespace testing;
using namespace std;

class CustomerTest: public Test 
{
public:

Customer* customer;
Movie* fightClub;
Movie* shane;
Movie* casinoRoyaleNew;
Movie* bambi;
Movie* matrix;

	void SetUp()
	{
		customer = new Customer("Jane Doe");
		fightClub = new Movie("Fight Club", PriceCode::REGULAR);
		shane = new Movie("Shane", PriceCode::REGULAR);
		casinoRoyaleNew = new Movie("Casino Royale", PriceCode::NEW_RELEASE);
		bambi = new Movie("Bambi", PriceCode::CHILDRENS);
		matrix = new Movie("Matrix", PriceCode::CHILDRENS);
	}

	void TearDown()
	{
		delete fightClub;
		delete shane;
		delete casinoRoyaleNew;
		delete bambi;
		delete matrix;
		delete customer;
	}
};

/*
TEST_F(CustomerTest, PerformanceOfStatement)
{
	time_t start, stop;
	int its = 500000;
	Rental rental1(*shane, 3);
	Rental rental2(*fightClub, 3);
	Rental rental3(*casinoRoyaleNew, 3);
	Rental rental4(*bambi, 3);
	Rental rental5(*matrix, 3);
	customer->add(rental1);
	customer->add(rental2);
	customer->add(rental3);
	customer->add(rental4);
	customer->add(rental5);
	ctime(&start);

	boost::timer t;

	for (int i = 0; i < its; i++) {	
		std::string statement = customer->statement();
	}
	std::cout << t.elapsed() << std::endl;
}
*/

TEST_F(CustomerTest, Create)
{
	ASSERT_EQ("Jane Doe", customer->name());
	vector<Rental> rentals = customer->rentals();
	ASSERT_EQ(0, rentals.size());
}

TEST_F(CustomerTest, AddRental)
{
	Rental rental(*shane, 3);
	customer->add(rental);
	vector<Rental> rentals = customer->rentals();
	ASSERT_EQ(1, rentals.size());
	Rental retrieved = rentals[0];
	ASSERT_EQ(rental.daysRented(), retrieved.daysRented());
	ASSERT_EQ(shane->title(), retrieved.movie().title());
}

TEST_F(CustomerTest, StatementNoRentals)
{
	string expected(
		"Rental Record for Jane Doe\n"
		"Amount owed is 0.00\n"
		"You earned 0 frequent renter points");
	ASSERT_EQ(expected, customer->statement());
}

TEST_F(CustomerTest, StatementWithOneRegularRental) 
{
	int daysRented = 2;
	Rental rental(*fightClub, daysRented);
	customer->add(rental);

	string expected(
		"Rental Record for Jane Doe\n"
		"\tFight Club\t2.00\n"
		"Amount owed is 2.00\n"
		"You earned 1 frequent renter points");
	ASSERT_EQ(expected, customer->statement());
}

TEST_F(CustomerTest, StatementWithTwoRegularRentals) 
{
	Rental rental1(*fightClub, 3);
	Rental rental2(*shane, 3);
	customer->add(rental1);
	customer->add(rental2);

	std::string expected(
		"Rental Record for Jane Doe\n"
		"\tFight Club\t3.50\n"
		"\tShane\t3.50\n"
		"Amount owed is 7.00\n"
		"You earned 2 frequent renter points");
	ASSERT_EQ(expected, customer->statement());
}

TEST_F(CustomerTest, StatementWithChildrensRental)
{
	Rental rental(*bambi, 7);
	customer->add(rental);
	string expected(
		"Rental Record for Jane Doe\n"
		"\tBambi\t9.00\n"
		"Amount owed is 9.00\n"
		"You earned 1 frequent renter points");
	ASSERT_EQ(expected, customer->statement());
}

TEST_F(CustomerTest, StatementWithNewReleaseOneNight)
{
	Rental rental(*casinoRoyaleNew, 1);
	customer->add(rental);
	string expected(
		"Rental Record for Jane Doe\n"
		"\tCasino Royale\t3.00\n"
		"Amount owed is 3.00\n"
		"You earned 1 frequent renter points");
	ASSERT_EQ(expected, customer->statement());
}

TEST_F(CustomerTest, StatementWithNewReleaseMoreThanOneNight)
{
	Rental rental(*casinoRoyaleNew, 3);
	customer->add(rental);
	string expected(
		"Rental Record for Jane Doe\n"
		"\tCasino Royale\t9.00\n"
		"Amount owed is 9.00\n"
		"You earned 2 frequent renter points");
	ASSERT_EQ(expected, customer->statement());
}

TEST_F(CustomerTest, StatementWithManyRentals)
{
	Rental rental1(*casinoRoyaleNew, 3);
	Rental rental2(*fightClub, 3);
	Rental rental3(*bambi, 10);
	Rental rental4(*shane, 10);
	customer->add(rental1);
	customer->add(rental2);
	customer->add(rental3);
	customer->add(rental4);

	string expected(
		"Rental Record for Jane Doe\n"
		"\tCasino Royale\t9.00\n"
		"\tFight Club\t3.50\n"
		"\tBambi\t13.50\n"
		"\tShane\t14.00\n"
		"Amount owed is 40.00\n"
		"You earned 5 frequent renter points");
	ASSERT_EQ(expected, customer->statement());
}
