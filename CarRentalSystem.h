#ifndef CARRENTALSYSTEM_H
#define CARRENTALSYSTEM_H

#include <vector>
#include <string>
#include "Car.h"
#include "Customer.h"

using namespace std;

class Rental {
private:
    Car* car;  // Changed from vector<Car*>
    Customer* customer;
    int days;
    string bookingCode;

public:
    Rental(Car* car, Customer* customer, int days, const string& bookingCode);

    Car* getCar() const;
    Customer* getCustomer() const;
    int getDays() const;
    string getBookingCode() const;
};

class CarRentalSystem {
private:
    vector<Car*> cars;        // Changed to pointer
    vector<Customer> customers;
    vector<Rental> rentals;

public:
    ~CarRentalSystem();  // Added destructor
    void addCar(Car* car);  // Changed parameter
    void addCustomer(const Customer& customer);
    void rentCar(Car* car, Customer& customer, int days);  // Changed parameter
    void returnCar(const string& bookingCode);
    void viewAvailableCars() const;
    void menu();
    void cancelReservation();
    void contactUs() const;
};

#endif