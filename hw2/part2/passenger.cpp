#include "include/passenger.hpp"
#include "include/airplane.hpp"
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

// Function that prints the passenger menu after logging in
void passenger_login(Airplane &airplane, Passenger &passenger) {
  while (true) {
    cout << "Welcome, " << passenger.name << "! \n";
    cout << "Please select an option: \n";
    cout << "1. Display the seating map/chart \n";
    cout << "2. Choose a seat with our automated system\n";
    cout << "3. Manually choose a seat \n";
    cout << "4. Change or cancel seat assignment \n";
    cout << "5. Print a boarding pass \n";
    cout << "6. Quit \n";

    int choice;
    cin >> choice;

    if (cin.fail() || choice < 1 || choice > 6) {
      cout << "Invalid input. Please try again. \n";
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
      // Choose a seat randomly
      choose_seat_randomly(airplane, passenger);
      break;
    case 3:
      // Manually choose a seat
      manually_choose_seat(airplane, passenger);
      break;
    case 4:
      // Change or cancel seat assignment
      change_or_cancel_seat_assignment(airplane, passenger, false);
      break;
    case 5:
      // Print a boarding pass
      print_boarding_pass(airplane, passenger);
      break;
    case 6:
      // On the quit, do another save manifest so no data gets lost
      save_manifest(airplane, "working_manifest.txt");
      cout << "Goodbye, " << passenger.name << "!\n";
      return;
    }

    // Clear the buffer and wait for the enter key to go back to the menu
    cout << "\nPress Enter to return to the main menu..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
  }
}

// Function that selects a random seat for the passenger
void choose_seat_randomly(Airplane &airplane, Passenger &passenger) {
  // Check if the plane is full
  if (airplane.is_full()) {
    cout << "The current plane is full. Next flight leaves in 3 hours. \n";
    return;
  }

  // Check if the passenger already has a seat
  if (passenger.seat.is_assigned) {
    cout << "You have already been assigned a seat. \n";
    cout << "You are set to be sitting in seat " << passenger.seat.seat_number
         << " in " << passenger.seat.level << ". \n";
    cout << "Return to the menu to change or cancel your seat assignment. \n";
    return;
  }

  // Assign a random seat
  int row, column;
  while (true) {
    row = rand() % 12;
    column = rand() % 6;
    if (!airplane.seats[row][column].is_assigned) {
      airplane.seats[row][column].is_assigned = true;
      passenger.seat = airplane.seats[row][column];
      cout << "Seat assigned successfully! \n";
      cout << "You have been assigned seat " << passenger.seat.seat_number
           << " in " << passenger.seat.level << ". \n";
      return;
    }
  }

  // Save manifest
  save_manifest(airplane, "working_manifest.txt");
}

// Function that allows the passenger to manually choose a seat
void manually_choose_seat(Airplane &airplane, Passenger &passenger) {
  // Check if the plane is full
  if (airplane.is_full()) {
    cout << "The current plane is full. Next flight leaves in 3 hours. \n";
    return;
  }

  // Check if the passenger already has a seat
  if (passenger.seat.is_assigned) {
    cout << "You have already been assigned a seat. \n";
    cout << "You are set to be sitting in seat " << passenger.seat.seat_number
         << " in " << passenger.seat.level << ". \n";
    cout << "Return to the menu to change or cancel your seat assignment. \n";
    return;
  }

  // Display the seating chart for the passenger to reference
  display_seating_chart(airplane);

  // Provide the passenger with the option to choose a seat from any class/level
  char choice;
  while (true) {
    cout << "Which seat class would you like to sit in? \n";
    cout << "Please type 'F' for first class \n";
    cout << "Please type 'B' for business class \n";
    cout << "Please type 'E' for economy class \n";

    cin >> choice;

    // Check if the input is valid
    if (cin.fail() || (choice != 'F' && choice != 'B' && choice != 'E')) {
      cout << "Invalid input. Please try again. \n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
      break;
    }
  }

  // Initialize the loop variables based on the passenger's class/level choice
  int row_start, row_end;
  if (choice == 'F') {
    row_start = 0;
    row_end = 1;
  } else if (choice == 'B') {
    row_start = 1;
    row_end = 4;
  } else {
    row_start = 4;
    row_end = 12;
  }

  while (true) {
    // Display the seats that do not have the trait is_assigned within the
    // level's section
    cout << "Available seats: \n";
    for (int i = row_start; i < row_end; ++i) {
      for (int j = 0; j < 6; ++j) {
        if (!airplane.seats[i][j].is_assigned) {
          cout << airplane.seats[i][j].seat_number << " ";
        }
      }
    }
    cout << "\nSelect your seat: ";
    string seat;
    cin >> seat;

    // Validate the seat input
    if (seat.length() < 2 || seat.length() > 3) {
      cout << "Invalid seat number. Please try again. \n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    char seat_col = seat[0];
    int seat_row = stoi(seat.substr(1)) - 1;

    if (seat_col < 'A' || seat_col > 'H' || seat_col == 'C' ||
        seat_col == 'G' || seat_row < row_start || seat_row >= row_end) {
      cout << "Invalid seat number. Please try again. \n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    int row = seat_row;
    int column = seat_col - 'A';
    if (seat_col > 'B')
      // Adjust for aisles (C and G)
      column -= 1;

    // Check if the seat is already assigned
    if (airplane.seats[row][column].is_assigned) {
      cout << "Seat is already occupied. Please try again. \n";
    } else {
      // Assign the seat to the passenger
      airplane.seats[row][column].is_assigned = true;
      passenger.seat = airplane.seats[row][column];
      cout << "Seat assigned successfully! \n";
      cout << "You have been assigned seat " << passenger.seat.seat_number
           << " in " << passenger.seat.level << ". \n";
      return;
    }
  }
  // Save manifest
  save_manifest(airplane, "working_manifest.txt");
}

// Function that changes the passenger's seat assignment
void change_seat(Airplane &airplane, Passenger &passenger, bool is_employee) {
  // If the user is an employee, prompt them with a new menu to change the seat
  if (is_employee) {
    cout << "Please enter which seat you want " << passenger.name
         << " to sit in: ";

    string seat;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, seat);
    if (seat.length() < 2 || seat.length() > 3) {
      cout << "Invalid seat number. Please try again. \n";
      return;
    }

    // Validate the seat input
    char seat_col = seat[0];
    int seat_row = stoi(seat.substr(1)) - 1;

    if (seat_col < 'A' || seat_col > 'H' || seat_col == 'C' ||
        seat_col == 'G' || seat_row < 0 || seat_row >= 12) {
      cout << "Invalid seat number. Please try again. \n";
      return;
    }

    int row = seat_row;
    int column = seat_col - 'A';
    if (seat_col > 'B') {
      // Adjust for aisles (C and G)
      column -= 1;
    }

    // Check if the seat is already assigned
    if (airplane.seats[row][column].is_assigned) {
      cout << "Seat is already occupied. Please try again. \n";
      return;
    }

    // Free the previous seat
    int old_row = passenger.seat.seat_number[1] - '1';
    int old_column = passenger.seat.seat_number[0] - 'A';
    if (passenger.seat.seat_number[0] > 'B') {
      old_column -= 1; // Adjust for aisles (C and G)
    }

    // Assign the new seat to the passenger
    airplane.seats[old_row][old_column].is_assigned = false;
    airplane.seats[row][column].is_assigned = true;
    passenger.seat = airplane.seats[row][column];
    cout << "Seat changed successfully! \n";

    // Save manifest
    save_manifest(airplane, "working_manifest.txt");
    return;

  } else {
    // Check if the passenger already has a seat
    if (!passenger.seat.is_assigned) {
      cout << "You have not been assigned a seat yet. \n";
      cout << "Please return to the menu to choose a seat. \n";
      return;
    }

    int choice;
    while (true) {
      // Provide a menu for the passenger to upgrade or downgrade their seat
      cout << "You are currently assigned to seat "
           << passenger.seat.seat_number << " in " << passenger.seat.level
           << ". \n";
      cout << "Please select whether you would like to upgrade or downgrade "
              "your seat: \n";
      cout << "1. Upgrade to a higher class \n";
      cout << "2. Downgrade to a lower class \n";
      cout << "3. Return to the menu \n";

      cin >> choice;
      if (cin.fail() || (choice != 1 && choice != 2 && choice != 3)) {
        cout << "Invalid input. Please try again. \n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      } else {
        break;
      }
    }

    // Not using a switch statement here.
    int row_start, row_end;
    if (choice == 1) {
      // You cannot upgrade to a higher class if you are already in first class
      if (passenger.seat.level == "First Class") {
        cout << "You are already in the highest class. \n";
        return;
      } else if (passenger.seat.level == "Business Class") {
        // Initialize the loop variables based on the business class section
        row_start = 0;
        row_end = 1;
      } else {
        row_start = 1;
        row_end = 4;
      }
    } else if (choice == 2) {
      // You cannot downgrade to a lower class if you are already in economy
      // class
      if (passenger.seat.level == "Economy Class") {
        cout << "You are already in the lowest class. \n";
        return;
      } else if (passenger.seat.level == "Business Class") {
        // Initialize the loop variables based on the economy class section
        row_start = 4;
        row_end = 12;
      } else {
        // Initialize the loop variables based on the first class section
        row_start = 1;
        row_end = 4;
      }
    } else {
      return; // Return to the menu
    }

    while (true) {
      // Provide the available seats within the new class/level
      cout << "Available seats: \n";
      for (int i = row_start; i < row_end; ++i) {
        for (int j = 0; j < 6; ++j) {
          if (!airplane.seats[i][j].is_assigned) {
            cout << airplane.seats[i][j].seat_number << " ";
          }
        }
      }
      cout << "\nSelect your seat (e.g., A1, B5, etc.): ";
      string seat;
      cin >> seat;

      if (seat.length() < 2 || seat.length() > 3) {
        cout << "Invalid seat number. Please try again. \n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
      }

      // Validate the seat input
      char seat_col = seat[0];
      int seat_row = stoi(seat.substr(1)) - 1;

      if (seat_col < 'A' || seat_col > 'H' || seat_col == 'C' ||
          seat_col == 'G' || seat_row < row_start || seat_row >= row_end) {
        cout << "Invalid seat number. Please try again. \n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
      }

      int row = seat_row;
      int column = seat_col - 'A';
      if (seat_col > 'B')
        // Adjust for aisles (C and G)
        column -= 1;

      // Check if the seat is already assigned
      if (airplane.seats[row][column].is_assigned) {
        cout << "Seat is already occupied. Please try again. \n";
      } else {
        // Free the previous seat
        int old_row = passenger.seat.seat_number[1] - '1';
        int old_column = passenger.seat.seat_number[0] - 'A';
        if (passenger.seat.seat_number[0] > 'B')
          old_column -= 1; // Adjust for aisles (C and G)

        airplane.seats[old_row][old_column].is_assigned = false;

        // Assign the new seat to the passenger
        airplane.seats[row][column].is_assigned = true;
        passenger.seat = airplane.seats[row][column];
        cout << "Seat changed successfully! \n";
        cout << "You have been assigned seat " << passenger.seat.seat_number
             << " in " << passenger.seat.level << ". \n";
        return;
      }
    }
    // Save manifest
    save_manifest(airplane, "working_manifest.txt");
  }
}

// Function that cancels the passenger's seat assignment
void cancel_seat(Airplane &airplane, Passenger &passenger, bool is_employee) {
  // If the user is an employee, prompt them with a new menu to cancel a
  // passenger's seat
  if (is_employee) {
    cout << "Are you sure you want to cancel " << passenger.name
         << "'s seat assignment? \n";
    cout << "1. Yes \n";
    cout << "2. No \n";

    int choice;
    cin >> choice;
    if (cin.fail() || (choice != 1 && choice != 2)) {
      cout << "Invalid input. Please try again. \n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      return;
    }

    switch (choice) {
    case 1: {
      // Free the seat
      int row = passenger.seat.seat_number[1] - '1';
      int column = passenger.seat.seat_number[0] - 'A';
      if (passenger.seat.seat_number[0] > 'B')
        column -= 1;

      airplane.seats[row][column].is_assigned = false;
      passenger.seat.is_assigned = false;
      cout << "Seat assignment canceled successfully! \n";

      // Save change to the working manifest
      save_manifest(airplane, "working_manifest.txt");
      break;
    }
    case 2: {
      // Go back to the menu
      return;
    }
    }
  } else {
    // Check if the passenger already has a seat
    if (!passenger.seat.is_assigned) {
      cout << "You have not been assigned a seat yet. \n";
      cout << "Please return to the menu to choose a seat. \n";
      return;
    }

    int choice;
    while (true) {
      string name;
      // Confirm the passenger's name and seat number (credentials) before
      // canceling the seat
      cout << "Please enter your name to confirm the cancellation: ";
      cin >> name;
      if (cin.fail()) {
        cout << "Invalid input. Please try again. \n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
      } else if (name != passenger.name) {
        cout << "Name does not match your boarding pass. Please try again. \n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
      }
      string seat_number;
      cout << "Please enter your seat number to confirm the cancellation: ";
      cin >> seat_number;
      if (cin.fail()) {
        cout << "Invalid input. Please try again. \n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
      } else if (seat_number != passenger.seat.seat_number) {
        cout << "Seat number does not match your boarding pass. Please try "
                "again. \n";
        continue;
      }

      // Confirm the passenger's intent to cancel the seat assignment once the
      // credentials are verified
      cout << "You are currently assigned to seat "
           << passenger.seat.seat_number << " in " << passenger.seat.level
           << ". \n";
      cout << "Are you sure you want to cancel your seat assignment? \n";
      cout << "1. Yes \n";
      cout << "2. No \n";

      cin >> choice;

      if (cin.fail() || choice < 1 || choice > 2) {
        cout << "Invalid input. Please try again. \n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      } else {
        break;
      }
    }

    switch (choice) {
    case 1: {
      // Free the seat
      int row = passenger.seat.seat_number[1] - '1';
      int column = passenger.seat.seat_number[0] - 'A';
      if (passenger.seat.seat_number[0] > 'B')
        column -= 1;

      airplane.seats[row][column].is_assigned = false;
      passenger.seat.is_assigned = false;
      cout << "Seat assignment canceled successfully! \n";
      // Save manifest
      save_manifest(airplane, "working_manifest.txt");
      break;
    }
    case 2: {
      // Go back to the menu
      return;
    }
    }
  }
}

// Function that prints the change or cancel seat assignment menu
void change_or_cancel_seat_assignment(Airplane &airplane, Passenger &passenger,
                                      bool is_employee) {

  // First check if the passenger doesn't have a seat
  if (!passenger.seat.is_assigned) {
    cout << "You have not been assigned a seat yet. \n";
    cout << "Please return to the menu to choose a seat. \n";
    return;
  }

  int choice;
  while (true) {
    // Customize the menu message based on whether the user is an employee or a
    // passenger
    if (is_employee) {
      cout << passenger.name << " is currently assigned to seat "
           << passenger.seat.seat_number << " in " << passenger.seat.level
           << ". \n";
      cout << "As an employee, you can change or cancel this passenger's seat "
              "assignment. \n";
      cout << "1. Change seat \n";
      cout << "2. Cancel seat assignment \n";
      cout << "3. Return to the menu \n";
    } else {
      cout << "You are currently assigned to seat "
           << passenger.seat.seat_number << " in " << passenger.seat.level
           << ". \n";
      cout << "Would you like to change or cancel your seat assignment? \n";
      cout << "1. Change seat \n";
      cout << "2. Cancel seat assignment \n";
      cout << "3. Return to the menu \n";
    }

    cin >> choice;

    if (cin.fail() || choice < 1 || choice > 3) {
      cout << "Invalid input. Please try again. \n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
      break;
    }
  }

  switch (choice) {
  case 1:
    // Pass in the is_employee flag to determine whether the user is an employee
    // or a passenger
    change_seat(airplane, passenger, is_employee);
    break;
  case 2:
    // Pass in the is_employee flag to determine whether the user is an employee
    // or a passenger
    cancel_seat(airplane, passenger, is_employee);
    break;
  case 3:
    // Go back to the menu
    return;
  }
}

// Function that prints the boarding pass for the passenger
void print_boarding_pass(Airplane &airplane, Passenger &passenger) {
  if (!passenger.seat.is_assigned) {
    cout << "You have not been assigned a seat yet. \n";
    cout << "Please return to the menu to choose a seat. \n";
  } else {
    cout << " _______________________\n";
    cout << "/                       \\\n";
    cout << "|       Boarding Pass   |\n";
    cout << "|                       |\n";
    cout << "|  Name: " << setw(13) << left << passenger.name << "|\n";
    cout << "|  Seat: " << setw(13) << left << passenger.seat.seat_number
         << "|\n";
    cout << "|  Level: " << setw(12) << left << passenger.seat.level << "|\n";
    cout << "|                       |\n";
    cout << "|_______________________|\n";
    cout << "\\_______________________/\n";
  }
}
