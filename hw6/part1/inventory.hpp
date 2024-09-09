#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include "vehicle.hpp"

class Inventory {
public:
    void add_vehicle(const Vehicle& vehicle);
    void remove_vehicle(const string& make, const string& model);
    Vehicle* find_vehicle(const string& make, const string& model);
    vector<Vehicle> get_all_vehicles() const;

private:
    vector<Vehicle> vehicles;
};

#endif
