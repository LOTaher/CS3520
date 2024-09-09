#ifndef ORDER_HPP
#define ORDER_HPP

#include <string>
#include "vehicle.hpp"
#include "customer.hpp"
#include "delivery.hpp"

using namespace std;

class Order
{
public:
    Order(const string &orderId, const Vehicle &vehicle, const Customer &customer, const Delivery &delivery);

    string get_order_id() const;
    Vehicle get_vehicle() const;
    Customer get_customer() const;
    Delivery get_delivery() const;

private:
    string order_id;
    Vehicle vehicle;
    Customer customer;
    Delivery delivery;
};

#endif
