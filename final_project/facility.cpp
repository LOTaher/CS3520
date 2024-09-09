#include "include/facility.hpp"
#include "include/event.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

struct UserNameComparer
{
    UserNameComparer(const string &username) : username(username) {}

    bool operator()(const User &u) const
    {
        return u.get_username() == username;
    }

private:
    string username;
};

struct EventNameComparer
{
    EventNameComparer(const string &name) : name(name) {}
    bool operator()(const Event &e) const
    {
        return e.get_name() == name;
    }

private:
    string name;
};

Facility::Facility(string name, int budget)
    : name(name), budget(budget) {}

void Facility::add_user(User &user)
{
    all_users.push_back(user);
}

void Facility::set_budget(int budget)
{
    this->budget = budget;
}

int Facility::get_budget() const
{
    return budget;
}

void Facility::add_approved_reservation(Event &event)
{
    approved_reservations.push_back(event);
}

void Facility::remove_approved_reservation(const Event &event)
{
    auto it = find_if(approved_reservations.begin(), approved_reservations.end(), EventNameComparer(event.get_name()));
    if (it != approved_reservations.end())
    {
        approved_reservations.erase(it);
        add_events_to_file(approved_reservations, "approved_reservations.txt");
    }
    else
    {
        cout << "Approved reservation not found: " << event.get_name() << endl;
    }
}

void Facility::remove_reservation(Event &event)
{
    auto it = find_if(approved_reservations.begin(), approved_reservations.end(), EventNameComparer(event.get_name()));
    if (it != approved_reservations.end())
    {
        approved_reservations.erase(it);
        cout << "Removed reservation for event: " << event.get_name() << endl;
    }
}

User *get_user_by_username(string username, Facility &facility)
{
    for (auto &user : facility.get_all_users())
    {
        if (user.get_username() == username)
        {
            return &user;
        }
    }
    throw runtime_error("User not found: " + username);
}

vector<User> &Facility::get_all_users()
{
    return all_users;
}

vector<Event> &Facility::get_approved_reservations()
{
    return approved_reservations;
}

void Facility::add_pending_reservation(Event &event)
{
    pending_reservations.push_back(event);
}

vector<Event> &Facility::get_pending_reservations()
{
    return pending_reservations;
}

void Facility::remove_pending_reservation(const Event &event)
{
    auto it = find_if(pending_reservations.begin(), pending_reservations.end(), EventNameComparer(event.get_name()));
    if (it != pending_reservations.end())
    {
        pending_reservations.erase(it);
        add_events_to_file(pending_reservations, "pending_reservations.txt");
    }
    else
    {
        cout << "Pending reservation not found: " << event.get_name() << endl;
    }
}

bool Facility::exceeds_max_reservation_time() const
{
    int organization_time = 0;
    int city_time = 0;
    int resident_time = 0;
    int non_resident_time = 0;

    for (const auto &event : approved_reservations)
    {
        time_t start_time = event.get_start_time();
        time_t end_time = event.get_end_time();
        tm start_tm_struct;
        localtime_r(&start_time, &start_tm_struct);
        tm end_tm_struct;
        localtime_r(&end_time, &end_tm_struct);

        if (event.get_type() == OrganizerType::ORGANIZATION)
        {
            organization_time += end_tm_struct.tm_hour - start_tm_struct.tm_hour - 1;
        }
        else if (event.get_type() == OrganizerType::CITY)
        {
            city_time += end_tm_struct.tm_hour - start_tm_struct.tm_hour - 1;
        }
        else if (event.get_type() == OrganizerType::RESIDENT)
        {
            resident_time += end_tm_struct.tm_hour - start_tm_struct.tm_hour - 1;
        }
        else
        {
            non_resident_time += end_tm_struct.tm_hour - start_tm_struct.tm_hour - 1;
        }
    }
    return organization_time > 36 || city_time > 48 || resident_time > 24 || non_resident_time > 24;
}

void Facility::update_user(const User &user)
{
    auto it = find_if(all_users.begin(), all_users.end(), UserNameComparer(user.get_username()));
    if (it != all_users.end())
    {
        *it = user;
    }
}

void Facility::update_approved_reservation(const Event &event)
{
    auto it = find_if(approved_reservations.begin(), approved_reservations.end(), EventNameComparer(event.get_name()));
    if (it != approved_reservations.end())
    {
        *it = event;
    }
}

void Facility::update_pending_reservation(const Event &event)
{
    auto it = find_if(pending_reservations.begin(), pending_reservations.end(), EventNameComparer(event.get_name()));
    if (it != pending_reservations.end())
    {
        *it = event;
    }
}
