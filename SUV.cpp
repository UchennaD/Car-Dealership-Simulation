#include "SUV.h"

SUV::SUV(string carId, string brand, string model, double basePricePerDay)
    : Car(carId, brand, model, "SUV", basePricePerDay) {}

double SUV::calculatePrice(int rentalDays) const {
    // SUVs might have a premium charge
    double basePrice = Car::calculatePrice(rentalDays);
    return basePrice;
}

