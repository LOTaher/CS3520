#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "enums.hpp"
#include "event.hpp"
#include <string>
#include <vector>
#include <ctime>

time_t parse_datetime(const string &datetime_str);
bool parse_bool(const string &bool_str);
LayoutType parse_layout(const string &layout_str);
OrganizerType parse_organizer_type(const string &organizer_type_str);
bool is_overlapping(const Event &new_event, const vector<Event> &events);

#endif // GLOBAL_HPP
