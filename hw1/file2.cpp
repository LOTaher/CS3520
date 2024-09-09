/*  
Laith Taher (5/7/2024)

Automatic dialing machine
Delivers a sales message
Needs to print all possible combinations of areacode and exchangecode with the last 4 digits


Example : If areacode = 617, exchange = 424
Output : 
"I am calling to tell you to buy a subscription to Dogs Monthly Magazine!"
617-424-0001
617-424-0002
617-424-0003
...
617-424-9998
617-424-9999
*/

// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments) at the end of file.

// Edited import statement
#include<iostream>
// Imported the string library
#include<string>
// Included namespace to use the std library without requiring std:: before functions
using namespace std;
  
int main(){
   // Changed the data type to int
   int digit1, digit2, digit3, digit4; 
   string areaCode, exchange;
   cout<< "Hello, I am a telemarketing calling making program.\n";
   cout<< "Enter a three-digit area code "; 
   // This is meant to be an input, so it was changed to be cin>>
   cin>>areaCode; 
   cout<<"Enter a three-digit exchange to call "; 
   cin>>exchange; 
   cout<< "I am calling to tell you to buy a subscription to Dogs Monthly!\n";
   // Incrementing the digits instead of decrementing
   for(digit1 = 0; digit1 <= 9; ++digit1){ 
        for(digit2 = 0; digit2 <=9; ++digit2){ 
            for(digit3 = 0; digit3 <=9; ++digit3) { 
                for(digit4 = 0; digit4 <=9; ++digit4) {
                    cout<< areaCode << "-" << exchange << "-" << digit1 << digit2 << digit3 << digit4 << endl;
                }
            }
        
        }
    }
    
   // Removed the "Calls completed" output due to it not being required in the expected output.
   return 0;
}

/*
To include the iostream library, "#" should appear before include, and not "%"

Added #include<string> to include the string library.

areaCode and exchange were not able to be initialized due to the string library not being imported.

To avoid repeating the use of std:: before std library functions you can write the line "using namespace std;" at the top of the program

digit1, digit2, digit3 and digit4 variables would not run as they should due to them being defined as chars instead of ints

areaCode and exchange are expected to be inputted by the user, however that couldn't happen because of the use of cout<< instead of cin>>

Digit was incorrect due to the digits being decremented in each of the for loops instead of being incremented.
*/
