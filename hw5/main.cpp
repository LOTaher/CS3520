#include "game.hpp"
#include <cstdlib>  
#include <ctime>    
#include <iostream>
#include <string>
#include <sstream> 

using namespace std;

int get_input_with_default(const string& prompt, int default_value) {
    cout << prompt;
    string input;
    getline(cin, input);
    if (input.empty()) {
        return default_value;
    }
    stringstream ss(input);
    int value;
    ss >> value;
    if (ss.fail() || value < 0) {
        cout << "Invalid input. Using default value of " << default_value << "." << endl;
        return default_value;
    }
    return value;
}

bool get_bool_input_with_default(const string& prompt, bool default_value) {
    cout << prompt;
    string input;
    getline(cin, input);
    if (input.empty()) {
        return default_value;
    }
    stringstream ss(input);
    int value;
    ss >> value;
    if (ss.fail() || (value != 0 && value != 1)) {
        cout << "Invalid input. Using default value of " << default_value << "." << endl;
        return default_value;
    }
    return static_cast<bool>(value);
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "Welcome to the Predator-Prey Simulation!" << endl;

    int num_doodlebugs = get_input_with_default("How many doodlebugs would you like to start with? Enter nothing to use the default value of 15: ", 15);
    int num_ants = get_input_with_default("How many ants (both male and female) would you like to start with? Enter nothing to use the default value of 50: ", 50);
    int num_queens = get_input_with_default("How many queens would you like to start with? Enter nothing to use the default value of 2: ", 2);
    int width = get_input_with_default("How many rows would you like the grid to have? Enter nothing to use the default value of 100: ", 100);
    int height = get_input_with_default("How many columns would you like the grid to have? Enter nothing to use the default value of 100: ", 100);
    bool fast_forward = get_bool_input_with_default("Would you like to fast forward the simulation? Enter 1 for yes or 0 for no. Enter nothing to use the default value of 0: ", false);

    if (num_doodlebugs < 1) {
        cout << "The number of doodlebugs must be at least 1." << endl;
        return 1;
    }
    if (num_ants < 1) {
        cout << "The number of ants must be at least 1." << endl;
        return 1;
    }
    if (num_queens < 1) {
        cout << "The number of queens must be at least 1." << endl;
        return 1;
    }

    if (num_doodlebugs + num_ants + num_queens > width * height) {
        cout << "The total number of doodlebugs, ants, and queens must be less than or equal to the number of cells in the grid." << endl;
        return 1;
    }

    if (width < 10 || height < 10) {
        cout << "The grid size is too small. Please use a larger grid." << endl;
        return 1;
    }

    Game game(width, height, num_doodlebugs, num_ants, num_queens, fast_forward);
    game.run();

    return 0;
}
