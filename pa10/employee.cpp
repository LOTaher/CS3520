#include "employee.hpp"

using namespace std;

// Constructors
Employee::Employee(string name, string email, string role, int group_id) {
    this->name = name;
    this->email = email;
    this->role = role;
    this->group_id = group_id;
}

Employee::Employee() {
    name = "";
    email = "";
    role = "";
    group_id = 0;
}

// Getters
string Employee::get_name() { return name; }
string Employee::get_email() { return email; }
string Employee::get_role() { return role; }
int Employee::get_group_id() { return group_id; }

// Setters
Employee& Employee::set_name(string name) {
    this->name = name;
    return *this;
}

Employee& Employee::set_email(string email) {
    this->email = email;
    return *this;
}

Employee& Employee::set_role(string role) {
    this->role = role;
    return *this;
}

Employee& Employee::set_group_id(int group_id) {
    this->group_id = group_id;
    return *this;
}

// Overload << operator for printing
ostream& operator<<(ostream& os, const Employee& e) {
    os << "Name: " << e.name << ", Email: " << e.email << ", Role: " << e.role << ", Group ID: " << e.group_id;
    return os;
}

// Overload >> operator for reading
istream& operator>>(istream& is, Employee& e) {
    is >> e.name >> e.email >> e.role >> e.group_id;
    return is;
}

// Overload == operator for comparing
bool Employee::operator==(const Employee& e) const {
    return name == e.name && email == e.email && role == e.role && group_id == e.group_id;
}
