#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "airplane.hpp"
#include <string>

// Represents an employee in the Airline Reservation System
struct Employee {
    // The username of the employee
    string username;
    // The password of the employee
    string password;
};

// Function declarations. (Function definitions are in employee.cpp)
bool validate_employee_credentials(string, string);
void employee_login(Airplane&, Employee&);
void load_previous_manifest(Airplane&);
void replace_saved_manifest();

#endif // EMPLOYEE_H
