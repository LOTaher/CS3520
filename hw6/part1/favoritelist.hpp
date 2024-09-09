#ifndef FAVORITELIST_HPP
#define FAVORITELIST_HPP

#include <vector>
#include <string>
#include "vehicle.hpp"

using namespace std;

class FavoriteList
{
public:
    void add_vehicle(const Vehicle &vehicle);
    void remove_vehicle(const string &make, const string &model);
    vector<Vehicle> get_all_favorites() const;

private:
    vector<Vehicle> favorite_vehicles;
};

#endif
