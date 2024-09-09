#include "include/airplane.hpp"
#include "include/passenger.hpp"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// Constants
const int rows = 12;
const int columns = 6;
const string seat_labels[columns] = {"A", "B", "D", "E", "F", "H"};

// Iterates through the seating chart to find any open seats
bool Airplane::is_full() {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      if (!seats[i][j].is_assigned) {
        return false;
      }
    }
  }
  return true;
}

// Initializes the plane's seating chart. It sets the attributes to each Seat
// object.
void create_seating_chart(Airplane &airplane) {
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      airplane.seats[i][j].seat_number = seat_labels[j] + to_string(i + 1);
      airplane.seats[i][j].is_assigned = false;
      if (i == 0)
        // Seats in the first row are first class
        airplane.seats[i][j].level = "First Class";
      else if (i < 4)
        // Seats in rows 2-4 are business class
        airplane.seats[i][j].level = "Business Class";
      else
        // Seats in rows 5-12 are economy class
        airplane.seats[i][j].level = "Economy Class";
    }
  }
}

// Displays the seating chart. It shows the seat number and whether it is
// assigned or not.
void display_seating_chart(Airplane &airplane) {
  cout << "Seating Chart" << endl;
  cout << "X = Assigned, O = Open" << endl;
  cout << "   A B  D E F  H" << endl; // Top labels with aisles

  for (int i = 0; i < rows; ++i) {
    cout << setw(2) << (i + 1) << " "; // Row number

    for (int j = 0; j < columns; ++j) {
      if (j == 2 || j == 5) {
        cout << " ";
      }
      cout << (airplane.seats[i][j].is_assigned ? 'X' : 'O') << " ";
    }
    cout << endl;
  }
}

// Comparator function to sort passengers by seat number
bool seat_comparator(const Passenger &a, const Passenger &b) {
  if (a.seat.seat_number.length() != b.seat.seat_number.length()) {
    return a.seat.seat_number.length() < b.seat.seat_number.length();
  }
  return a.seat.seat_number < b.seat.seat_number;
}

// Saves the manifest to the working_manifest.txt file (or whatever name
// specified) to be saved by an employee.
void save_manifest(Airplane &airplane, string file_name) {
  // Sort the passenger list by seat number using the comparator function
  sort(airplane.passenger_list.begin(), airplane.passenger_list.end(),
       seat_comparator);

  // Open the file for writing
  ofstream file(file_name);
  if (!file.is_open()) {
    cout << "Error: could not open file" << endl;
    return;
  }

  // Write the sorted passenger list to the file
  for (int i = 0; i < airplane.passenger_list.size(); ++i) {
    file << airplane.passenger_list[i].name << endl;
    file << airplane.passenger_list[i].seat.seat_number << endl;
    file << airplane.passenger_list[i].seat.level << endl;
  }

  // Close the file (means we're done writing to it)
  file.close();
}

// Reads the manifest from a file (in this case it would be the
// saved_manifest.txt file) and populates the airplane's seating chart and
// passenger list
void read_manifest(Airplane &airplane, string file_name) {
  ifstream file(file_name);
  // Check if the file is open (meaning it was successfully opened for reading)
  if (!file.is_open()) {
    cout << "Error: could not open file" << endl;
    return;
  }

  // if the file is empty, return
  if (file.peek() == ifstream::traits_type::eof()) {
    file.close();
    return;
  }

  // Copy the saved_manifest file content to the working_manifest file
  ofstream working_file("working_manifest.txt");
  if (!working_file.is_open()) {
    cout << "Error: could not open working manifest file" << endl;
    file.close();
    return;
  }

  // Copy the content of the saved_manifest file to the working_manifest file
  working_file << file.rdbuf();
  // Close the working_manifest file
  working_file.close();
  // Clear the saved_manifest file
  file.clear();
  // Seek back to the beginning of the file
  file.seekg(0);

  // I learned about the clear and seekg functions from the following link:
  // https://stackoverflow.com/questions/5343173/return-to-the-beginning-of-file-after-reading-it

  // Read the manifest file and populate the airplane's seating chart and
  // passenger list
  string name, seat_number, level;
  while (getline(file, name) && getline(file, seat_number) &&
         getline(file, level)) {
    // Create a new Passenger object and populate its attributes
    Passenger passenger;
    passenger.name = name;
    passenger.seat.seat_number = seat_number;
    passenger.seat.level = level;
    passenger.seat.is_assigned = true;

    // Find row and column based on seat number
    int row = stoi(seat_number.substr(1)) - 1;
    char col = seat_number[0];
    int col_index = col - 'A';
    if (col > 'B')
      col_index--; // Adjust for aisles

    // Assign the seat to the passenger and mark the seat as assigned
    airplane.seats[row][col_index].seat_number = seat_number;
    airplane.seats[row][col_index].level = level;
    airplane.seats[row][col_index].is_assigned = true;

    // Add the passenger to the list
    airplane.passenger_list.push_back(passenger);
  }

  // Close the file (means we're done reading from it)
  file.close();
}
