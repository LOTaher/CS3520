// Aaryan Jain and Laith Taher

#include <iostream>
#include <string>
using namespace std;

// this class represents a person
class Person {
    private:
        float height;
        static int age;
    public:
        string first_name;
        static string grade;
        void print_memory_addresses();

        // creating a class constructor
        Person(float h) {
            height = h;
        }
        void introduce_yourself() {
            cout << "Hello my name is: " << first_name << endl;
        }
};

// printing values and addresses of each of the fields
void Person::print_memory_addresses() {
    cout << first_name << "'s addresses" << endl;
    cout << "Value of height: " << height << ", address of height: " << &height << endl;
    cout << "Value of age: " << age << ", address of age: " << &age << endl;
    cout << "Value of first name: " << first_name << ", address of first name: " << &first_name << endl;
    cout << "Value of grade: " << grade << ", address of grade: " << &grade << endl;
}

// initializing static variables
int Person::age = 20;
string Person::grade = "Junior";

int main() {
    // initialize two Person objects
    Person aaryan(5.6);
    Person laith(6.0);

    // printing objects memory addresses
    cout << "Aaryan's memory address is " << &aaryan << endl;
    cout << "Laith's memory address is " << &laith << "\n\n";

    // initializing first names
    aaryan.first_name = "Aaryan";
    laith.first_name = "Laith";
    
    // calling a public method
    aaryan.introduce_yourself();
    laith.introduce_yourself();
    cout << endl;

    // printing the memory addresses of all the fields of each object
    aaryan.print_memory_addresses();
    cout << endl;
    laith.print_memory_addresses();
}


/*
We noticed that the address of age and grade (our static variables) for both objects is the same. 
We assume this means that because they are static variables, they are shared accross objects so 
it would make sense for their reference to be the same within different objects as well.

We noticed that the height field shares the same memory address as our class objects. 
We assume this is because height was defined in the class’ constructor and is the first field in the class. 
We noticed that the second to last bit of our two defined objects are different. We believe this 
is because they are apart of the same defined class and are just different defined objects.

For the first_name field, we noticed that the second to last bit might be related to the object as the second to 
last bit for the first_name corresponded to the second to last bit of the object for both aaryan and laith. And then we
believe the last bit could be correlated to the field which is why the last bit for both objects first_name field is the same as they are
the same field.
*/
