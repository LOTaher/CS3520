// Debug T-1
// Function template adds objects. The function works on any object which has '+' opertor defined.
// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments)

#include <iostream>
#include <string>
using namespace std;
template <class T>
// made y type T
T add(T x, T y)
{
   // changed sum from type U to T
   T sum = x + y;
   return sum;
}

class Person
{
   friend ostream &operator<<(ostream &, const Person &);

private:
   string lastName;
   string firstName;
   int age;

public:
   void setValues(string, string, int);
   // capitalized the p in Person
   Person operator+(Person);
};

// added const to the Person definition
ostream &operator<<(ostream &out, const Person &per)
{
   out << per.firstName << " " << per.lastName << " " << per.age << " years old" << endl;
   // added return statement
   return out;
}
void Person::setValues(string last, string first, int age)
{
   lastName = last;
   firstName = first;
   // added this-> to differentiate the age variables
   this->age = age;
}
Person Person::operator+(Person p)
{
   Person temp;
   temp.lastName = "of Age";
   temp.firstName = "Sum";
   // set the temp.age to the sume of the inputted person's age + the current person's age
   temp.age = p.age + this->age;
   return temp;
}

int main()
{
   int a = 7, b = 26, c;
   double d = 39.25, e = 2.01, f;
   Person g, h, i;
   g.setValues("Mitchell", "Donald", 40);
   h.setValues("Clayton", "Rita", 35);
   c = add(a, b);
   f = add(d, e);
   i = add(g, h);
   cout << c << endl;
   cout << f << endl;
   cout << i << endl;
   return 0;
}

/*
 * Fixes:
 * - added type `T` to parameter `y` in the template function `add`.
 * - changed the type of `sum` from `U` to `T` in the template function `add`.
 * - added a return statement to the overloaded `operator<<` for `Person`.
 * - corrected the parameter type in the `Person` class's `operator+` from lowercase `person` to `Person`.
 * - added `const` to the `Person` parameter in the `operator<<` function to make it a constant reference.
 * - added `this->` to `age` in the `setValues` function to differentiate between the parameter and the member variable.
 * - corrected the logic in the `operator+` function of the `Person` class to sum the ages correctly.
 * - specified the return type of the `operator<<` function as `ostream&`.
 */
