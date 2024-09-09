#ifndef SEAT_H
#define SEAT_H

#include <string>
using namespace std;

// Represents a seat in the plane
struct Seat {
    // The seat number is a string that is a combination of the seat label and the row number
    string seat_number;
    // The name of the passenger assigned to the seat
    string name;
    // A boolean value that indicates whether the seat is assigned
    bool is_assigned;
    // A string that indicates the class level of the seat
    string level;
};

#endif
