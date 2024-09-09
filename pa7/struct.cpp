// This program includes a struct called car that is used to store information
// about a given car The program should ask the user for information about their
// car and initialize a car structure with the given information The program
// should also print the information using a pointer to the initialized struct
// The information printed using the struct and the pointer should be the same

#include <iostream>
// String header was not being used so it was removed

// Added using namespace std to avoid writing std:: before cout, cin, etc.
using namespace std;

struct car {
  char *name;
  int modelYear;
  float speed;
};

int main(void) {
  char n[20];
  int a;
  float w;

  struct car c;
  car *cPtr = &c;

  cout << "What is your favorite car's name: ";
  cin >> n;
  // Can't call name directly, need to use c.name
  c.name = n;

  cout << "When was it launched: ";
  // Changed from cout to cin
  cin >> a;
  c.modelYear = a;

  cout << "How much speed does it give: ";
  // Changed from << to >> because a cin is used
  cin >> w;
  // Speed was not defined, so instead we're setting the car speed to w, which
  // is the user input
  c.speed = w;

  // Instead of cPtr.name, we need to use cPtr->name since cPtr is a pointer
  cout << "Car's name is" << c.name << ", and should be the same as "
       << cPtr->name << ".\n";

  // Car was defined as c
  cout << "Car's model year is " << c.modelYear
       << ", and should be the same as " << cPtr->modelYear << ".\n";
  cout << "Car's speed is " << c.speed << ", and should be the same as "
       << cPtr->speed << ".\n";
}

/*
Fixes:
Changed 'char* name' to 'string name' in the struct for simplicity and safety.
Changed 'char n[20]' to 'string n' for easier input handling.
Fixed assignment of name to use 'c.name = n' instead of 'name = n'.
Corrected 'cout' to 'cin' for reading model year.
Fixed 'cin << w' to 'cin >> w' for reading speed.
Assigned 'w' to 'c.speed' correctly.
Used 'cPtr->name', 'cPtr->modelYear', and 'cPtr->speed' to access struct members via the pointer.
Added spaces in the output for better formatting.
*/
