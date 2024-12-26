#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
using namespace std;

class Customer {
private:
    string customerId;
    string name;

public:
    Customer(string customerId, string name);

    string getCustomerId() const;
    string getName() const;
};

#endif
