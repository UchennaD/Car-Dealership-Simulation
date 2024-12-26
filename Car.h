#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

class Car : public Vehicle {
protected:
    string category;

public:
    Car(string carId, string brand, string model, string category, double basePricePerDay);
    
    virtual ~Car() = default;
    
    string getCategory() const;
    virtual double calculatePrice(int rentalDays) const override;
};

#endif