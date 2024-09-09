#include "include/facility_manager.hpp"
#include "include/facility.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

FacilityManager::FacilityManager(const string &username, const string &password)
    : username(username), password(password)
{
}

string FacilityManager::get_username() const
{
    return username;
}

struct EventComparator
{
    bool operator()(const Event &a, const Event &b) const
    {
        return a.get_type() < b.get_type();
    }
};

void FacilityManager::view_reservations(const string &file_name) const
{
    ifstream file(file_name);
    if (!file.is_open())
    {
        cout << "Error: could not open file " << file_name << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}

bool FacilityManager::is_valid_event(const Event &event) const
{
    const time_t opening_time = 8 * 3600;
    const time_t closing_time = 23 * 3600;

    if (event.get_start_time() < opening_time || event.get_end_time() > closing_time)
    {
        return false;
    }

    if (event.get_num_guests() > 40)
    {
        return false;
    }

    return true;
}

bool FacilityManager::is_valid_layout(const Event &event) const
{
    if (event.get_type() == OrganizerType::CITY || event.get_type() == OrganizerType::ORGANIZATION)
    {
        return event.get_layout() != LayoutType::WEDDING_STYLE;
    }
    return true;
}

bool validate_facility_manager_credentials(const string &username, const string &password, FacilityManager &manager)
{
    ifstream file("manager_credentials.txt");
    if (!file.is_open())
    {
        cout << "Error: could not open manager credentials file" << endl;
        return false;
    }

    string file_username, file_password, line;
    while (getline(file, line))
    {
        if (line.find("username: ") == 0)
        {
            file_username = line.substr(10);
        }
        else if (line.find("password: ") == 0)
        {
            file_password = line.substr(10);
        }

        if (file_username == username && file_password == password)
        {
            manager = FacilityManager(username, password);
            return true;
        }
    }

    return false;
}

void view_events_for_next_week(Facility &facility)
{
    time_t current_time = time(nullptr);
    time_t next_week = current_time + 7 * 24 * 3600;

    cout << "Events for the next week: " << endl;
    int event_count = 0;
    for (const Event &event : facility.get_approved_reservations())
    {
        if (event.get_start_time() >= current_time && event.get_start_time() <= next_week)
        {
            event_count++;
            cout << event << endl;
        }
    }
    if (event_count == 0)
    {
        cout << "No events found for the next week." << endl;
    }
}

void approve_reservation(Event &event, Facility &facility)
{
    if (facility.exceeds_max_reservation_time())
    {
        cout << "Cannot approve reservation due to exceeded weekly hours." << endl;
        return;
    }
    facility.remove_pending_reservation(event);
    facility.add_approved_reservation(event);
    add_events_to_file(facility.get_approved_reservations(), "approved_reservations.txt");
    add_events_to_file(facility.get_pending_reservations(), "pending_reservations.txt");

    cout << "Approved reservation for event: " << event.get_name() << endl;
}

void facility_manager_menu(FacilityManager &manager, Facility &facility)
{
    while (true)
    {
        cout << "Welcome Manager " << manager.get_username() << "!\n";
        cout << "1. View Reservation Requests\n";
        cout << "2. View Approved Reservations\n";
        cout << "3. Refund Event\n";
        cout << "4. View Budget\n";
        cout << "5. Approve Reservation\n";
        cout << "6. View events for the next week\n";
        cout << "7. Logout\n";

        int choice;
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 7)
        {
            cout << "Invalid input. Please try again. \n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            if (facility.get_pending_reservations().empty())
            {
                cout << "No pending reservations." << endl;
                break;
            }
            for (const Event &event : facility.get_pending_reservations())
            {
                cout << event << endl;
            }
            break;
        }
        case 2:
        {
            if (facility.get_approved_reservations().empty())
            {
                cout << "No approved reservations." << endl;
                break;
            }
            for (const Event &event : facility.get_approved_reservations())
            {
                cout << event << endl;
            }
            break;
        }
        case 3:
        {
            for (const Event &event : facility.get_approved_reservations())
            {
                cout << event << endl;
            }
            for (const Event &event : facility.get_pending_reservations())
            {
                cout << event << endl;
            }
            string user_name;
            cout << "Enter the name of the user whos event you want to cancel: ";
            cin.ignore();
            getline(cin, user_name);
            User *organizer = get_user_by_username(user_name, facility);
            cancel_reservation(*organizer, facility);
            break;
        }
        case 4:
            cout << facility.get_budget() << endl;
            break;
        case 5:
        {
            if (facility.get_pending_reservations().empty())
            {
                cout << "No pending reservations." << endl;
                break;
            }

            vector<Event> &reservations = facility.get_pending_reservations();
            sort(reservations.begin(), reservations.end(), EventComparator());

            auto it = facility.get_pending_reservations().begin();
            if (it != facility.get_pending_reservations().end())
            {
                cout << *it << endl;
                cout << "Do you want to approve the event: " << it->get_name() << "? 1 for yes and 0 for no: ";
                int choice;
                cin >> choice;
                if (cin.fail() || choice < 0 || choice > 1)
                {
                    cout << "Invalid input. Please try again. \n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                if (choice == 1)
                {
                    approve_reservation(*it, facility);
                }
                else
                {
                    break;
                }
            }
            else
            {
                cout << "Event not found." << endl;
            }
            break;
        }
        case 6:
            view_events_for_next_week(facility);
            break;
        case 7:
            return;
        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }
    }
}
