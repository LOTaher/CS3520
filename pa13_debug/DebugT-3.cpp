// Debug T-3
// A container class for displaying a comma-separated list.
// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments)

#include <iostream>
#include <string>
using namespace std;
template <class T>
class CommaSeparatedList
{
private:
   T *data;
   int size;

public:
   CommaSeparatedList(T *d, int s);
   void printList();
};
template <class T>
// added pointer in front of d
CommaSeparatedList<T>::CommaSeparatedList(T *d, int s)
{
   data = d;
   size = s;
}
template <class T>
    // changed from < to >
    void CommaSeparatedList < T > ::printList()
{
   // changed >> to << to work for cout 
   cout << "Comma separated list:" << endl;
   for (int x = 0; x < size; ++x)
   {
      // changed from y to x
      cout << data[x];
      if (x != size - 1)
         cout << ", ";
   }
   cout << endl
        << endl;
}
class Book
{
   friend ostream &operator<<(ostream &, const Book &);

private:
   string title;
   int year;

public:
   void setBook(string, int);
};
void Book::setBook(string Title, int pr)
{
   title = Title;
   year = pr;
}

ostream &operator<<(ostream &out, const Book &b)
{
   // added a space after "in"
   out << b.title << " was published in " << b.year;
   // return out instead of ostream
   return out;
}

class Customer
{
   friend ostream &operator<<(ostream &, const Customer &);

private:
   string name;
   double balDue;

public:
   void setCustomer(string, double);
};
void Customer::setCustomer(string CustomerName, double pr)
{
   name = CustomerName;
   balDue = pr;
}
ostream &operator<<(ostream &out, const Customer &aCustomer)
{
   // made it a single space after the owes
   out << aCustomer.name << " owes $" << aCustomer.balDue;
   return out;
}

int main()
{
   int CommaSeparatedListSize;
   // Declare and assign values to four kinds of CommaSeparatedLists
   int someInts[] = {12, 34, 55, 77, 99};
   double someDoubles[] = {11.11, 23.44, 44.55, 123.66};
   Book someBook[2];
   someBook[0].setBook("Wizard of Oz", 1986);
   someBook[1].setBook("Harry Potter", 2000);
   Customer someCustomers[6];
   someCustomers[0].setCustomer("Zaps", 23.55);
   someCustomers[1].setCustomer("Martin", 155.77);
   someCustomers[2].setCustomer("Fine", 333.88);
   someCustomers[3].setCustomer("Torrence", 123.99);
   someCustomers[4].setCustomer("Richard", 20.06);
   someCustomers[5].setCustomer("Curtin", 56999.19);
   // Calculate size and create CommaSeparatedList objects
   CommaSeparatedListSize = sizeof(someInts) / sizeof(someInts[0]);
   CommaSeparatedList<int> CommaSeparatedListOfIntegers(someInts, CommaSeparatedListSize);
   CommaSeparatedListSize = sizeof(someDoubles) / sizeof(someDoubles[0]);
   CommaSeparatedList<double> CommaSeparatedListOfDoubles(someDoubles, CommaSeparatedListSize);
   // changed sizeif to sizeof
   CommaSeparatedListSize = sizeof(someBook) / sizeof(someBook[0]);
   CommaSeparatedList<Book> CommaSeparatedListOfBooks(someBook, CommaSeparatedListSize);
   CommaSeparatedListSize = sizeof(someCustomers) / sizeof(someCustomers[0]);
   CommaSeparatedList<Customer> CommaSeparatedListOfCustomers(someCustomers, CommaSeparatedListSize);
   // Use showList() with each CommaSeparatedList
   CommaSeparatedListOfIntegers.printList();
   CommaSeparatedListOfDoubles.printList();
   // spelled printList correctly
   CommaSeparatedListOfBooks.printList();
   CommaSeparatedListOfCustomers.printList();
   return 0;
}

/*
 * Fixes:
 * - changed the parameter `T d` to `T *d` in the `CommaSeparatedList` constructor.
 * - fixed the syntax of the `printList` method definition (`<` to `>`, `void` to `printList`).
 * - corrected the `cout` stream operator from `>>` to `<<` in the `printList` method.
 * - fixed the index variable in the `printList` method from `y` to `x`.
 * - added a space after "was published in" in the `operator<<` for the `Book` class.
 * - changed the return type from `ostream` to `out` in the `operator<<` for the `Book` class.
 * - fixed the spacing after "owes" in the `operator<<` for the `Customer` class.
 * - fixed the typo from `sizeif` to `sizeof` in the main function.
 * - corrected the spelling of `printList` in the main function for `CommaSeparatedListOfBooks`.
 */
