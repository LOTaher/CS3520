#include "include/employee.hpp"
#include "include/airplane.hpp"
#include "include/passenger.hpp"
#include <algorithm> // Include the algorithm header for sort
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Compare functions for sorting the passenger list
bool compare_by_seat_ascending(const Passenger &a, const Passenger &b) {
  return a.seat.seat_number < b.seat.seat_number;
}

bool compare_by_seat_descending(const Passenger &a, const Passenger &b) {
  return a.seat.seat_number > b.seat.seat_number;
}

bool compare_by_name_ascending(const Passenger &a, const Passenger &b) {
  return a.name < b.name;
}

bool compare_by_name_descending(const Passenger &a, const Passenger &b) {
  return a.name > b.name;
}

bool compare_by_class(const Passenger &a, const Passenger &b) {
  if (a.seat.level == b.seat.level)
    return a.name < b.name;
  if (a.seat.level == "First Class")
    return true;
  if (b.seat.level == "First Class")
    return false;
  if (a.seat.level == "Business Class")
    return true;
  if (b.seat.level == "Business Class")
    return false;
  return false;
}

// Employee login function
void employee_login(Airplane &airplane, Employee &employee) {
  cout << "Welcome, " << employee.username << "!" << endl;
  while (true) {
    cout << "Please select an option: " << endl;
    cout << "1. Display the seating map" << endl;
    cout << "2. Print a passenger manifest" << endl;
    cout << "3. Load previous seat assignment and passenger manifest" << endl;
    cout << "4. Save current seat assignment and passenger manifest" << endl;
    cout << "5. Re-assign or cancel a seat assignment" << endl;
    cout << "6. Quit" << endl;

    int choice;
    cin >> choice;
    if (cin.fail() || choice < 1 || choice > 6) {
      cout << "Invalid input. Please try again." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    switch (choice) {
    case 1:
      // Display the seating chart
      display_seating_chart(airplane);
      break;
    case 2:
      // Print the passenger manifest
      print_manifest(airplane, true);
      break;
    case 3:
      // Load the previous manifest
      load_previous_manifest(airplane);
      break;
    case 4:
      // Save the current manifest
      replace_saved_manifest();
      break;
    case 5: {
      cout << "Please enter the name of the passenger: ";
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      string passenger_name;
      getline(cin, passenger_name);
      if (cin.fail() || passenger_name.empty()) {
        cout << "Invalid input. Please try again." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
      }
      // Find the passenger by name so we can use the passenger object to change
      // or cancel the seat assignment
      for (Passenger &passenger : airplane.passenger_list) {
        if (passenger.name == passenger_name) {
          change_or_cancel_seat_assignment(airplane, passenger, true);
          break;
        }
      }
      // If there is no passenger with the given name, print an error message
      cout << "Passenger not found." << endl;
      break;
    }
    case 6:
      // Go back to the main menu
      cout << "Goodbye, " << employee.username << "!" << endl;
      return;
    }

    // Clear the buffer and wait for the enter key to go back to the menu
    cout << "\nPress Enter to return to the main menu..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
  }
}

// Function to validate employee credentials from the file credentials.txt
bool validate_employee_credentials(string username, string password) {
  ifstream file("credentials.txt");
  if (!file.is_open()) {
    cout << "Error: could not open credentials file" << endl;
    return false;
  }

  string file_username, file_password, line;
  while (getline(file, line)) {
    if (line.find("username: ") == 0) {
      // Substring starting from the 10th character to get the username
      file_username = line.substr(10);
    } else if (line.find("password: ") == 0) {
      // Substring starting from the 10th character to get the password
      file_password = line.substr(10);
    }
  }

  // This returns a bool
  return username == file_username && password == file_password;
}

// Function to print the manifest and reorder it based on user input
void print_manifest(Airplane &airplane, bool reorder) {
  cout << "Current passenger manifest:" << endl;
  for (size_t i = 0; i < airplane.passenger_list.size(); ++i) {
    cout << "Name: " << airplane.passenger_list[i].name
         << " Seat: " << airplane.passenger_list[i].seat.seat_number
         << " Level: " << airplane.passenger_list[i].seat.level << endl;
  }

  // If the user wants to reorder the manifest, display a new menu
  if (reorder) {
    cout << "How would you like to reorder the manifest?" << endl;
    cout << "1. By seat number (ascending)" << endl;
    cout << "2. By seat number (descending)" << endl;
    cout << "3. By name (A-Z)" << endl;
    cout << "4. By name (Z-A)" << endl;
    cout << "5. By class (first, business, economy)" << endl;
    cout << "6. I don't want to reorder the manifest" << endl;

    int choice;
    cin >> choice;
    if (cin.fail() || choice < 1 || choice > 6) {
      cout << "Invalid input. Please try again." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      return;
    }

    // Sort the passenger list based on the user's choice
    vector<Passenger> passenger_list = airplane.passenger_list;

    switch (choice) {
    case 1:
      // Compare by seat number ascending
      sort(passenger_list.begin(), passenger_list.end(),
           compare_by_seat_ascending);
      break;
    case 2:
      // Compare by seat number descending
      sort(passenger_list.begin(), passenger_list.end(),
           compare_by_seat_descending);
      break;
    case 3:
      // Compare by name ascending
      sort(passenger_list.begin(), passenger_list.end(),
           compare_by_name_ascending);
      break;
    case 4:
      // Compare by name descending
      sort(passenger_list.begin(), passenger_list.end(),
           compare_by_name_descending);
      break;
    case 5:
      // Compare by class
      sort(passenger_list.begin(), passenger_list.end(), compare_by_class);
      break;
    case 6:
      // Go back to the menu
      return;
    }

    // Based on the sorted passenger list, use it to print the manifest
    for (size_t i = 0; i < passenger_list.size(); ++i) {
      cout << "Name: " << passenger_list[i].name
           << " Seat: " << passenger_list[i].seat.seat_number
           << " Level: " << passenger_list[i].seat.level << endl;
    }
  }
}

// Function to take the saved manifest and load it into the airplane object
void load_previous_manifest(Airplane &airplane) {
  string saved_manifest_file = "saved_manifest.txt";
  ifstream saved_file(saved_manifest_file);
  if (!saved_file.is_open()) {
    cout << "Error: could not open saved manifest file" << endl;
    return;
  }

  // If the content is empty, return
  if (saved_file.peek() == ifstream::traits_type::eof()) {
    cout << "Your saved manifest is empty. There is no passenger information "
            "to load."
         << endl;
    saved_file.close();
    return;
  }

  // Copy the content from saved_manifest to working_manifest
  string working_manifest_file = "working_manifest.txt";
  ofstream working_file(working_manifest_file);
  if (!working_file.is_open()) {
    cout << "Error: could not open working manifest file" << endl;
    saved_file.close();
    return;
  }

  working_file << saved_file.rdbuf(); // Copy the contents
  saved_file.close();
  working_file.close();

  // Clear the airplane's passenger list and seating chart
  airplane.passenger_list.clear();
  for (int i = 0; i < 12; ++i) {
    for (int j = 0; j < 6; ++j) {
      airplane.seats[i][j].is_assigned = false;
      airplane.seats[i][j].seat_number = "";
      airplane.seats[i][j].level = "";
    }
  }

  // Reopen the saved manifest file to load the passengers and seat assignments
  ifstream file(saved_manifest_file);
  if (!file.is_open()) {
    cout << "Error: could not open saved manifest file for loading" << endl;
    return;
  }

  string line;
  // Read the file line by line
  while (getline(file, line)) {
    Passenger passenger;

    passenger.name = line;

    if (!getline(file, line))
      break;
    passenger.seat.seat_number = line;

    if (!getline(file, line))
      break;
    passenger.seat.level = line;

    // For every passenger and their seat info listed in the manifest, assign
    // the seat to the passenger in the airplane object
    int row = passenger.seat.seat_number[1] - '1';
    char seat_col = passenger.seat.seat_number[0];
    int column = seat_col - 'A';
    if (seat_col > 'B')
      column -= 1;

    if (row >= 0 && row < 12 && column >= 0 && column < 6) {
      airplane.seats[row][column].is_assigned = true;
      airplane.seats[row][column].seat_number = passenger.seat.seat_number;
      airplane.seats[row][column].level = passenger.seat.level;
      passenger.seat.is_assigned = true;
    }

    airplane.passenger_list.push_back(passenger);
  }
  // Close the file
  file.close();

  cout << "Loaded previous manifest successfully." << endl;

  // Print the manifest
  print_manifest(airplane, false);
}

// Function to replace the saved manifest with the working manifest
void replace_saved_manifest() {
  // Using an ifstream to read the working manifest
  ifstream working_file("working_manifest.txt");
  if (!working_file.is_open()) {
    cout << "Error: could not open working_manifest.txt" << endl;
    return;
  }

  // Using an ofstream to write to the saved manifest
  ofstream saved_file("saved_manifest.txt");
  if (!saved_file.is_open()) {
    cout << "Error: could not open saved_manifest.txt" << endl;
    working_file.close();
    return;
  }

  // Read the working manifest line by line and write it to the saved manifest
  string line;
  while (getline(working_file, line)) {
    saved_file << line << endl;
  }

  // Close both files
  working_file.close();
  saved_file.close();

  cout << "Saved manifest successfully." << endl;
}
