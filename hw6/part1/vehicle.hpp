#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <string>

using namespace std;

class Vehicle {
public:
    Vehicle(const string& make, const std::string& model, double price);

    string get_make() const;
    string get_model() const;
    double get_price() const;

private:
    string make;
    string model;
    double price;
};

#endif
