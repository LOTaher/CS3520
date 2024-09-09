#include "include/user.hpp"
#include "include/event.hpp"
#include "include/facility.hpp"
#include "include/global.hpp"
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>

using namespace std;

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

struct UserNameComparer
{
    UserNameComparer(const string &username) : username(username) {}

    bool operator()(const User &u) const { return u.get_username() == username; }

private:
    string username;
};

User::User(const string &username, int balance, const string &city)
    : username(username), balance(balance), city(city) {}

void User::add_reservation(Event &event) { reservations.push_back(event); }

void User::add_event(Event &event) { events.push_back(event); }

ostream &operator<<(ostream &os, const User &other)
{
    os << "Username: " << other.username << endl;
    os << "Balance: " << other.balance << endl;
    os << "City: " << other.city << endl;
    return os;
}

bool User::operator==(const User &other) const
{
    return username == other.username;
}

string User::get_username() const { return username; }

int User::get_balance() const { return balance; }

string User::get_city() const { return city; }

void User::set_balance(int balance) { this->balance = balance; }

void User::view_my_information()
{
    cout << "Username: " << username << endl;
    cout << "Balance: " << balance << endl;
    cout << "City: " << city << endl;
}

void User::cancel_approved_reservation(Event &event, Facility &facility)
{
    auto it = find(facility.get_approved_reservations().begin(), facility.get_approved_reservations().end(), event);
    if (it != facility.get_approved_reservations().end())
    {
        facility.remove_approved_reservation(*it);
        cout << "Reservation cancelled for " << event.get_name() << endl;
        return;
    }
    else
    {
        cout << "Reservation not found for " << event.get_name() << endl;
        return;
    }
}

void User::cancel_pending_reservation(Event &event, Facility &facility)
{
    auto it = find(facility.get_pending_reservations().begin(), facility.get_pending_reservations().end(), event);
    if (it != facility.get_pending_reservations().end())
    {
        facility.remove_pending_reservation(*it);
        cout << "Reservation cancelled for " << event.get_name() << endl;
        return;
    }
    else
    {
        cout << "Reservation not found for " << event.get_name() << endl;
        return;
    }
}

vector<User> read_users_from_file(string filename)
{
    ifstream infile(filename);
    if (!infile)
    {
        cerr << "Error opening file: " << filename << endl;
        return vector<User>();
    }
    vector<User> users;
    string line;
    while (getline(infile, line))
    {
        stringstream ss(line);
        string username, balance_str, city;
        getline(ss, username, ',');
        getline(ss, balance_str, ',');
        getline(ss, city, ',');

        if (username.empty() || balance_str.empty() || city.empty())
        {
            cerr << "Invalid data in line: " << line << endl;
            continue;
        }

        double balance = stod(balance_str);
        User user(username, balance, city);
        users.push_back(user);
    }

    infile.close();
    return users;
}

void User::view_my_events(Facility &facility)
{
    const vector<Event> &approved_reservations =
        facility.get_approved_reservations();

    bool has_event = false;
    for (const auto &event : approved_reservations)
    {
        if (is_user_in_event(*this, event))
        {
            cout << event << endl;
            has_event = true;
        }
    }
    if (!has_event)
    {
        cout << "You have no upcoming events.\n";
    }
}

bool can_user_sign_up(const User &user, const Event &event)
{
    if (!event.is_public_event())
    {
        return false;
    }
    if (event.is_open_to_residents() &&
        user.get_city() == event.get_organizer()->get_city())
    {
        return true;
    }
    if (event.is_open_to_non_residents() &&
        user.get_city() != event.get_organizer()->get_city())
    {
        return true;
    }
    if (is_user_in_event(user, event))
    {
        return false;
    }
    return false;
}

bool is_user_in_event(const User &user, const Event &event)
{
    for (const auto &attendee : event.get_attendees())
    {
        if (attendee.get_username() == user.get_username())
        {
            return true;
        }
    }
    return false;
}

bool is_user_in_waitlist(const User &user, const Event &event)
{
    for (const auto &attendee : event.get_waitlist())
    {
        if (attendee.get_username() == user.get_username())
        {
            return true;
        }
    }
    return false;
}

void User::view_upcoming_events(User &user, Facility &facility) const
{
    const vector<Event> &approved_reservations = facility.get_approved_reservations();
    cout << "+======================================================+\n";
    cout << "|                    Upcoming Events                   |\n";
    cout << "+======================================================+\n";
    for (const auto &event : approved_reservations)
    {
        cout << event << endl;
        cout << "+----------------------+------------------------------+\n";
        if (is_user_in_waitlist(user, event))
        {
            cout << "| Status:              | You are in the waitlist.     |\n";
        }
        else if (event.get_num_guests() <= event.get_attendees().size())
        {
            cout << "| Status:              | This event is full. You will |\n";
            cout << "|                      | be added to the waitlist if  |\n";
            cout << "|                      | you buy a ticket.            |\n";
        }

        else if (event.get_organizer() &&
                 event.get_organizer()->get_username() == user.get_username())
        {
            cout << "| Status:              | You are the organizer of this|\n";
            cout << "|                      | event.                       |\n";
        }
        else if (is_user_in_event(user, event))
        {
            cout << "| Status:              | You are signed up for this   |\n";
            cout << "|                      | event.                       |\n";
        }
        else if (can_user_sign_up(user, event))
        {
            cout << "| Status:              | You can sign up for this     |\n";
            cout << "|                      | event.                       |\n";
        }
        else
        {
            cout << "| Status:              | You cannot sign up for this  |\n";
            cout << "|                      | event.                       |\n";
        }
        cout << "+----------------------+------------------------------+\n";
        cout << endl;
    }
}

void User::view_my_reservations(Facility &facility)
{
    cout << "+======================================================+\n";
    cout << "|                  Pending Reservations                 |\n";
    cout << "+======================================================+\n";
    bool hasPending = false;
    for (const auto &event : facility.get_pending_reservations())
    {
        if (event.get_organizer() &&
            event.get_organizer()->get_username() == username)
        {
            cout << event << endl;
            hasPending = true;
        }
    }
    if (!hasPending)
    {
        cout << "| No pending reservations.                              |\n";
        cout << "+------------------------------------------------------+\n";
    }

    cout << "+======================================================+\n";
    cout << "|                 Approved Reservations                 |\n";
    cout << "+======================================================+\n";
    bool hasApproved = false;
    for (const auto &event : facility.get_approved_reservations())
    {
        if (event.get_organizer() &&
            event.get_organizer()->get_username() == username)
        {
            cout << event << endl;
            hasApproved = true;
        }
    }
    if (!hasApproved)
    {
        cout << "| No approved reservations.                             |\n";
        cout << "+------------------------------------------------------+\n";
    }
}

time_t prompt_for_datetime(const string &prompt)
{
    tm timeinfo = {};
    string datetime_str;
    while (true)
    {
        cout << prompt << " (or type 'b' to go back to the main menu): ";
        getline(cin, datetime_str);
        if (datetime_str == "b")
        {
            throw runtime_error("back to menu");
        }
        stringstream ss(datetime_str);
        ss >> get_time(&timeinfo, "%Y-%m-%d %H:%M");
        if (ss.fail())
        {
            cout << "Invalid date and time. Please enter in YYYY-MM-DD HH:MM "
                    "format.\n";
        }
        else
        {
            break;
        }
    }
    return mktime(&timeinfo);
}

int prompt_for_int(const string &prompt)
{
    int value;
    while (true)
    {
        cout << prompt << " (or type 'b' to go back to the main menu): ";
        string input;
        cin >> input;
        if (input == "b")
        {
            throw runtime_error("back to menu");
        }
        stringstream ss(input);
        if (ss >> value && value >= 0)
        {
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid number.\n";
    }
    return value;
}

string prompt_for_string(const string &prompt)
{
    string value;
    cout << prompt << " (or type 'b' to go back to the main menu): ";
    cin.ignore();
    getline(cin, value);
    if (value == "b")
    {
        throw runtime_error("back to menu");
    }
    return value;
}

bool prompt_for_bool(const string &prompt)
{
    string value;
    while (true)
    {
        cout << prompt << " (1 for Yes, 0 for No) (or type 'b' to go back to the main menu): ";
        cin >> value;
        if (value == "b")
        {
            throw runtime_error("back to menu");
        }
        if (value == "1" || value == "0")
        {
            break;
        }
        else
        {
            cout << "Invalid input. Please enter 1 for Yes or 0 for No.\n";
        }
    }
    return value == "1";
}

LayoutType prompt_for_layout_type()
{
    int layout_int;
    while (true)
    {
        cout << "Enter the layout type (integer value):\n";
        cout << "0: MEETING_STYLE\n";
        cout << "1: LECTURE_STYLE\n";
        cout << "2: WEDDING_STYLE\n";
        cout << "3: DANCE_ROOM_STYLE\n";
        cout << "(or type 'b' to go back to the main menu): ";
        string input;
        cin >> input;
        if (input == "b")
        {
            throw runtime_error("back to menu");
        }
        stringstream ss(input);
        if (ss >> layout_int && layout_int >= 0 && layout_int <= 3)
        {
            break;
        }
        cout << "Invalid layout type. Please enter a number between 0 and 3.\n";
    }
    return static_cast<LayoutType>(layout_int);
}

OrganizerType prompt_for_organizer_type()
{
    int organizer_type_int;
    while (true)
    {
        cout << "Enter the organizer type (integer value):\n";
        cout << "0: CITY\n";
        cout << "1: ORGANIZATION\n";
        cout << "2: RESIDENT\n";
        cout << "3: NON_RESIDENT\n";
        cout << "(or type 'b' to go back to the main menu): ";
        string input;
        cin >> input;
        if (input == "b")
        {
            throw runtime_error("back to menu");
        }
        stringstream ss(input);
        if (ss >> organizer_type_int && organizer_type_int >= 0 &&
            organizer_type_int <= 3)
        {
            break;
        }
        cout << "Invalid organizer type. Please enter a number between 0 and 3.\n";
    }
    return static_cast<OrganizerType>(organizer_type_int);
}

int get_price_of_event(OrganizerType organizer_type, int hours_of_event)
{
    int price = 10;
    switch (organizer_type)
    {
    case OrganizerType::CITY:
        price += 5 * hours_of_event;
        break;
    case OrganizerType::ORGANIZATION:
        price += 20 * hours_of_event;
        break;
    case OrganizerType::RESIDENT:
        price += 10 * hours_of_event;
        break;
    case OrganizerType::NON_RESIDENT:
        price += 15 * hours_of_event;
        break;
    default:
        price = 10;
    }
    return price;
}

Event User::create_event(Facility &facility)
{
    try
    {
        string event_name = prompt_for_string("Enter the event name: ");
        time_t start_time;
        time_t end_time;
        while (true)
        {
            start_time =
                prompt_for_datetime("Enter the start time (YYYY-MM-DD HH:MM): ");
            end_time = prompt_for_datetime("Enter the end time (YYYY-MM-DD HH:MM): ");
            if (start_time >= end_time)
            {
                cout << "Start time cannot be after end time. Please re-enter.\n";
            }
            else
            {
                break;
            }
        }

        bool is_public = prompt_for_bool("Is the event public?");

        int num_guests;
        while (true)
        {
            num_guests = prompt_for_int("Enter the number of guests: ");
            if (num_guests > 40)
            {
                cout << "Cannot create event with more than 40 people. Please "
                        "re-enter.\n";
            }
            else
            {
                break;
            }
        }
        int ticket_price = prompt_for_int("Enter the ticket price: ");
        LayoutType layout = prompt_for_layout_type();
        OrganizerType organizer_type = prompt_for_organizer_type();
        int hours_of_event = (end_time - start_time) / 3600;
        int price_of_event = get_price_of_event(organizer_type, hours_of_event);
        bool open_to_residents = prompt_for_bool("Is the event open to residents?");
        bool open_to_non_residents =
            prompt_for_bool("Is the event open to non-residents?");
        User *organizer = this;

        Event new_event(event_name, start_time, end_time, is_public, num_guests,
                        *organizer, layout, price_of_event, ticket_price,
                        organizer_type, open_to_residents, open_to_non_residents,
                        false);
        if (is_overlapping(new_event, facility.get_pending_reservations()) ||
            is_overlapping(new_event, facility.get_approved_reservations()))
        {
            cout << "Unable to create event. The new event overlaps with an existing "
                    "event.\n";
            throw runtime_error("overlapping event");
        }
        else
        {
            new_event.add_attendee(*this);
            this->add_reservation(new_event);
            cout << "Event has been created. You will have to wait for the facility "
                    "manager to approve the event until it is confirmed"
                 << endl;
            return new_event;
        }
    }
    catch (const runtime_error &e)
    {
        cout << "Returning to main menu.\n";
        throw;
    }
}

void User::buy_ticket(Facility &facility)
{
    try
    {
        view_upcoming_events(*this, facility);

        cout << "Enter the name of the event you would like to buy a ticket for "
                "(or type 'b' to go back to the main menu): ";
        string event_name;
        cin.ignore();
        getline(cin, event_name);

        if (event_name == "b")
        {
            throw runtime_error("back to menu");
        }

        vector<Event> available_events =
            retrieve_events_from_file("approved_reservations.txt", facility);

        if (available_events.empty())
        {
            cout << "No events available for purchase.\n";
            return;
        }

        auto it = find_if(available_events.begin(), available_events.end(),
                          EventNameComparer(event_name));
        if (it != available_events.end())
        {
            Event &event = *it;

            if (balance < event.get_ticket_price())
            {
                cout << "Insufficient balance to buy ticket.\n";
                return;
            }
            if (is_user_in_event(*this, event))
            {
                cout << "You are already signed up for this event.\n";
                return;
            }
            if (event.get_attendees().size() >= event.get_num_guests())
            {
                cout << "This event is full, you will be added to the waitlist for: " << event_name << endl;
                event.add_to_waitlist(*this);
                facility.update_approved_reservation(event);
                add_events_to_file(facility.get_approved_reservations(), "approved_reservations.txt");
            }
            else
            {
                event.add_attendee(*this);
                facility.update_approved_reservation(event);
                add_events_to_file(facility.get_approved_reservations(),
                                   "approved_reservations.txt");
                this->balance -= event.get_ticket_price();
                events.push_back(*it);
            }

            ofstream outfile("users.txt");
            outfile.close();

            facility.update_user(*this);
            for (const auto user : facility.get_all_users())
            {
                save_user_to_file(user);
            }
            cout << "Ticket purchased for " << event_name << endl;
        }
        else
        {
            cout << "Event not found.\n";
        }
    }
    catch (const runtime_error &e)
    {
        cout << "Returning to main menu.\n";
        throw;
    }
}

void User::refund_ticket(Facility &facility)
{
    view_my_events(facility);
    vector<Event> &approved_reservations = facility.get_approved_reservations();
    vector<Event> &pending_reservations = facility.get_pending_reservations();

    bool has_event = false;
    bool is_waitlisted = false;
    for (const auto &event : approved_reservations)
    {
        if (is_user_in_event(*this, event))
        {
            has_event = true;
        }
        if (is_user_in_waitlist(*this, event))
        {
            cout << "You are in the waitlist for: " << endl;
            cout << event << endl;
            is_waitlisted = true;
        }
    }
    if (!has_event && !is_waitlisted)
    {
        return;
    }

    cout << "Enter the name of the event you would like to refund a ticket for "
            "(or type 'b' to go back to the main menu): ";
    string event_name;
    cin.ignore();
    getline(cin, event_name);
    if (event_name == "b")
    {
        throw runtime_error("back to menu");
    }
    bool is_user_in_approved_event = false;
    bool is_user_waitlist = false;
    for (const auto &event : approved_reservations)
    {
        if (event.get_name() == event_name)
        {
            is_user_in_approved_event = is_user_in_event(*this, event);
            is_user_waitlist = is_user_in_waitlist(*this, event);
            break;
        }
    }
    if (!is_user_in_approved_event && !is_user_in_waitlist)
    {
        cout << "You are not signed up for this event.\n";
        return;
    }
    cout << "Are you sure you want to refund the ticket for this event? (1 for "
            "Yes, 0 for No): ";
    int confirm;
    cin >> confirm;
    if (confirm != 1)
    {
        return;
    }
    else
    {

        auto it =
            find_if(approved_reservations.begin(), approved_reservations.end(),
                    EventNameComparer(event_name));
        if (it != approved_reservations.end())
        {
            Event &event = *it;
            if (is_user_waitlist)
            {
                event.remove_from_waitlist(*this);
                facility.update_approved_reservation(event);
                add_events_to_file(facility.get_approved_reservations(), "approved_reservations.txt");
            }
            else
            {
                event.remove_attendee(*this);
                this->balance += event.get_ticket_price();
                events.erase(remove(events.begin(), events.end(), event), events.end());
                facility.update_user(*this);
                cout << "Ticket refunded for " << event_name << endl;

                if (!event.get_waitlist().empty())
                {
                    auto it = event.get_waitlist().begin();
                    User &next_user = *it;
                    event.add_attendee(next_user);
                    next_user.set_balance(next_user.get_balance() - event.get_ticket_price());
                    facility.update_user(next_user);
                    event.remove_from_waitlist(next_user);
                }
                ofstream outfile("users.txt");
                outfile.close();
                for (const auto user : facility.get_all_users())
                {
                    save_user_to_file(user);
                }
                facility.update_approved_reservation(event);
                add_events_to_file(facility.get_approved_reservations(),
                                   "approved_reservations.txt");
            }
        }
    }
}

void cancel_reservation(User &user, Facility &facility)
{
    user.view_my_reservations(facility);
    bool hasPending = false;
    for (const auto &event : facility.get_pending_reservations())
    {
        if (event.get_organizer() &&
            event.get_organizer()->get_username() == user.get_username())
        {
            hasPending = true;
        }
    }
    bool hasApproved = false;
    for (const auto &event : facility.get_approved_reservations())
    {
        if (event.get_organizer() &&
            event.get_organizer()->get_username() == user.get_username())
        {
            hasApproved = true;
        }
    }
    if (!hasPending && !hasApproved)
    {
        cout << "No reservations to cancel.\n";
        return;
    }
    cout << "Enter the name of the event you would like to cancel (or type "
            "'b' to go back to the main menu): ";
    string event_name;
    cin.ignore();
    getline(cin, event_name);

    if (event_name == "b")
    {
        throw runtime_error("back to menu");
    }

    vector<Event> pending_reservations = retrieve_events_from_file("pending_reservations.txt", facility);
    vector<Event> approved_reservations = retrieve_events_from_file("approved_reservations.txt", facility);
    vector<Event>::iterator it_pending = find_if(pending_reservations.begin(), pending_reservations.end(), EventNameComparer(event_name));
    vector<Event>::iterator it_approved = find_if(approved_reservations.begin(), approved_reservations.end(), EventNameComparer(event_name));

    if (it_pending != pending_reservations.end() || it_approved != approved_reservations.end())
    {
        cout << "Are you sure you want to cancel this reservation? (1 for "
                "Yes, 0 for No): ";
        int confirm;
        cin >> confirm;
        if (confirm == 1)
        {
            if (it_pending != pending_reservations.end())
            {
                user.set_balance(user.get_balance() + it_pending->get_price_of_event());
                facility.update_user(user);
                facility.set_budget(facility.get_budget() - it_pending->get_price_of_event());
                cout << "You will be refunded: " << it_pending->get_price_of_event() << endl;
                cout << "Your new balance: " << user.get_balance() << endl;
                user.cancel_pending_reservation(*it_pending, facility);
                it_pending->remove_attendee(user);
                it_pending->refund_users(facility);
                pending_reservations.erase(it_pending);
                add_events_to_file(pending_reservations,
                                   "pending_reservations.txt");
            }
            else if (it_approved != approved_reservations.end())
            {
                if (it_approved->get_start_time() - time(nullptr) < 86400)
                {
                    it_approved->remove_attendee(user);
                    cout << "You will not recieve a refund for cancelling this "
                            "reservation due to it being within 24 hours.\n";
                }
                else
                {
                    user.set_balance(user.get_balance() + it_approved->get_price_of_event());
                    facility.update_user(user);
                    facility.set_budget(facility.get_budget() - it_approved->get_price_of_event());
                    cout << "You will be refunded: " << it_approved->get_price_of_event() << endl;
                    cout << "Your new balance: " << user.get_balance() << endl;
                }
                it_approved->remove_attendee(user);
                it_approved->refund_users(facility);
                user.cancel_approved_reservation(*it_approved, facility);
                approved_reservations.erase(it_approved);
                add_events_to_file(approved_reservations,
                                   "approved_reservations.txt");
            }
        }
        else
        {
            cout << "Cancellation aborted.\n";
        }
    }
    else
    {
        cout << "Event not found.\n";
    }
}

void user_menu(User &user, Facility &facility)
{
    cout << "Welcome " << user.get_username() << "!\n";
    while (true)
    {
        cout << "1. View Upcoming Events\n";
        cout << "2. My Upcoming Events\n";
        cout << "3. My Created Reservations\n";
        cout << "4. Create Reservation\n";
        cout << "5. Cancel Reservation\n";
        cout << "6. Buy Ticket\n";
        cout << "7. Refund Ticket\n";
        cout << "8. View My Information\n";
        cout << "9. Logout\n";

        int choice;
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 9)
        {
            cout << "Invalid input. Please try again. \n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        try
        {
            switch (choice)
            {
            case 1:
                user.view_upcoming_events(user, facility);
                break;
            case 2:
                user.view_my_events(facility);
                break;
            case 3:
                user.view_my_reservations(facility);
                break;
            case 4:
            {
                Event new_event = user.create_event(facility);
                vector<Event> pending_events =
                    retrieve_events_from_file("pending_reservations.txt", facility);
                vector<Event> approved_events =
                    retrieve_events_from_file("approved_reservations.txt", facility);

                if (is_overlapping(new_event, pending_events) ||
                    is_overlapping(new_event, approved_events))
                {
                    cout << "Error: The new event overlaps with an existing event.\n";
                    break;
                }

                pending_events.push_back(new_event);
                add_events_to_file(pending_events, "pending_reservations.txt");
                facility.add_pending_reservation(new_event);
                cout << "Price to create the event is: "
                     << new_event.get_price_of_event() << endl;
                user.set_balance(user.get_balance() - new_event.get_price_of_event());
                facility.update_user(user);
                facility.set_budget(facility.get_budget() + new_event.get_price_of_event());
                ofstream outfile("users.txt");
                outfile.close();
                for (const auto user : facility.get_all_users())
                {
                    save_user_to_file(user);
                }
                break;
            }
            case 5:
            {
                cancel_reservation(user, facility);
                break;
            }
            case 6:
                user.buy_ticket(facility);
                break;
            case 7:
                user.refund_ticket(facility);
                break;
            case 8:
                user.view_my_information();
                break;
            case 9:
                return;
            default:
                cout << "Invalid choice. Try again.\n";
                break;
            }
        }
        catch (const runtime_error &e)
        {
            cout << "Returning to main menu.\n";
            continue;
        }
    }
}

bool load_user_from_file(const string &username, User &user)
{
    ifstream infile("users.txt");
    if (!infile)
    {
        cerr << "Error opening file: users.txt" << endl;
        return false;
    }

    string line;
    while (getline(infile, line))
    {
        stringstream ss(line);
        string file_username, city;
        int balance;

        getline(ss, file_username, ',');
        if (file_username == username)
        {
            ss >> balance;
            ss.ignore();
            getline(ss, city);

            user = User(file_username, balance, city);
            return true;
        }
    }

    return false;
}

void save_user_to_file(const User &user)
{
    ofstream outfile("users.txt", ios::app);
    if (!outfile)
    {
        cerr << "Error opening file: users.txt" << endl;
        return;
    }

    outfile << user.get_username() << "," << user.get_balance() << ","
            << user.get_city() << "\n";
    outfile.close();
}

bool validate_user_credentials(const string &username, User &user, Facility &facility)
{
    if (load_user_from_file(username, user))
    {
        return true;
    }
    else
    {
        string city;
        int balance;

        cout << "User not found. Creating a new user.\n";
        cout << "Enter balance: ";
        cin >> balance;
        cout << "Enter city: ";
        cin.ignore();
        getline(cin, city);

        user = User(username, balance, city);
        save_user_to_file(user);
        facility.add_user(user);
        return true;
    }
}
