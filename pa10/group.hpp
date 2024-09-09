#ifndef GROUP_HPP
#define GROUP_HPP

#include <string>
#include <vector>
#include "employee.hpp"

class Group {
private:
    string name;
    string area;
    int id;
    vector<Employee> employees;

public:
    Group(string name, string area, int id);
    Group();

    // Add an employee to the group
    Group& add_employee(Employee employee);

    // Getters
    string get_name();
    string get_area();
    int get_id();
    vector<Employee> get_employees();

    // Setters
    Group& set_name(string name);
    Group& set_area(string area);
    Group& set_id(int id);
    Group& set_employees(vector<Employee> employees);

    // Overload << operator for printing
    friend ostream& operator<<(ostream& os, const Group& g);

    // Overload >> operator for reading
    friend istream& operator>>(istream& is, Group& g);

    // Overload - operator to remove employees
    Group& operator-(int x);

    // Overload + operator to merge two groups
    Group operator+(const Group& g) const;
};

#endif
