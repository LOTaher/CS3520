#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <string>
#include "customer.hpp"

using namespace std;

class Account {
public:
    Account(const string& username, const string& password, const Customer& customer);

    string get_username() const;
    bool verify_password(const std::string& password) const;
    Customer get_customer() const;

private:
    string username;
    string password;
    Customer customer;
};

#endif
