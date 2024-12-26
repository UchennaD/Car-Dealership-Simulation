#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
using namespace std;

class Vehicle {
protected:
    string vehicleId;
    string brand;
    string model;
    double basePricePerDay;
    bool isAvailable;

public:
    Vehicle(string vehicleId, string brand, string model, double basePricePerDay);
    
    virtual ~Vehicle() = default;
    
    string getVehicleId() const;
    string getBrand() const;
    string getModel() const;
    virtual double calculatePrice(int rentalDays) const;
    bool available() const;
    
    void rent();
    void returnVehicle();
};

#endif