#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
public:
    string username;
    string password;
    User* next;

    User(string username, string password) : username(username), password(password), next(nullptr) {}
};

#endif
