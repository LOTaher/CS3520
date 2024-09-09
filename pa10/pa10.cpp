#include <cstdio>
#include <iostream>
#include "group.hpp"
#include "employee.hpp"

using namespace std;

int main() {
    // Initialize groups
    Group g1("Sales", "Marketing", 1);
    Group g2("Design", "UI Design", 2);

    // Add employees to group 1
    g1.add_employee(Employee("Alice", "alice@example.com", "Manager", 1));
    g1.add_employee(Employee("Bob", "bob@example.com", "Executive", 1));

    // Add employees to group 2
    g2.add_employee(Employee("Charlie", "charlie@example.com", "Designer", 2));
    g2.add_employee(Employee("Dave", "dave@example.com", "Lead Designer", 2));

    // Test the cout << operator
    for (const auto& e : g1.get_employees()) {
        cout << e << "\n";
    }

    cout << " " << endl;

    for (const auto& e : g2.get_employees()) {
        cout << e << "\n";
    }
    
    cout << "Group 1:\n" << g1 << "\n";

    cout << " " << endl;

    cout << "Group 2:\n" << g2 << "\n";

    // Testing the cin >> operator
    cout << "Enter a new group (name, area, id), each input should be seperated by returns:\n";
    Group g4;
    cin >> g4;
    cout << "Group:\n" << g4 << "\n";

    cout << "Enter a new employee for the new group (name, email, role, group_id):, each input should be seperated by returns:\n";
    Employee e("", "", "", g4.get_id());
    cin >> e;
    g4.add_employee(e);
    cout << "Updated Group:\n" << g4 << "\n";

    // Testing - operator
    cout << "Removing 1 employee from Group 1:\n";
    g1 = g1 - 1;
    cout << g1 << "\n";

    // Testing + operator
    cout << "Merging Group 1 and Group 2:\n";
    Group g3 = g1 + g2;
    cout << g3 << "\n";

    return 0;
}
