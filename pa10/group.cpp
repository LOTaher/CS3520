#include "group.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// Constructors
Group::Group(string name, string area, int id) {
    this->name = name;
    this->area = area;
    this->id = id;
} 

Group::Group() {
    name = "";
    area = "";
    id = 0;
    employees = {};
}

// Add an employee to the group
Group& Group::add_employee(Employee employee) {
    if (employee.get_group_id() != id) {
        cout << "Employee does not belong to this group\n";
        return *this;
    }  else if (find(employees.begin(), employees.end(), employee) != employees.end()) {
        cout << "Employee already exists in the group\n";
        return *this;
    }
    employees.push_back(employee);
    return *this;
}

// Getters
string Group::get_name() { return name; }
string Group::get_area() { return area; }
int Group::get_id() { return id; }
vector<Employee> Group::get_employees() { return employees; }

// Setters
Group& Group::set_name(string name) {
    this->name = name;
    return *this;
}

Group& Group::set_area(string area) {
    this->area = area;
    return *this;
}

Group& Group::set_id(int id) {
    this->id = id;
    return *this;
}

Group& Group::set_employees(vector<Employee> employees) {
    this->employees = employees;
    return *this;
}

// Overload << operator for printing
ostream& operator<<(ostream& os, const Group& g) {
    os << "Group Name: " << g.name << ", Group ID: " << g.id << ", Area: " << g.area << "\nEmployees:\n";
    for (const auto& e : g.employees) {
        os << e << "\n";
    }
    return os;
}

// Overload >> operator for reading
std::istream& operator>>(std::istream& is, Group& g) {
    is >> g.name >> g.area >> g.id;
    return is;
}

// Overload - operator to remove employees
Group& Group::operator-(int x) {
    if (x >= employees.size()) {
        employees.clear();
    } else {
        employees.erase(employees.begin(), employees.begin() + x);
    }
    return *this;
}

// Overload + operator to merge two groups
Group Group::operator+(const Group& g) const {
    Group newGroup = *this;
    newGroup.employees.insert(newGroup.employees.end(), g.employees.begin(), g.employees.end());
    return newGroup;
}
