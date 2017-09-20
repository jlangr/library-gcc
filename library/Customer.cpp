#include "Customer.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include "Rental.h"
#include "PriceCode.h"

Customer::Customer(const std::string& name)
	: mName(name)
{
}

Customer::~Customer()
{
}

void Customer::add(const Rental& rental)
{
	mRentals.push_back(rental);
}

std::string Customer::name() const
{
	return mName;
}

std::vector<Rental> Customer::rentals() const
{
	return mRentals;
}

std::string Customer::statement() 
{
	double totalAmount = 0.0;
	int frequentRenterPoints = 0;

	std::vector<Rental>::iterator it;
	std::stringstream result;
	result << std::setprecision(2) << std::fixed << std::showpoint;
	result << "Rental Record for " << mName << "\n";

	for (it = mRentals.begin(); it != mRentals.end(); it++)
	{
		double thisAmount = 0;
		Rental& each = (*it);

		// Determine amounts for each line of movies
		switch (each.movie().priceCode()) {

			case PriceCode::REGULAR:
				thisAmount += 2;
				if (each.daysRented() > 2) 
					thisAmount += (each.daysRented() - 2) * 1.5;
				break;

			case PriceCode::NEW_RELEASE:
				thisAmount += each.daysRented() * 3;
				break;

			case PriceCode::CHILDRENS:
				thisAmount += 1.5;
				if (each.daysRented() > 2)
					thisAmount += (each.daysRented() - 2) * 1.5;
				break;
		}

		// Add frequent renter points
		frequentRenterPoints++;

		// Add bonus for a two-day new release rental
		if ((each.movie().priceCode() == PriceCode::NEW_RELEASE) &&
			 each.daysRented() > 1) 
		{
			frequentRenterPoints++;
		}

		// Show figures for this rental
		result << "\t" << each.movie().title() << "\t" <<
			thisAmount << "\n";
		totalAmount += thisAmount;
	}

	// Add footer lines
	result 
		<< "Amount owed is "  
		<< totalAmount << "\n";
	result 
		<< "You earned " << frequentRenterPoints
		<< " frequent renter points";
	return result.str();
}
