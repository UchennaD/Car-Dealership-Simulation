#ifndef USERLIST_H
#define USERLIST_H

#include "User.h"
#include <iostream>
#include <fstream>

class UserList {
private:
    User* head;

public:
    UserList() : head(nullptr) {}

    ~UserList() {
        User* current = head;
        while (current) {
            User* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void addUser(const string& username, const string& password) {
        User* newUser = new User(username, password);
        newUser->next = head;
        head = newUser;
    }

    bool validateUser(const string& username, const string& password) const {
        User* current = head;
        while (current) {
            if (current->username == username && current->password == password) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void saveToFile(const string& filename) const {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "Error: Could not open the file for writing.\n";
            return;
        }

        User* current = head;
        while (current) {
            outFile << current->username << " " << current->password << endl;
            current = current->next;
        }
        outFile.close();
    }

    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cerr << "Error: Could not open the file for reading.\n";
            return;
        }

        string username, password;
        while (inFile >> username >> password) {
            addUser(username, password);
        }
        inFile.close();
    }
};

#endif
