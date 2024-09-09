/*
Laith Taher (5/7/2024)

This program determines if a nuumber is prime or composite.
*/

#include <iostream>
// Added the line due to the input and output functions not having std:: in front of them
using namespace std;

int main(void) {
  int num;
  // Initialized value to false
  bool factor_found = false;

  cout << "Enter Number:\n";
  cin >> num;
  // Adjusted the conditional statement to use less than (<) insead of equals (==)
  if (num < 0) {
    cout << num << " is negative\n";
    return 0;
  }
  // Adjusted the conditional statement to use or (||) instead of and (&&)
  if (num == 0 || num == 1) {
    cout << num << " is not prime or composite\n";
    return 0;
  }
  
  // Incrementing i instead of decrementing, changed i to 2 at the start of the loop
  for (int i = 2; i < num; i++) {
    if (num % i == 0) {
      factor_found = true;
      break;
    }
  }

  if (factor_found) {
    cout << num << " is a composite number\n";
  } else {
   cout << num << " is a prime number\n";
  }
}

/*
The cout and cin functions would not compile due to not including std:: before defining them. This was fixed by adding "using namespace std;" above the main function.

Even if there was no factor found, the program would bring out that any number is a composite number. This was solved by changed the initial value of factor_found to false instead of true.

The first for loop would check if num == 0 and then return an output saying that 0 is a negative number, however the logic should instead be if num < 0.

Since num can't be two values at once, using && in the conditional statement would never allow it to run. Instead, && should be changed to || to account for the possibility of num being 0 OR 1

Because the if statements above the for loop are already checking if num are 0 or 1, causing the program to not run properly, i should be initialized to 2 instead of 0 or 1. Furthermore, i should be getting incremented instead of decremented.
*/
