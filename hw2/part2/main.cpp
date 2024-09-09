#include <fstream>
#include <iostream>
#include <limits>  
#include <string>
#include "include/airplane.hpp"
#include "include/passenger.hpp"
#include "include/employee.hpp"

using namespace std;

int main() {
    // Initializing the airplane object
    Airplane airplane;

    // Create the seating chart for the airplane
    create_seating_chart(airplane);
    
    // Defining the saved manifest file
    string manifest_file = "saved_manifest.txt";

    // There are dummy data passengers saved already, so the demo will arleady have some passengers
    read_manifest(airplane, manifest_file);
    
    // The main menu of the Airline Reservation System
    while (true) {
        cout << "Welcome to our airline reservation system! Please login to continue.\n";
        cout << "Are you a passenger or an airline employee? \n";
        cout << "1. Passenger \n";
        cout << "2. Airline Employee \n";
        cout << "3. Quit \n";

        int choice;
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 3) {
            cout << "Invalid input. Please try again. \n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            // Passenger login
            case 1: {
                string name;
                cout << "Please enter your name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, name);
                if (cin.fail() || name.empty()) {
                    cout << "Invalid input. Please try again. \n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                // Check if the passenger already exists using a simple loop
                bool passenger_exists = false;
                for (size_t i = 0; i < airplane.passenger_list.size(); ++i) {
                    if (airplane.passenger_list[i].name == name) {
                        passenger_exists = true;
                        // Pass the existing passenger by reference
                        passenger_login(airplane, airplane.passenger_list[i]); 
                        break;
                    }
                }

                if (!passenger_exists) {
                    Passenger new_passenger;
                    new_passenger.name = name;
                    // Add the new passenger to the passenger list
                    airplane.passenger_list.push_back(new_passenger); 
                    // Pass the new passenger by reference
                    passenger_login(airplane, airplane.passenger_list.back()); 
                }
                break;
            }
            case 2: {
                // Employee login
                string username, password;
                cout << "Please enter your username: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, username);
                if (cin.fail() || username.empty()) {
                    cout << "Invalid input. Please try again. \n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                cout << "Please enter your password: ";
                getline(cin, password);
                if (cin.fail() || password.empty()) {
                    cout << "Invalid input. Please try again. \n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                // Validate the employee credentials by reading the username and password from the credentials.txt file
                if (!validate_employee_credentials(username, password)) {
                    cout << "Login credentials are incorrect. Please try again. \n";
                    continue;
                } else {
                    // If they are correct, create an employee object and pass it by reference
                    Employee employee;
                    employee.username = username;
                    employee.password = password;
                    employee_login(airplane, employee);
                }
                break;
            }
            case 3: {
                // Quit the program
                cout << "Goodbye! \n";
                // remove the content from the working manifest file
                ofstream file("working_manifest.txt");
                file.close();
                return 0;
            }
            default: {
                // If none of the above options are selected, print an error message.
                cout << "Invalid choice. Try again.\n";
                break;
            }
        }
    }

    return 0;
}
