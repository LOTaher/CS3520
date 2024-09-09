// Fibonacci calculations performed in separate threads
#include <iostream>
#include <iomanip>
#include <future>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

// class to represent the results
class ThreadData {
public:
    time_t startTime;    // time thread starts processing
    time_t endTime;      // time thread finishes processing
    thread::id threadId; // thread ID
};

// function prototypes
unsigned long long int fibonacci(unsigned int n);
ThreadData startFibonacci(unsigned int n);

int main() {
    int num1, num2, num3;
    cout << "This program calculates Fibonacci numbers for three user-provided numbers and measures the computation time." << endl;
    cout << "Please ensure each number is greater than 30." << endl;
    cout << "Enter Number 1: ";
    while (cin >> num1) {
        if (num1 < 30) {
            cout << "The number must be greater than 30. Please try again: ";
        } else {
            break;
        }
    }
    cout << "Enter Number 2: ";
    while (cin >> num2) {
        if (num2 < 30) {
            cout << "The number must be greater than 30. Please try again: ";
        } else {
            break;
        }
    }
    cout << "Enter Number 3: ";
    while (cin >> num3) {
        if (num3 < 30) {
            cout << "The number must be greater than 30. Please try again: ";
        } else {
            break;
        }
    }

    cout << fixed << setprecision(6);
    cout << "Computing fibonacci(" << num1 << "), fibonacci(" << num2 << "), and fibonacci(" << num3 << ") sequentially." << endl;

    // Sequential execution
    auto startSequential = chrono::high_resolution_clock::now();
    startFibonacci(num1);
    startFibonacci(num2);
    startFibonacci(num3);
    auto endSequential = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedSequential = endSequential - startSequential;
    cout << "Time taken for sequential execution: " << elapsedSequential.count() << " seconds" << endl;

    // Parallel execution
    cout << "Launching threads to compute Fibonacci numbers in parallel..." << endl;
    auto startParallel = chrono::high_resolution_clock::now();
    auto futureResult1 = async(launch::async, startFibonacci, num1);
    auto futureResult2 = async(launch::async, startFibonacci, num2);
    auto futureResult3 = async(launch::async, startFibonacci, num3);

    // wait for results from each thread
    ThreadData result1 = futureResult1.get();
    ThreadData result2 = futureResult2.get();
    ThreadData result3 = futureResult3.get();
    auto endParallel = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsedParallel = endParallel - startParallel;

    cout << "Time taken for parallel execution: " << elapsedParallel.count() << " seconds" << endl;

    cout << "Thread ID for fibonacci(" << num1 << "): " << result1.threadId << endl;
    cout << "Thread ID for fibonacci(" << num2 << "): " << result2.threadId << endl;
    cout << "Thread ID for fibonacci(" << num3 << "): " << result3.threadId << endl;

    return 0;
} // end main

// executes function fibonacci asynchronously
ThreadData startFibonacci(unsigned int n) {
    // create a ThreadData object to store times
    ThreadData result = {0, 0};
    result.threadId = this_thread::get_id();

    cout << "Computing fibonacci(" << n << ") in thread " << result.threadId << endl;
    result.startTime = time(nullptr); // time before calculation
    auto fibonacciValue = fibonacci(n);
    result.endTime = time(nullptr); // time after calculation

    // display fibonacci calculation result and total calculation time
    cout << "Result for fibonacci(" << n << ") = " << fibonacciValue << endl;
    cout << "Time taken for this calculation: " << difftime(result.endTime, result.startTime) / 60.0 << " minutes\n" << endl;

    return result;
} // end function startFibonacci

// Recursively calculates fibonacci numbers
unsigned long long int fibonacci(unsigned int n) {
    // base case
    if (0 == n || 1 == n) {
        return n;
    } else { // recursive step
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
} // end function fibonacci
