#include <iostream>
#include <limits>
#include <string>
#include "include/user.hpp"
#include "include/facility_manager.hpp"
#include "include/facility.hpp"

using namespace std;

int main()
{
    Facility facility("facility");

    vector<User> users = read_users_from_file("users.txt");
    for (auto &user : users)
    {
        facility.add_user(user);
    }

    vector<Event> pending_reservations = retrieve_events_from_file("pending_reservations.txt", facility);
    for (auto &event : pending_reservations)
    {
        facility.add_pending_reservation(event);
    }

    vector<Event> approved_reservations = retrieve_events_from_file("approved_reservations.txt", facility);
    for (auto &event : approved_reservations)
    {
        facility.add_approved_reservation(event);
    }

    for (auto &user : facility.get_all_users())
    {
        for (auto &event : facility.get_approved_reservations())
        {
            for (const auto &attendee : event.get_attendees())
            {
                if (attendee.get_username() == user.get_username())
                {
                    user.add_event(event);
                }
            }
            if (event.get_organizer()->get_username() == user.get_username())
            {
                user.add_reservation(event);
            }
        }
        for (auto &event : facility.get_pending_reservations())
        {
            if (event.get_organizer()->get_username() == user.get_username())
            {
                user.add_event(event);
            }
        }
    }

    while (true)
    {
        cout << "Welcome to the Community Center Management System! Please login to continue.\n";
        cout << "Are you a user or a facility manager? \n";
        cout << "1. User \n";
        cout << "2. Facility Manager \n";
        cout << "3. Quit \n";

        int choice;
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 3)
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
            string username;
            cout << "Please enter your username: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, username);
            if (cin.fail() || username.empty())
            {
                cout << "Invalid input. Please try again. \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            User user("", 0, "");
            if (validate_user_credentials(username, user, facility))
            {
                user_menu(user, facility);
            }
            else
            {
                cout << "Login failed. Please try again. \n";
            }
            break;
        }
        case 2:
        {
            string username, password;
            cout << "Please enter your username: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, username);
            if (cin.fail() || username.empty())
            {
                cout << "Invalid input. Please try again. \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            cout << "Please enter your password: ";
            getline(cin, password);
            if (cin.fail() || password.empty())
            {
                cout << "Invalid input. Please try again. \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            FacilityManager manager(username, password);
            if (validate_facility_manager_credentials(username, password, manager))
            {
                facility_manager_menu(manager, facility);
            }
            else
            {
                cout << "Login credentials are incorrect. Please try again. \n";
            }
            break;
        }
        case 3:
        {
            cout << "Goodbye! \n";
            return 0;
        }
        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }
    }

    return 0;
}
