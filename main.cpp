#include "Sedan.h"
#include "SUV.h"
#include "UserList.h"
#include "CarRentalSystem.h"
#include "Vehicle.h"
#include <iostream>
#include <limits>

using namespace std;

void signUp(UserList& users) {
    string username, password;

    cout << "\n=== Sign Up ===\n";
    cout << "Enter a username: ";
    cin >> username;
    cout << "Enter a password: ";
    cin >> password;

    users.addUser(username, password);
    users.saveToFile("users.txt"); // Save the new user to file

    cout << "Sign up successful! You can now login.\n";
}

bool login(UserList& users) {
    string username, password;

    cout << "\n=== Login ===\n";
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    if (users.validateUser(username, password)) {
        cout << "Login successful!\n";
        return true;
    } else {
        cout << "Invalid username or password.\n";
        return false;
    }
}

void displayStartMenu() {
    cout << "\n===== Welcome to the Car Rental System =====\n";
    cout << "1. Login\n";
    cout << "2. Sign Up\n";
    cout << "3. Exit\n";
}

int main() {
    UserList users;
    users.loadFromFile("users.txt"); // Load users from file at startup

    int choice;
    bool authenticated = false;

    while (!authenticated) {
        displayStartMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            authenticated = login(users);
        } else if (choice == 2) {
            signUp(users);
        } else if (choice == 3) {
            cout << "Exiting the program. Goodbye!\n";
            return 0;
        } else {
            cout << "Invalid choice. Please select a valid option.\n";
        }
    }

    // Proceed to the Car Rental System menu after successful login
    CarRentalSystem rentalSystem;

    rentalSystem.addCar(new Sedan("C001", "Toyota", "Camry", 60.0));
    rentalSystem.addCar(new Sedan("C002", "Honda", "Accord", 70.0));
    rentalSystem.addCar(new SUV("C003", "Mahindra", "Thar", 90.0));
    rentalSystem.addCar(new SUV("C004", "Ford", "Endeavour", 105.0));
    rentalSystem.menu();

    return 0;
}
