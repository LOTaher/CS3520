#ifndef DELIVERY_HPP
#define DELIVERY_HPP

#include <string>

using namespace std;

class Delivery {
public:
    Delivery(const string& method, const string& address);

    string get_method() const;
    string get_address() const;

private:
    string method;
    string address;
};

#endif
