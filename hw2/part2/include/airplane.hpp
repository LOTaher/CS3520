#ifndef AIRPLANE_H
#define AIRPLANE_H

#include "seat.hpp"
#include <vector>
using namespace std;

// Forward declaration of Passenger
struct Passenger;

// Represents the only airplane in the Airline Reservation System
struct Airplane {
    // The seats on the airplane
    Seat seats[12][6];
    // A list of passengers on the airplane
    vector<Passenger> passenger_list;
    // A boolean value that indicates whether the airplane is full
    bool is_full();
};

// Function declarations. (Function definitions are in airplane.cpp)
void create_seating_chart(Airplane&);
void display_seating_chart(Airplane&);
void save_manifest(Airplane&, string);
void read_manifest(Airplane&, string);
void print_manifest(Airplane&, bool);

#endif
