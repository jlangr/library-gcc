#pragma once

class Price
{
public:
    virtual int Code() const=0;
    virtual double Charge(int daysRented) const=0;
};

class NewRelease: public Price
{
public:
    virtual int Code() const { return PriceCode::NEW_RELEASE; }
  
    virtual double Charge(int daysRented) const
    {
        return daysRented * 3;
    }

};

class Childrens: public Price
{
public:
    virtual int Code() const { return PriceCode::CHILDRENS; }

    virtual double Charge(int daysRented) const
    {
        double charge(1.5);
        if (daysRented > 2)
            charge += (daysRented - 2) * 1.5;
        return charge;
    }
};

class Regular: public Price
{
public:
    virtual int Code() const { return PriceCode::REGULAR; }

    double Charge(int daysRented) const
    {
        double charge(2);
        if (daysRented > 2) 
            charge += (daysRented- 2) * 1.5;
        return charge;
    }
};