// This program allocated memory for an NxM integer array dynamicaly
// The program then prints the 2D array in a matrix form using a combination of
// * and [] operators Note: You can't use ** or [][] for printing the values
// (use a combination of * and [] only.

// Number of bugs/errors : 6

#include <cstdlib>
#include <iostream>
using namespace std;

int main() {
  int N = 3, M = 5;
  int i, j;
  // Changed sizeof(int) to sizeof(int*) because we are allocating memory for an
  // array of pointers, and not an array of integers
  int **d_array = (int **)malloc(
      N * sizeof(int *)); // Allocating memory for 2D array (N rows)
                          // Added a semicolon within the if statement
  for (i = 0; i < N; i++)
    d_array[i] = (int *)malloc(
        M * sizeof(int)); // Allocating memory for each row with M columns)
  // Initializing 2D array using [ ][ ] notation
  printf("Initializing array values!\n");
  for (i = 0; i < N; i++) {
    for (j = 0; j < M; j++) {
      // Replaced the , at the end of the line to a ;
      // Changed from d_array + i + j to d_array[i] + j because we are accessing
      // a 2D array
      *(d_array[i] + j) = i + j;
    }
  }
  // Using cout instead of printf
  // Accessing 2D array using a combination of * and [] notation
  cout << "\n";
  for (i = 0; i < N; i++) {
    // Changed to j < M 
    for (j = 0; j < M; j++) {
      // Dereferencing the pointer 
      cout << *(d_array[i] + j) << " ";
    }
    cout << "\n";
  }
  // Deallocating 2D array
  for (i = 0; i < N; i++)
    // Changed d_array + i to d_array[i] because we are freeing the memory
    // allocated for each row, instead of the entire array
    free(d_array[i]);
  free(d_array);
}

/*
Changed sizeof(int) to sizeof(int*) in the first malloc call because we are allocating memory for an array of pointers, not an array of integers.
Removed incorrect comment about adding a semicolon within the if statement.
Changed d_array + i + j to d_array[i] + j in the initialization loop because we are accessing a 2D array and need to correctly reference each element.
Replaced the comma , at the end of the initialization line with a semicolon ; to fix the syntax error.
Used cout instead of printf for printing the array to since there were no necessary format specifiers.
Corrected the deallocation loop by changing d_array + i to d_array[i] because we need to free the memory allocated for each row, not the entire array at once.
Changed the loop condition in the printing loop to j < M to correctly iterate over the columns of the 2D array.
*/
