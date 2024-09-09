#include "include/event.hpp"
#include "include/global.hpp"
#include "include/facility.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

Event::Event(const string name, time_t start_time, time_t end_time,
             bool is_public, int num_guests, User &organizer, LayoutType layout,
             int price_of_event, int ticket_price, OrganizerType type,
             bool open_to_residents, bool open_to_non_residents, bool approved, vector<User> attendees, vector<User> waitlist)
    : name(name), start_time(start_time), end_time(end_time),
      is_public(is_public), num_guests(num_guests), organizer(&organizer), layout(layout),
      price_of_event(price_of_event), ticket_price(ticket_price), type(type),
      open_to_residents(open_to_residents), open_to_non_residents(open_to_non_residents), approved(approved), attendees(attendees), waitlist(waitlist) {}

string Event::get_name() const { return name; }
time_t Event::get_start_time() const { return start_time; }
time_t Event::get_end_time() const { return end_time; }
bool Event::is_public_event() const { return is_public; }
int Event::get_num_guests() const { return num_guests; }
int Event::get_price_of_event() const { return price_of_event; }
User *Event::get_organizer() const { return organizer; }
LayoutType Event::get_layout() const { return layout; }
int Event::get_ticket_price() const { return ticket_price; }
OrganizerType Event::get_type() const { return type; }
bool Event::is_open_to_residents() const { return open_to_residents; }
bool Event::is_open_to_non_residents() const { return open_to_non_residents; }
vector<User> Event::get_attendees() const { return attendees; }
vector<User> Event::get_waitlist() const { return waitlist; }
void Event::set_ticket_price(int price) { ticket_price = price; }
bool Event::is_approved() const { return approved; }
void Event::set_approved(bool approved) { this->approved = approved; }

ostream &operator<<(ostream &os, const Event &event)
{
    time_t start_time = event.get_start_time();
    time_t end_time = event.get_end_time();
    tm start_tm_struct;
    localtime_r(&start_time, &start_tm_struct);
    tm end_tm_struct;
    localtime_r(&end_time, &end_tm_struct);

    start_tm_struct.tm_hour -= 1;
    end_tm_struct.tm_hour -= 1;

    os << "+-----------------------------------------+\n";
    os << "| Event Details                          |\n";
    os << "+----------------------+------------------+\n";
    os << "| Event Name:          | " << event.name << "\n";
    os << "+----------------------+------------------+\n";
    if (event.organizer)
    {
        os << "| Organizer:           | " << event.organizer->get_username() << "\n";
    }
    else
    {
        os << "| Organizer:           | None\n";
    }
    os << "+----------------------+------------------+\n";
    os << "| Start Time:          | " << put_time(&start_tm_struct, "%Y-%m-%d %H:%M") << "\n";
    os << "+----------------------+------------------+\n";
    os << "| End Time:            | " << put_time(&end_tm_struct, "%Y-%m-%d %H:%M") << "\n";
    os << "+----------------------+------------------+\n";
    os << "| Ticket Price:        | $" << event.ticket_price << "\n";
    os << "+----------------------+------------------+\n";
    os << "| Room Setup:          | " << layoutTypeToString(event.layout) << "\n";
    os << "+----------------------+------------------+\n";
    os << "| Organizer Type:      | " << organizerTypeToString(event.type) << "\n";
    os << "+----------------------+------------------+\n";
    os << "| Availability:        | " << event.get_attendees().size() << "/" << event.get_num_guests() << " people coming" << "\n";
    os << "+----------------------+------------------+\n";
    os << "| Attendees:          | ";
    for (const auto &attendee : event.attendees)
    {
        os << attendee.get_username() << ", ";
    }
    os << "\n";
    os << "+----------------------+------------------+\n";
    os << "| Is Public:          | " << (event.is_public ? "Yes" : "No") << "\n";
    os << "+----------------------+------------------+\n";

    return os;
}

bool Event::operator==(const Event &other) const
{
    return name == other.name && start_time == other.start_time &&
           end_time == other.end_time && num_guests == other.num_guests && organizer == other.organizer &&
           layout == other.layout && price_of_event == other.price_of_event && ticket_price == other.ticket_price &&
           type == other.type && open_to_residents == other.open_to_residents && open_to_non_residents == other.open_to_non_residents;
}

void Event::add_attendee(User &user)
{
    attendees.push_back(user);
}

void Event::add_to_waitlist(User &user)
{
    waitlist.push_back(user);
}

void Event::remove_attendee(User &user)
{
    auto it = find(attendees.begin(), attendees.end(), user);
    if (it != attendees.end())
    {
        attendees.erase(it);
    }
}

void Event::remove_from_waitlist(User &user)
{
    auto it = find(waitlist.begin(), waitlist.end(), user);
    if (it != waitlist.end())
    {
        waitlist.erase(it);
    }
}

void Event::refund_users(Facility &facility)
{
    for (auto &attendee : attendees)
    {
        int cost = ticket_price;
        attendee.set_balance(attendee.get_balance() + cost);
        facility.update_user(attendee);
        cout << "Refunded " << attendee.get_username() << " " << cost << " credits." << endl;
    }

    ofstream outfile("users.txt");
    outfile.close();

    for (auto &attendee : facility.get_all_users())
    {
        save_user_to_file(attendee);
    }

    cout << "All attendees have been refunded." << endl;
}

void add_events_to_file(vector<Event> events, string filename)
{
    ofstream outfile(filename);
    if (!outfile)
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    for (const auto &event : events)
    {
        time_t start_time = event.get_start_time();
        time_t end_time = event.get_end_time();
        tm start_tm_struct;
        localtime_r(&start_time, &start_tm_struct);
        tm end_tm_struct;
        localtime_r(&end_time, &end_tm_struct);

        start_tm_struct.tm_hour += 1;
        end_tm_struct.tm_hour += 1;

        outfile << "Event Name: " << event.get_name() << endl;
        outfile << "Start Time: " << put_time(&start_tm_struct, "%Y-%m-%d %H:%M") << endl;
        outfile << "End Time: " << put_time(&end_tm_struct, "%Y-%m-%d %H:%M") << endl;
        outfile << "Is public: " << (event.is_public_event() ? "yes" : "no") << endl;
        outfile << "Number of Guests: " << event.get_num_guests() << endl;
        if (event.get_organizer())
        {
            outfile << "Organizer: " << event.get_organizer()->get_username() << endl;
        }
        else
        {
            outfile << "Organizer: " << "None" << endl;
        }
        outfile << "Layout: " << layoutTypeToString(event.get_layout()) << endl;
        outfile << "Price of Event: " << event.get_price_of_event() << endl;
        outfile << "Ticket Price: " << event.get_ticket_price() << endl;
        outfile << "Organizer Type: " << organizerTypeToString(event.get_type()) << endl;
        outfile << "Open to Residents: " << (event.is_open_to_residents() ? "yes" : "no") << endl;
        outfile << "Open to Non-Residents: " << (event.is_open_to_non_residents() ? "yes" : "no") << endl;
        outfile << "Approved: " << (event.is_approved() ? "yes" : "no") << endl;
        outfile << "Attendees: ";
        const vector<User> &attendees = event.get_attendees();
        for (size_t i = 0; i < attendees.size(); ++i)
        {
            const User &user = attendees[i];
            outfile << user.get_username() << "," << user.get_balance() << "," << user.get_city();
            if (i < attendees.size() - 1)
            {
                outfile << ";";
            }
        }
        outfile << endl;
        outfile << "Waitlist: ";
        const vector<User> &waitlist = event.get_waitlist();
        for (size_t i = 0; i < waitlist.size(); ++i)
        {
            const User &user = waitlist[i];
            outfile << user.get_username() << "," << user.get_balance() << "," << user.get_city();
            if (i < waitlist.size() - 1)
            {
                outfile << ";";
            }
        }
        outfile << endl;

        outfile << "----------------------------------------" << endl;
    }
    outfile.close();
}

vector<Event> retrieve_events_from_file(string filename, Facility &facility)
{
    ifstream infile(filename);
    vector<Event> events;
    if (!infile)
    {
        cerr << "Error opening file: " << filename << endl;
        return events;
    }

    string line;
    while (getline(infile, line))
    {
        if (line.find("Event Name: ") == 0)
        {
            try
            {
                string event_name = line.substr(12);

                getline(infile, line);
                time_t start_time = parse_datetime(line.substr(12));

                getline(infile, line);
                time_t end_time = parse_datetime(line.substr(10));

                getline(infile, line);
                bool is_public = parse_bool(line.substr(11));

                getline(infile, line);
                int num_guests = stoi(line.substr(18));

                getline(infile, line);
                string organizer_username = line.substr(11);
                User *organizer = get_user_by_username(organizer_username, facility);
                if (!organizer)
                {
                    cerr << "Error: User not found for organizer: " << organizer_username << endl;
                    continue;
                }

                getline(infile, line);
                LayoutType layout = parse_layout(line.substr(8));

                getline(infile, line);
                int price_of_event = stoi(line.substr(16));

                getline(infile, line);
                int ticket_price = stoi(line.substr(14));

                getline(infile, line);
                OrganizerType organizer_type = parse_organizer_type(line.substr(16));

                getline(infile, line);
                bool open_to_residents = parse_bool(line.substr(19));

                getline(infile, line);
                bool open_to_non_residents = parse_bool(line.substr(24));

                getline(infile, line);
                bool approved = parse_bool(line.substr(10));

                vector<User> attendees;
                getline(infile, line);
                if (line.find("Attendees: ") == 0)
                {
                    string attendees_str = line.substr(11);
                    stringstream ss(attendees_str);
                    string attendee_info;
                    while (getline(ss, attendee_info, ';'))
                    {
                        if (!attendee_info.empty())
                        {
                            stringstream attendee_stream(attendee_info);
                            string username;
                            getline(attendee_stream, username, ',');
                            try
                            {
                                User *attendee = get_user_by_username(username, facility);
                                if (attendee)
                                {
                                    attendees.push_back(*attendee);
                                }
                            }
                            catch (const runtime_error &e)
                            {
                                cerr << "Error: " << e.what() << endl;
                            }
                        }
                    }
                }

                vector<User> waitlist;
                getline(infile, line);
                if (line.find("Waitlist: ") == 0)
                {
                    string waitlist_str = line.substr(10);
                    stringstream ss(waitlist_str);
                    string waitlist_info;
                    while (getline(ss, waitlist_info, ';'))
                    {
                        if (!waitlist_info.empty())
                        {
                            stringstream attendee_stream(waitlist_info);
                            string username;
                            getline(attendee_stream, username, ',');
                            try
                            {
                                User *attendee = get_user_by_username(username, facility);
                                if (attendee)
                                {
                                    waitlist.push_back(*attendee);
                                }
                            }
                            catch (const runtime_error &e)
                            {
                                cerr << "Error: " << e.what() << endl;
                            }
                        }
                    }
                }

                getline(infile, line);

                Event event(event_name, start_time, end_time, is_public, num_guests, *organizer, layout, price_of_event, ticket_price, organizer_type, open_to_residents, open_to_non_residents, approved, attendees);
                events.push_back(event);
            }
            catch (const out_of_range &e)
            {
                cerr << "Error parsing file: " << e.what() << endl;
            }
            catch (const invalid_argument &e)
            {
                cerr << "Invalid data found: " << e.what() << endl;
            }
        }
    }

    infile.close();
    return events;
}
