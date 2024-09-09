#ifndef FACILITYMANAGER_H
#define FACILITYMANAGER_H

#include <string>
#include "event.hpp"

class Facility;

class FacilityManager
{
public:
    FacilityManager(const string &username, const string &password);

    string get_username() const;
    void view_reservations(const string &file_name) const;

private:
    string username;
    string password;

    bool is_valid_event(const Event &event) const;
    bool is_valid_layout(const Event &event) const;
};

bool validate_facility_manager_credentials(const string &username, const string &password, FacilityManager &manager);
void facility_manager_menu(FacilityManager &manager, Facility &facility);
void view_events_for_next_week(Facility &facility);
void approve_reservation(Event &event, Facility &facility);

#endif // FACILITYMANAGER_H
