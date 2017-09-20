#include "Customer.h"

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

#include "Rental.h"
#include "PriceCode.h"

using namespace std;

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

string Customer::statement() 
{
	stringstream result;
    ConfigureDecimalOutput(result);
    AddHeader(result);
	for (vector<Rental>::iterator it = mRentals.begin(); it != mRentals.end(); it++)
        AddDetail(result, *it);
    AddFooter(result);
	return result.str();
}

void Customer::ConfigureDecimalOutput(stringstream& stream)
{
    stream << std::setprecision(2) << std::fixed << std::showpoint;
}

void Customer::AddFooter(stringstream& stream)
{
    stream 
        << "Amount owed is "  
        << TotalCharge() << "\n";
    stream
        << "You earned " << TotalFrequentRenterPoints()
        << " frequent renter points";
}

void Customer::AddHeader(stringstream& stream)
{
    stream << "Rental Record for " << mName << "\n";
}

void Customer::AddDetail(stringstream& stream, Rental& rental)
{
    stream << "\t" << rental.movie().title() << "\t" <<
        Charge(rental) << "\n";
}

int Customer::FrequentRenterPoints(Rental& each)
{
    int frequentRenterPoints = 0;

    // Add frequent renter points
    frequentRenterPoints++;

    // Add bonus for a two-day new release rental
    if ((each.movie().priceCode() == PriceCode::NEW_RELEASE) &&
        each.daysRented() > 1) 
    {
        frequentRenterPoints++;
    }
    return frequentRenterPoints;
}

double Customer::Charge(Rental& each)
{
    return each.Charge();
}

double Customer::TotalCharge()
{
    double totalAmount = 0.0;
	for (vector<Rental>::iterator it = mRentals.begin(); it != mRentals.end(); it++)
		totalAmount += Charge(*it);
    return totalAmount;
}

int Customer::TotalFrequentRenterPoints()
{
    int frequentRenterPoints = 0;
    for (vector<Rental>::iterator it = mRentals.begin(); it != mRentals.end(); it++)
        frequentRenterPoints += FrequentRenterPoints(*it);
    return frequentRenterPoints;
}