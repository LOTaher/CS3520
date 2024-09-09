// Program to check if the user-provided number is a palindrome

// TODO: Fix the bugs and make sure the program runs as expected.
// Provide a brief comment identifying each bug fixed.

#include <iostream>

// Must include using namespace std to use cout and cin
using namespace std;
// the return value of your func should be true / false only

// moved function above main so it can be used
// renamed to is_palindrome to make it more descriptive
// removed the result parameter
bool is_palindrome(int n)
{

    // Save the original inputted number for a comparison
    int original = n;
    int reversed = 0;

    // Switched the conditional to n > 0 to avoid the loop never running.
    while (n > 0)
    {
        // Using the modulus operator for the remainder
        // remainder is now an int
        int remainder = n % 10;
        // Declared variable called reverse instead of temp to accumulate the reversed number
        reversed = reversed * 10 + remainder;
        // Dividing the number by 10 to get the next digit
        n /= 10;
    }

    // Conditional statements like if then, else false are unnecessary and can be solved by returning the comparison
    return original == reversed;
}


// Changed the return type of the function to int
int  main()
{
        // Input shouldn't have a value before the user input
        // Changed input from char to int
        int input;
        cout << "enter an integer please";
        // Added a blank line for formatting
        cout << endl;
        // Added a cin statement to get the user input
        cin >> input;
        // bool needs to be put before returned_val since the is_palindrome function returns a boolean value
        bool returned_val = is_palindrome(input);
        if (returned_val)
        {
                // Added quotes to the cout string
                cout << "It is not a palindrome" << endl;
        }
        else
        {
                cout << "It is a palindrome" << endl;
        }

        // Added return 0; to return an integer value
        return 0;
}

/*
Changed void main() to int main() 
Changed char input = 1001; to int input; to allow for user input.
Fixed function call returned_val = func2(return_value_function); to returned_val = is_palindrome(input);.
Added proper return type and signature to is_palindrome function.
Added missing cin statement to read user input.
Fixed logical errors in the is_palindrome function, including properly reversing the number.
Ensured the correct comparison and return of boolean values.
Added semicolons and quotes around strings in cout statements.
*/
