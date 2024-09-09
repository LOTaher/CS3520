// Aaryan Jain and Laith Taher

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;


/*
    Psuedocode:

        write_2d_vector:
        -  Open + read the file 
        -  Convert eat line to an istringsteam and then loop through each number seperated by a comma
            - Add each row of numbers (after converting it to a double) to a vector to store all the numbers
            - Add the value of each number to a total sum variable and print it out after the loop
        - Calculate the total number of numbers in the vector
        - Determine the size of the 2d vector based on the total number of numbers
            - Use even dimensions up to 6x6 to find the smallest and most efficent matrix size which could hold all the numbers
        - Resize the 2d vector to match the new dimensions and populate all values to 0
        - Populate the 2d vector with the values from the list of all numbers
        - Create an output file stream and output all the values from each row of the 2d vector
            - Add a new line after each row's vector is printed to properly build the 2d matrix

        write_3d_array:
        - Open + read the file
        - Convert each line to an istringstream and loop through each number seperated by a comma
        - Add each number (after conversting it to a double) to a vector to store all the numbers
        - Add the value of each number to the total sum variable and print it out after the loop
        - Calculate the total number of numbers in the vector
        - Determine the size of the 3d array based on the total number of numbers
            - Use even dimensions up to 3x3x3 to find the smallest and most efficent matrix size which could hold all the numbers
        - Create a 3d array and populate all values to 0
        - Replace the necessary values of the 3d array with the values from the list of all numbers
        - Create an output file stream and output all the values from each row of the 3d array
            - Add a new line after each axis' array is printed to properly build the 3d matrix
*/


void write_2d_vector(string filename) {
    ifstream file(filename);
    vector<vector<double>> output;
    string line;
    vector<double> all_numbers;
    double sum_of_numbers;

    // Checking if the file exists
    if (!file) {
        cout << "Cannot open file" << endl;
        return;
    }

    // Reading all numbers from the file
    while (getline(file, line)) {
        istringstream ss(line);
        string num;
        while (getline(ss, num, ',')) {
            all_numbers.push_back(stod(num));
            sum_of_numbers += stod(num);
        }
    }

    cout << "Sum of all the numbers is: " << sum_of_numbers << endl;
    int total_size = all_numbers.size();
    
    // Determine the size of the 2D vector
    int line_length = 0;
    for (int i = 0; i <= 6; i++) {
        if (total_size <= i * i) {
            line_length = i;
            break;
        }
    }

    // Initializing the 2D vector with zeros
    output.resize(line_length, vector<double>(line_length, 0));

    // Filling the 2D vector with the numbers
    int index = 0;
    for (int i = 0; i < line_length; i++) {
        for (int j = 0; j < line_length; j++) {
            if (index < total_size) {
                output[i][j] = all_numbers[index++];
            }
        }
    }

    // Output the content of `output` into an output file
    ofstream outFile("2DVector.txt");
    for (int i = 0; i < line_length; i++) {
        for (int j = 0; j < line_length; j++) {
            outFile << output[i][j] << " ";
        }
        outFile << endl;
    }
}

void write_3d_array(string filename) {
    ifstream file(filename);
    string line;
    vector<double> all_numbers;
    double sum_of_numbers;

    // Checking if the file exists
    if (!file) {
        cout << "Cannot open file" << endl;
        return;
    }

    // Reading all numbers from the file
    while (getline(file, line)) {
        istringstream ss(line);
        string num;
        while (getline(ss, num, ',')) {
            all_numbers.push_back(stod(num));
            sum_of_numbers += stod(num);
        }
    }

    cout << "Sum of all the numbers is: " << sum_of_numbers << endl;
    int total_size = all_numbers.size();

    // Determine the size of the 3D array
    int x, y, z;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            for (int k = 1; k <= 3; k++) {
                if (total_size <= i * j * k) {
                    x = i;
                    y = j;
                    z = k;
                    break;
                }
            }
        }
    }

    // Create a 3D array
    double output[x][y][z];

    // Fill the 3d array with zeroes
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                output[i][j][k] = 0;
            }
        }
    }

    // Filling the 3D array with the numbers
    int index = 0;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                if (index < total_size) {
                    output[i][j][k] = all_numbers[index++];
                }
            }
        }
    }

    // Output the content of `output` into an output file
    ofstream outFile("3DArray.txt");
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                outFile << output[i][j][k] << " ";
            }
            outFile << endl;
        }
        outFile << endl;
    }
}

int main() {
    cout << "Running write_2d_vector" << endl;
    write_2d_vector("input.txt");

    cout << "Running write_3d_array" << endl;
    write_3d_array("input.txt");

    return 0;
}
