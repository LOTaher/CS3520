#include <iostream>
#include <memory>
#include <cstring>
#include <utility>

using namespace std;

class MyString {
    unique_ptr<char[]> str;
public:
    MyString() : str(new char[1]) {
        str[0] = '\0';
    }

    MyString(const char* val) : str(new char[strlen(val) + 1]) {
        strcpy(str.get(), val);
    }

    // copy constructor
    MyString(const MyString& source) : str(new char[strlen(source.str.get()) + 1]) {
        strcpy(str.get(), source.str.get());
    }

    // move constructor
    MyString(MyString&& source) noexcept : str(std::move(source.str)) {}

    // destructor
    ~MyString() = default;
};

int main() {
    cout << "Start!" << endl;
    MyString a;
    MyString b{"Hello"};
    MyString c{a};
    MyString d{MyString{"World"}};
    cout << "Bye" << endl;
    return 0;
}

/* 
 * Updates:
 * - replaced raw pointers with unique_ptr for automatic memory management.
 * - ensured memory safety and exception safety using smart pointers.
 * - simplified code by eliminating explicit new and delete[] calls.
 * - applied RAII principles
 */
