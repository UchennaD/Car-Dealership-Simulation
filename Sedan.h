#ifndef SEDAN_H
#define SEDAN_H

#include "Car.h"

class Sedan : public Car {
public:
    Sedan(string carId, string brand, string model, double basePricePerDay);
    
    virtual double calculatePrice(int rentalDays) const override;
};

#endif