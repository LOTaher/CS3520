#ifndef ENUMS_H
#define ENUMS_H

#include <string>

using namespace std;

enum OrganizerType
{
    CITY = 0,
    ORGANIZATION = 1,
    RESIDENT = 2,
    NON_RESIDENT = 3
};

enum LayoutType
{
    MEETING_STYLE = 0,
    LECTURE_STYLE = 1,
    WEDDING_STYLE = 2,
    DANCE_ROOM_STYLE = 3
};

inline string layoutTypeToString(LayoutType layout)
{
    switch (layout)
    {
    case MEETING_STYLE:
        return "Meeting Style";
    case LECTURE_STYLE:
        return "Lecture Style";
    case WEDDING_STYLE:
        return "Wedding Style";
    case DANCE_ROOM_STYLE:
        return "Dance Room Style";
    default:
        return "Unknown Layout";
    }
}

inline string organizerTypeToString(OrganizerType organizerType)
{
    switch (organizerType)
    {
    case CITY:
        return "City";
    case ORGANIZATION:
        return "Organization";
    case RESIDENT:
        return "Resident";
    case NON_RESIDENT:
        return "Non-Resident";
    default:
        return "Unknown Organizer Type";
    }
}

#endif // ENUMS_H
