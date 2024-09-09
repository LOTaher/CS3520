// The goal of this debug execrice is to understand the concept of object slicing.
// Check for possible compiler errors, logical errors and rectify them
// Re-factor the code by adding few comments (make it readable) and
// provide list of most important fixes (in comments)

// Expected output -
// Name: tesla model Year: 2019
// Name: Hyundai model Year: 2020 Mileage: 23
// Name: Ford model Year: 2012 Miles driven: 20000
// Name: Ford model Year: 2017 Miles driven: 10000

#include <iostream>

using namespace std;

// capitalize the class name for good practice
class Car
{
// changed from private to protected
protected:
    string name;
    int modelYear;
    void assign(const Car &c)
    {
        name = c.name;
        modelYear = c.modelYear;
    }

public:
    Car(const string &n, const int my) : name(n), modelYear(my) {}

    virtual void print() const
    {
        cout << "Name: " << name << " model Year: " << modelYear << endl;
    }

    virtual const Car &operator=(const Car &c)
    {
        name = c.name;
        modelYear = c.modelYear;
        return *this;
    }
};

class Sedan : public Car
{
private:
    int mileage;

public:
    Sedan(const string &n, const int my, const int m) : Car(n, my), mileage(m) {}

    virtual void print() const
    {
        cout << "Name: " << name << " model Year: " << modelYear << " Mileage: " << mileage << endl;
    }
};

class Suv : public Car
{
    int miles;

public:
    // added Car to the constructor initializer
    Suv(const string &n, const int my, const int m) : Car(n, my), miles(m) {}

    virtual void print() const
    {
        cout << "Name: " << name << " model Year: " << modelYear << " Miles driven: " << miles << endl;
    }

    virtual const Suv &operator=(const Car c)
    {
        if (const Suv *b = dynamic_cast<const Suv *>(&c))
        {
            assign(*b);
        }
        return *this;
    }

protected:
    void assign(const Suv &c)
    {
        Car::assign(c);
        miles = c.miles;
    }
};

// deleted printCarInfo function 

int main()
{
    Car tesla = Car("tesla", 2019);
    Sedan hyundai = Sedan("Hyundai", 2020, 23);
    Suv ford = Suv("Ford", 2012, 20000);
    // instead of using printCarInfo, I am calling the types of cars .print()
    tesla.print();
    hyundai.print();

    // replaced Car with Suv
    Suv &ref = ford;
    ref.print();
    Suv ford2 = Suv("Ford", 2017, 10000);
    ref = ford2;
    ref.print();
    return 0;
}

/*
 * Fixes:
 * - capitalized the class name `car` to `Car`.
 * - changed access specifier from `private` to `protected` in `Car` to allow subclass access.
 * - added `Car` to the constructor initializer in `Suv`.
 * - deleted the `printCarInfo` function to avoid object slicing and used direct calls to `print`.
 * - replaced `Car &ref` with `Suv &ref` to prevent object slicing and correctly handle SUV objects.
 * - corrected typo in expected output comments.
 */
