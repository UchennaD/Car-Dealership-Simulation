#ifndef SUV_H
#define SUV_H

#include "Car.h"

class SUV : public Car {
public:
    SUV(string carId, string brand, string model, double basePricePerDay);
    
    virtual double calculatePrice(int rentalDays) const override;
};

#endif