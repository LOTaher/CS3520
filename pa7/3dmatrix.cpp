// Program to read 3-dimensional matrix and display the elements as N^3 matrix
// TODO
// take the SIZE of the matrix as input from the user
// initize matrix using update_3d method (see comments below)
// display method must not be able to modify array elements (update the code as
// needed) display method must use a single loop/iterator to print the entire
// array with addresses display cannot use nested loops

#include <iostream>
// Added using namespace std; to avoid having to use std:: in front of cout and
// cin
using namespace std;

// changed function parameters to take in a double*** and an int
void update_3d(double ***Matrix_3d, int size);
// changed function parameters to take in a const double*** and an int
// added const because the matrix does not get modified
void display_1d(const double ***Matrix_3d, int size);

int main(void) {
  // prompt the user to initialize the matrix accordingly
  int size;
  cout << "Enter the size of the 3D matrix: ";
  cin >> size;

  // allocating the memory needed for the 3d matrix (represented as double***)
  double ***Matrix_3d = new double **[size];
  for (int i = 0; i < size; i++) {
    Matrix_3d[i] = new double *[size];
    for (int j = 0; j < size; j++) {
      Matrix_3d[i][j] = new double[size];
    }
  }

  // initialize the array to non-zero values (use scanf or random numbers
  // generator) changed from SIZE to size
  update_3d(Matrix_3d, size);
  // display the values
  // changed from SIZE to size
  display_1d((const double ***)Matrix_3d, size);

  // deallocate the memory
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      delete[] Matrix_3d[i][j];
    }
    delete[] Matrix_3d[i];
  }
  delete[] Matrix_3d;
  return 0;
}

// update_3d now takes in a double*** as a parameter
void update_3d(double ***matrix, int size) {
  // 3d matrix is initialized with random numbers using rand (1-9)
  cout << "Entering N^3 elements of the matrix:" << endl;
  int i = 0;
  for (; i < size; i++) {
    int j = 0;
    for (; j < size; j++) {
      int k = 0;
      for (; k < size; k++) {
        matrix[i][j][k] = rand() % 9;
      }
    }
  }
}

// update as needed. 1 'for' loop only with 1 iterator to print all values with
// addresses must not be able to update the array. Share any observations. added
// the args matrix (double***) and size (int)
void display_1d(const double ***matrix, int size) {

  // declaring i within the loop. i < s * s * s due to 3d matrix
  for (int i = 0; i < size * size * size; i++) {
    // calculating the dimensions of the matrix
    int x = i / (size * size);
    int y = (i % (size * size)) / size;
    int z = i % size;
    // adjusted cout expression to print the address of the matrix and the value
    // at the address
    cout << "Address: " << &matrix[x][y][z] << " Value: " << matrix[x][y][z]
         << "\n";
  }
}

/*
Removed the #define SIZE 7 and took SIZE as input from the user.
Added using namespace std; to avoid having to use std:: in front of cout and cin.
Changed function parameters of update_3d and display_1d to take in a double*** and an int.
Added const to display_1d parameters because the matrix does not get modified.
Prompted the user to input the size of the matrix.
Dynamically allocated memory for the 3D matrix based on the user-provided size.
Initialized the 3D matrix with random numbers using rand() in update_3d.
Updated display_1d to use a single loop with one iterator to print all values with addresses.
Calculated the dimensions of the matrix within display_1d using the loop iterator.
Deallocated the dynamically allocated memory for the 3D matrix at the end of main.
Replaced the hardcoded SIZE with size in function calls to use the user-provided size.
Ensured that display_1d cannot modify the array elements by using a const double*** parameter.
*/
