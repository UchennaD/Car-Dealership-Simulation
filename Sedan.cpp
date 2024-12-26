#include "Sedan.h"

Sedan::Sedan(string carId, string brand, string model, double basePricePerDay)
    : Car(carId, brand, model, "Sedan", basePricePerDay) {}

double Sedan::calculatePrice(int rentalDays) const {
    // Sedans might have a special discount for longer rentals
    double basePrice = Car::calculatePrice(rentalDays);
    if (rentalDays >= 7) {
        return basePrice * 0.9; // 10% discount for weekly rentals
    }
    return basePrice;
}
