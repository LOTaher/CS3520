// Program to read integers into a 3X3 matrix and display them
// Todo: Fix bugs and makesure program works as intended.
// for each bug fix, add a comments specifying what you fixed.

#include <iostream>
using namespace std;

// Changed the size parameter to be of type int
void display(int Matrix[3][3], int size)
{
    // Fixed the inner loop to increment 'j' instead of 'i'
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // Removed comma for better formatting
            cout << Matrix[i][j] << " ";
        }
        cout << endl; // Added semicolon
    }
}

int main(void)
{
    int size = 3;
    // Changed the size of the matrix to be 3x3
    int Matrix[3][3];
    // Changed from cin to cout
    cout << "Enter 9 elements of the matrix:" << endl;
    // defined int i
    for (int i = 0; i < size; i++)
    {
        // moved j's definition in the loop
        for (int j = 0; j < size; j++)
        {
            // Fixed indexing to fill the matrix row-wise
            cin >> Matrix[i][j]; 
        }
    }
    // Removed the address operator to pass in matrix properly
    display(Matrix, size);
    return 0;
}

/*
Changed the size of the matrix to be 3x3.
Changed 'cin <<' to 'cout >>' for displaying the prompt.
Defined the loop variable 'i' in the for loop.
Moved 'j's' definition inside the for loop initialization.
Fixed indexing in the matrix input loop to fill it row-wise.
Removed the address operator to pass the matrix correctly to the display function.
Changed the size parameter in the display function to be of type int.
Fixed the inner loop in the display function to increment 'j' instead of 'i'.
Removed the comma in the display function output for better formatting.
Added a semicolon after the cout statement in the display function.
*/
