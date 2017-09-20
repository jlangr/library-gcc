#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
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
};

#endif
