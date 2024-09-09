/*
Laith Taher (5/7/2024)

*  Print the sum of products of odd and even numbers from 1 to 10
*  Print alternate characters from 'A' to 'Z' in the reverse order starting with 'Z'


*  Ouput of the program should look like:
    The value of limit is 10
    The Sum = 4785
    Z X V T R P N L J H F D B
*/

// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments) at the end of file.

#include <iostream>
using namespace std;

int main() {
 
// Initialized the necessary variables to their proper values.
  int limit = 10, even_product = 1, odd_product = 1, sum;

// Moved the char initialization to the loop of where it is used.

  cout << "The value of limit is " << limit << endl;

// Changed the initialization of the for loop.  
  for (int i = 1; i <= limit; ++i) {
// Adjusted the for loop logic.
    if (i % 2 == 1) {
      odd_product *= i;
    } else {
      even_product *= i;
    }
  }

  sum = even_product + odd_product;
  cout << "The Sum = " << sum << "\n";

// char c is initialized here instead of at the top of the function.
  for (char c = 'Z'; c >= 'A'; c -= 2) {
// Used a variable within scope.
    cout << c << " ";
  }
  cout << endl;

  return 0;
}

/*
Initialized the limit variable to 10, instead of 0. This caused the program to not run like it was supposed due to the loop just returning 0.

Initialized the even_product and odd_product variables to 1 instead of 0. Multiplying 0 by any number is 0, so the output would always result in 0.

Redefined c in the for loop where it is being used instead of keeping it in the main scope of the program.

Adjusted i within the for loop to begin at 1. This is because if it were to start at 0, the result of any mulitplication done would be 0.

Swapped where even_product and odd_product were in the for loop. The condition "i % 2 == 1" is the calculation of an odd number. So I made sure that the odd_product variable was being assigned to this value instead of even_product.

Replaced "i" with "c" in the letter printing for loop. This was because "i" was not defined in the scope of the for loop, and "c" was a char we had already defined. Furthermore, the conditional statements in the for loop used "c".
*/
