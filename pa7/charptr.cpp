// This program should read any string (including spaces) from the user and print it using a character pointer
// The program is setup to use pointer offset notation to get each character of the string

// Number of bugs/errors : 8

// Changed to include iostream, not stdio
#include <iostream>

using namespace std;

// Main should return an int not a void
int main(void)
{
  // Increase the buffer size to allow for bigger string input
  char s[100];
  // Changed cPtr to be a char pointer
  char *cPtr;
  // Adding a cout to prompt the user to enter a string
  cout << "Enter a string: ";
  // Using the getline function to read a full input INCLUDING spaces
  cin.getline(s, 100);

  cPtr = s;

  // Changed the while loop to use the correct condition, it is now checking the pointed value, not the pointer itself
  while (*cPtr != '\0')
  {
    // Print the character the pointer is pointing to
    cout << *cPtr; 
    // Increment the pointer to point to the next character
    cPtr++;
  }
  cout << "\n";
  return 0;
}

/*
Changed #include <stdio> to #include <iostream> 
Changed the return type of main from void to int.
Increased the buffer size of s to 100 to handle longer strings.
Changed char cPtr to char* cPtr to make it a pointer.
Used cin.getline(s, 100) instead of cin >> s to read a string with spaces.
Assigned cPtr to the start of the string with cPtr = s.
Changed the while loop condition to *cPtr != '\0' to check the value pointed by cPtr.
Printed the character pointed by cPtr with cout << *cPtr.
Incremented the pointer with cPtr++ to move to the next character.
Added a prompt for user input.
*/
