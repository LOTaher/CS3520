/*
Laith Taher (5/8/2024)

This program calculates the compound interest of an investment over 398 years.
It also calculates the amount of money in the investment for interest rates ranging from 2% to 10%
as well as calculates the amount of money in the investment if it was invested in the S&P 500 and NASDAQ.
*/

// Fig. 5.6: fig05_06.cpp
// Compound interest calculations with for.
#include <cmath> // standard math library
#include <iomanip>
#include <iostream>
using namespace std;

int main() {
  double principal = 11.00; // initial amount before interesta
  double snp500_return = 10.17; // average return of S&P500 since 1926
  double nasdaq_return = 10.4; // average return of NASDAQ since 1993

  // display headers
  cout << "Interest Rate (%)" << setw(30) << "Amount on deposit" << setw(30) << "S&P 500" << setw(30) << "NASDAQ" << endl;

  // set floating-point number format
  cout << fixed << setprecision(2);

  // calculate amount on deposit for each of ten years
  for (double rate = 2.0; rate <= 10.0; rate += 0.5) {
    // calculate new amount for specified year
    double amount = principal * pow(1.0 + rate / 100, 398);
    // calculate new amount for S&P500
    double snp500_amount = principal * pow(1.0 + snp500_return / 100, 398);
    // calculate new amount for NASDAQ
    double  nasdaq_amount = principal * pow(1.0 + nasdaq_return / 100, 398);

    // display the year and the amount for all three
    cout << rate << setw(30) << amount << setw(40) << snp500_amount << setw(40) << nasdaq_amount << endl;
  } // end for
} // end main

/*
The value of the investment increases as the interest rate increases, ranging from $29,124.67 at 2% interest to 
$327.85 trillion at 10% interest. However, the S&P 500 and NASDAQ yielded much higher returns. The S&P 500 yielded
$606.19 quadrillion and NASDAQ yielded $1.39 quadrillion. 

The current value of the Mona Lisa is $860 million, all three investments are worth much more than the present day Mona Lisa.
*/

/**************************************************************************
 * (C) Copyright 1992-2014 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
