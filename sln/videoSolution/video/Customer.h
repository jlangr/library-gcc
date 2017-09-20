#ifndef D_Customer_h
#define D_Customer_h

#include <string>
#include <vector>
#include <sstream>

#include "Rental.h"

class Customer
{
public:
	explicit Customer(const std::string& name);
	virtual ~Customer();
	void add(const Rental& rental);
	std::string name() const;
	std::vector<Rental> rentals() const;
	std::string statement();

private:
	Customer(const Customer&);
	Customer& operator=(const Customer&);
	std::vector<Rental> mRentals;
	std::string mName;
    double Charge(Rental&);
    int FrequentRenterPoints(Rental&);
    void ConfigureDecimalOutput(std::stringstream& stream);
    void AddHeader(std::stringstream& stream);
    void AddDetail(std::stringstream& stream, Rental& rental);
    double TotalCharge();
    int TotalFrequentRenterPoints();
    void AddFooter(std::stringstream& stream);
};

#endif  // D_Customer_h
