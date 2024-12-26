#include "CarRentalSystem.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <cmath>
#include <numeric>

using namespace std;

Rental::Rental(Car* car, Customer* customer, int days, const string& bookingCode)
    : car(car), customer(customer), days(days), bookingCode(bookingCode) {}

Car* Rental::getCar() const {
    return car;
}

Customer* Rental::getCustomer() const {
    return customer;
}

int Rental::getDays() const {
    return days;
}

string Rental::getBookingCode() const {
    return bookingCode;
}

// Destructor implementation
CarRentalSystem::~CarRentalSystem() {
    for (auto car : cars) {
        delete car;
    }
}

// Helper function to calculate days between dates
int calculateDays(const string& startDate, const string& endDate) {
    int startYear, startMonth, startDay;
    int endYear, endMonth, endDay;

    char dash;
    istringstream startStream(startDate);
    istringstream endStream(endDate);

    startStream >> startYear >> dash >> startMonth >> dash >> startDay;
    endStream >> endYear >> dash >> endMonth >> dash >> endDay;

    auto daysSinceYearStart = [](int year, int month, int day) {
        static int daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month > 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
            ++daysPerMonth[1];

        return year * 365 + year / 4 - year / 100 + year / 400 + day + 
               accumulate(daysPerMonth, daysPerMonth + (month - 1), 0);
    };

    return daysSinceYearStart(endYear, endMonth, endDay) - 
           daysSinceYearStart(startYear, startMonth, startDay);
}

void CarRentalSystem::addCar(Car* car) {
    cars.push_back(car);
}

void CarRentalSystem::addCustomer(const Customer& customer) {
    customers.push_back(customer);
}

void CarRentalSystem::rentCar(Car* car, Customer& customer, int days) {
    if (car->available()) {
        car->rent();

        srand(time(nullptr));
        int randomCode = rand() % 10000;
        string bookingCode = customer.getCustomerId() + "-" + to_string(randomCode);

        cout << "\n=== Reservation Details ===\n";
        cout << "Customer Name: " << customer.getName() << endl;
        cout << "Car: " << car->getBrand() << " " << car->getModel() << endl;
        cout << "Rental Duration: " << days << " days" << endl;
        cout << "Total Cost: $" << fixed << setprecision(2) << car->calculatePrice(days) << endl;

        cout << "\nConfirm reservation? (Y/N): ";
        char confirm;
        cin >> confirm;

        if (toupper(confirm) == 'Y') {
            rentals.emplace_back(car, &customer, days, bookingCode);
            cout << "\nReservation confirmed! Your booking code is: " << bookingCode << endl;
        } else {
            car->returnVehicle();  // Make car available again if reservation is cancelled
            cout << "\nReservation canceled. Returning to main menu.\n";
        }
    } else {
        cout << "\nCar is not available for rent." << endl;
    }
}

void CarRentalSystem::returnCar(const string& bookingCode) {
    for (auto it = rentals.begin(); it != rentals.end(); ++it) {
        if (it->getBookingCode() == bookingCode) {
            Car* carToReturn = it->getCar();
            carToReturn->returnVehicle();
            rentals.erase(it);
            cout << "\nCar returned successfully!" << endl;
            return;
        }
    }
    cout << "\nInvalid booking code. Please check your code and try again." << endl;
}

void CarRentalSystem::viewAvailableCars() const {
    cout << "\n== Available Cars ==" << endl;
    bool found = false;

    for (const auto& car : cars) {
        if (car->available()) {
            found = true;
            cout << car->getVehicleId() << " - " << car->getBrand() << " " << car->getModel()
                 << " (" << car->getCategory() << ") - $" << fixed << setprecision(2)
                 << car->calculatePrice(1) << " per day" << endl;
        }
    }

    if (!found) {
        cout << "No cars are currently available.\n";
    }
}

void CarRentalSystem::menu() {
    while (true) {
        cout << "\n===== Car Rental System =====" << endl;
        cout << "1. Rent a Car" << endl;
        cout << "2. Return a Car" << endl;
        cout << "3. View Available Cars" << endl;
        cout << "4. Cancel Reservation" << endl;
        cout << "5. Contact Us" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "\n== Rent a Car ==" << endl;
            cout << "Choose a category (Sedan/SUV): ";
            string category;
            cin >> category;

            vector<Car*> availableCars;
            for (auto car : cars) {
                if (car->getCategory() == category && car->available()) {
                    availableCars.push_back(car);
                }
            }

            if (availableCars.empty()) {
                cout << "\nNo cars available in this category.\n";
                continue;
            }

            cout << "\nAvailable Cars in " << category << " category:\n";
            for (size_t i = 0; i < availableCars.size(); ++i) {
                cout << "[" << i << "] " << availableCars[i]->getBrand() 
                     << " " << availableCars[i]->getModel() << endl;
            }

            int carIndex;
            cout << "\nEnter the number of the car you'd like to rent: ";
            cin >> carIndex;

            if (cin.fail() || carIndex < 0 || carIndex >= static_cast<int>(availableCars.size())) {
                cout << "\nInvalid selection.\n";
                continue;
            }

            Car* selectedCar = availableCars[carIndex];
            cout << "Enter your name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string name;
            getline(cin, name);

            cout << "Enter the rental start date (YYYY-MM-DD): ";
            string startDate;
            cin >> startDate;

            cout << "Enter the rental end date (YYYY-MM-DD): ";
            string endDate;
            cin >> endDate;

            int rentalDays = calculateDays(startDate, endDate);

            if (rentalDays <= 0) {
                cout << "\nInvalid date range.\n";
                continue;
            }

            Customer customer("CUS" + to_string(customers.size() + 1), name);
            addCustomer(customer);
            rentCar(selectedCar, customer, rentalDays);

        } else if (choice == 2) {
            cout << "\n== Return a Car ==" << endl;
            cout << "Enter your booking code: ";
            string bookingCode;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, bookingCode);

            returnCar(bookingCode);

        } else if (choice == 3) {
            viewAvailableCars();

        } else if (choice == 4) {
            cancelReservation();

        } else if (choice == 5) {
            contactUs();

        } else if (choice == 6) {
            break;

        } else {
            cout << "\nInvalid choice.\n";
        }
    }
}

void CarRentalSystem::cancelReservation() {
    cout << "\n=== Cancel Reservation ===\n";

    cout << "Enter the name on the reservation: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string name;
    getline(cin, name);

    cout << "Enter the booking code: ";
    string bookingCode;
    cin >> bookingCode;

    for (auto it = rentals.begin(); it != rentals.end(); ++it) {
        Rental& rental = *it;
        Car* car = rental.getCar();
        Customer* customer = rental.getCustomer();

        if (customer->getName() == name && rental.getBookingCode() == bookingCode) {
            cout << "\n=== Reservation Details ===\n";
            cout << "Customer Name: " << customer->getName() << endl;
            cout << "Car: " << car->getBrand() << " " << car->getModel() << endl;
            cout << "Rental Duration: " << rental.getDays() << " days" << endl;
            cout << "Booking Code: " << rental.getBookingCode() << endl;

            cout << "\nDo you want to cancel this reservation? (Y/N): ";
            char confirm;
            cin >> confirm;

            if (toupper(confirm) == 'Y') {
                car->returnVehicle();
                rentals.erase(it);
                cout << "\nReservation canceled successfully!\n";
                return;
            } else {
                cout << "\nReservation was not canceled. Returning to main menu.\n";
                return;
            }
        }
    }

    cout << "\nNo reservation found matching the provided details.\n";
}

void CarRentalSystem::contactUs() const {
    cout << "\n=== Contact Us ===\n";
    cout << "Phone: +1-800-555-RENT (7368)\n";
    cout << "Email: support@carrentalsystem.com\n";
    cout << "We are available 24/7 for your assistance.\n";
}