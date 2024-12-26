#include "Customer.h"

Customer::Customer(string customerId, string name) : customerId(customerId), name(name) {}

string Customer::getCustomerId() const {
    return customerId;
}

string Customer::getName() const {
    return name;
}
