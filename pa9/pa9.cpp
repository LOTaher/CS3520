#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

// Function object for sorting pairs by their second element (average price)
struct SortAvg {
    bool operator()(pair<string, double> a, pair<string, double> b) {
        return a.second < b.second;
    }
};

// Function object for printing the average prices
struct PrintAverage {
    void operator()(pair<string, double> p) {
        cout << p.first << ", Avg: " << p.second << endl;
    }
};

// Function object for printing the best prices
struct PrintBestPrice {
    void operator()(pair<string, string> p) {
        cout << p.first << ", Best Price Offered by: " << p.second << endl;
    }
};

int main() {
    // Define items and stores
    vector<string> items = {"IPhone14", "IPad Pro", "Noise Cancelling Headphones", "Back Roller", "Bike"};
    vector<string> stores = {"eBay", "Amazon", "BestBuy", "OfficeMax", "Staples"};

    // Define prices of each item from different stores
    map<string, vector<double>> prices;
    prices["IPhone14"] = {999.99, 978.99, 1009.99, 1029.99, 1019.99};
    prices["IPad Pro"] = {1499, 1459.98, 1545.99, 1529.99, 1539.99};
    prices["Noise Cancelling Headphones"] = {299.99, 289.99, 309.99, 319.99, 299.99};
    prices["Back Roller"] = {39.99, 44.99, 49.99, 39.99, 44.99};
    prices["Bike"] = {499.99, 489.99, 509.99, 519.99, 499.99};

    // Display prices of each item from different stores
    cout << "Prices of each item from different stores: " << endl;
    cout << "Name\t\t";
    for (auto store : stores) {
        cout << store << "\t";
    }
    cout << endl;

    for (auto item : items) {
        cout << item << "\t";
        for (auto price : prices[item]) {
            cout << price << "\t";
        }
        cout << endl;
    }

    // Calculate and store the average price for each item
    map<string, double> average_prices;
    for (auto item : items) {
        double sum = accumulate(prices[item].begin(), prices[item].end(), 0.0);
        double avg = sum / stores.size();
        average_prices[item] = avg;
    }

    cout << "\nAverage prices for each item:" << endl;

    // Copy the data from the map into a vector of pairs for sorting
    vector<pair<string, double>> avg_prices_vector;
    for (auto it = average_prices.begin(); it != average_prices.end(); ++it) {
        avg_prices_vector.push_back(*it);
    }

    // Sort the average prices using SortAvg function object
    sort(avg_prices_vector.begin(), avg_prices_vector.end(), SortAvg());

    // Print the sorted average prices using PrintAverage function object
    for_each(avg_prices_vector.begin(), avg_prices_vector.end(), PrintAverage());

    // Find the store that offers the best price for each item
    map<string, string> best_prices;
    for (auto item : items) {
        auto min_price_it = min_element(prices[item].begin(), prices[item].end());
        int index = distance(prices[item].begin(), min_price_it);
        best_prices[item] = stores[index];
    }

    cout << "\nBest price offered by each store:" << endl;

    // Print the best prices using PrintBestPrice function object
    for_each(best_prices.begin(), best_prices.end(), PrintBestPrice());

    return 0;
}
