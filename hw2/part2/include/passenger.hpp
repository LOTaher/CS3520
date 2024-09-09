#ifndef PASSENGER_H
#define PASSENGER_H

#include "airplane.hpp"
#include "seat.hpp"

// Represents a passenger in the Airline Reservation System
struct Passenger {
    // The name of the passenger
    string name;
    // The seat the passenger is assigned to
    Seat seat;
};

// Function declarations. (Function definitions are in passenger.cpp)
void passenger_login(Airplane&, Passenger&);
void choose_seat_randomly(Airplane&, Passenger&);
void manually_choose_seat(Airplane&, Passenger&);
void change_or_cancel_seat_assignment(Airplane&, Passenger&, bool);
void print_boarding_pass(Airplane&, Passenger&);

#endif
