#include "Car.h"

Car::Car(string carId, string brand, string model, string category, double basePricePerDay)
    : Vehicle(carId, brand, model, basePricePerDay), category(category) {}

string Car::getCategory() const { return category; }

double Car::calculatePrice(int rentalDays) const {
    // Base car calculation, can be overridden by specific car types
    return Vehicle::calculatePrice(rentalDays);
}
