#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <iostream>
#include <string>

using namespace std;

class Employee {
private:
    string name;
    string email;
    string role;
    int group_id;

public:
    // Constructors
    Employee(string name, string email, string role, int group_id);
    Employee();

    // Getters
    string get_name();
    string get_email();
    string get_role();
    int get_group_id();

    // Setters
    Employee& set_name(string name);
    Employee& set_email(string email);
    Employee& set_role(string role);
    Employee& set_group_id(int group_id);

    // Overload << operator for printing
    friend ostream& operator<<(ostream& os, const Employee& e);

    // Overload >> operator for reading
    friend istream& operator>>(istream& is, Employee& e);

    // Overload == operator for comparing
    bool operator==(const Employee& e) const;
};

#endif
