#ifndef DEALERSHIP_HPP
#define DEALERSHIP_HPP

#include <string>
#include <vector>
#include "inventory.hpp"
#include "order.hpp"

using namespace std;

class Dealership {
public:
    Dealership(const string& name, const string& location);

    string get_name() const;
    string get_location() const;
    Inventory& get_inventory();
    void place_order(const Order& order);

protected:
    string name;
    string location;
    Inventory inventory;
    vector<Order> orders;
};

#endif
