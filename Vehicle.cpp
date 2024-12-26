#include "Vehicle.h"

Vehicle::Vehicle(string vehicleId, string brand, string model, double basePricePerDay)
    : vehicleId(vehicleId), brand(brand), model(model), 
      basePricePerDay(basePricePerDay), isAvailable(true) {}

string Vehicle::getVehicleId() const { return vehicleId; }
string Vehicle::getBrand() const { return brand; }
string Vehicle::getModel() const { return model; }

double Vehicle::calculatePrice(int rentalDays) const {
    return basePricePerDay * rentalDays;
}

bool Vehicle::available() const { return isAvailable; }
void Vehicle::rent() { isAvailable = false; }
void Vehicle::returnVehicle() { isAvailable = true; }