#ifndef ONLINEDEALERSHIP_HPP
#define ONLINEDEALERSHIP_HPP

#include "dealership.hpp"

class OnlineDealership : public Dealership {
public:
    OnlineDealership(const string& name, const string& location, const string& website);

    string get_website() const;

private:
    string website;
};

#endif
