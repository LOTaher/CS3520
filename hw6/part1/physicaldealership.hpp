#ifndef PHYSICALDEALERSHIP_HPP
#define PHYSICALDEALERSHIP_HPP

#include "dealership.hpp"

using namespace std;

class PhysicalDealership : public Dealership {
public:
    PhysicalDealership(const string& name, const string& location, const string& address);

    string get_address() const;

private:
    string address;
};

#endif
