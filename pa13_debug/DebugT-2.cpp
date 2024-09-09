// Debug T-2
// Function template finds biggest of two or three objects. The function works on any data type which has greater than operator defined.

#include <iostream>
#include <string>
using namespace std;
template <class T>
// changed b to type T
void findBiggest(T a, T b, T c)
{
   T large = a;
   if (b > large)
      large = b;
   // changed to c > large
   if (c > large)
      large = c;
   // changed a from at the end of the cout to large
   cout << "The largest of " << a << " " << b << " " << c << " is " << large << endl;
}

template <class T>
void findBiggest(T a, T b)
{
   T large = a;
   // changed to b > large
   if (b > large)
      large = b;
   // changed from larger to large
   cout << "The larger of " << a << " " << b << " is " << large << endl;
}

class BankAccount
{
   friend ostream &operator<<(ostream &, const BankAccount &);

private:
   string name;
   int amount;

public:
   // added string &name to the constructor
   BankAccount(const string &name, const int);
   bool operator>(const BankAccount &);
};
BankAccount::BankAccount(const string &name, const int amount)
{
   // added this-> to name and amount to change the class members
   this->name = name;
   this->amount = amount;
}

// added const before BankAccount
ostream &operator<<(ostream &out, const BankAccount &bh)
{  
   // Moved the << out of the string, added bh. infront of the class members
   out << "Name " <<  bh.name << " Amount: " << bh.amount << endl;
   return out;
}

bool BankAccount::operator>(const BankAccount &bh)
{
   // changed from == to =
   bool flag = false;
   if (amount > bh.amount)
      flag = true;
   return flag;
}
int main()
{
   BankAccount bAA("A", 800);
   BankAccount bAB("B", 120);
   BankAccount bAC("C", 500);
   findBiggest(bAA, bAB);
   findBiggest(bAB, bAC);
   findBiggest(bAC, bAA);
   findBiggest(bAA, bAB, bAC);
   return 0;
}

/*
 * Fixes:
 * - changed the type of parameter `b` in the three-argument `findBiggest` function to type `T`.
 * - corrected the comparison in the three-argument `findBiggest` function to `c > large`.
 * - changed the output in the three-argument `findBiggest` function to display `large` instead of `a`.
 * - corrected the comparison in the two-argument `findBiggest` function to `b > large`.
 * - changed the output in the two-argument `findBiggest` function from `larger` to `large`.
 * - added `string &name` to the `BankAccount` constructor.
 * - added `this->` to `name` and `amount` in the `BankAccount` constructor to change the class members.
 * - added `const` before `BankAccount` in the `operator<<` function.
 * - moved the `<<` operator out of the string and added `bh.` in front of the class members in the `operator<<` function.
 * - corrected the assignment operator in the `BankAccount` `operator>` function from `==` to `=`.
 */
