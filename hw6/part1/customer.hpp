#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <string>
#include "favoritelist.hpp"

using namespace std;

class Customer {
public:
    Customer(const string& name, const string& id);

    string get_name() const;
    string get_id() const;
    FavoriteList& get_favorite_list();

private:
    string name;
    string id;
    FavoriteList favorite_list;
};

#endif
