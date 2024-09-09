#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>
#include "enums.hpp"
#include "user.hpp"

class Facility;

class Event
{
public:
    Event(const string name, time_t start_time, time_t end_time,
          bool is_public, int num_guests, User &organizer, LayoutType layout,
          int price_of_event, int ticket_price, OrganizerType type,
          bool open_to_residents, bool open_to_non_residents, bool approved, vector<User> attendees = vector<User>(),
          vector<User> waitlist = vector<User>());

    string get_name() const;
    time_t get_start_time() const;
    time_t get_end_time() const;
    bool is_public_event() const;
    int get_num_guests() const;
    int get_price_of_event() const;
    User *get_organizer() const;
    LayoutType get_layout() const;
    int get_ticket_price() const;
    OrganizerType get_type() const;
    bool is_open_to_residents() const;
    bool is_open_to_non_residents() const;
    bool is_approved() const;
    void set_approved(bool approved);
    void add_attendee(User &user);
    void remove_attendee(User &user);
    void remove_from_waitlist(User &user);
    void refund_users(Facility &facility);
    vector<User> get_attendees() const;
    vector<User> get_waitlist() const;
    void add_to_waitlist(User &user);
    void set_ticket_price(int price);
    bool operator==(const Event &other) const;
    friend ostream &operator<<(ostream &os, const Event &other);

private:
    string name;
    time_t start_time;
    time_t end_time;
    bool is_public;
    int num_guests;
    User *organizer;
    LayoutType layout;
    int price_of_event;
    int ticket_price;
    vector<User> attendees;
    vector<User> waitlist;
    OrganizerType type;
    bool open_to_residents;
    bool open_to_non_residents;
    bool approved;
};

void add_events_to_file(vector<Event> events, string filename);
vector<Event> retrieve_events_from_file(string filename, Facility &facility);

#endif // EVENT_H
