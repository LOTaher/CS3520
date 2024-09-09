#include <iostream>
#include "ReservationSystem.hpp"

using namespace std;

struct Book
{
    string title;
    string author;

    bool operator==(const Book &other) const
    {
        return title == other.title && author == other.author;
    }

    friend ostream &operator<<(ostream &os, const Book &book)
    {
        os << "Title: " << book.title << ", Author: " << book.author;
        return os;
    }
};

struct ConcertTicket
{
    string artist;
    string venue;
    string date;

    bool operator==(const ConcertTicket &other) const
    {
        return artist == other.artist && venue == other.venue && date == other.date;
    }

    friend ostream &operator<<(ostream &os, const ConcertTicket &ticket)
    {
        os << "Artist: " << ticket.artist << ", Venue: " << ticket.venue << ", Date: " << ticket.date;
        return os;
    }
};

int main()
{
    time_t now = time(nullptr);
    time_t three_days_ago = now - (3 * 24 * 60 * 60);
    time_t fourty_years_ago = now - (40 * 365 * 24 * 60 * 60);

    // Create instances of Reserver
    ReservationSystem<int>::Reserver reserverAlice("Alice", fourty_years_ago, "ReserverID1");
    ReservationSystem<int>::Reserver reserverBob("Bob", fourty_years_ago, "ReserverID2");
    ReservationSystem<double>::Reserver reserverCharlie("Charlie", fourty_years_ago, "ReserverID3");
    ReservationSystem<double>::Reserver reserverDave("Dave", fourty_years_ago, "ReserverID4");
    ReservationSystem<string>::Reserver reserverEve("Eve", fourty_years_ago, "ReserverID5");
    ReservationSystem<string>::Reserver reserverFrank("Frank", fourty_years_ago, "ReserverID6");
    ReservationSystem<Book>::Reserver reserverGrace("Grace", fourty_years_ago, "ReserverID7");
    ReservationSystem<Book>::Reserver reserverHeidi("Heidi", fourty_years_ago, "ReserverID8");
    ReservationSystem<ConcertTicket>::Reserver reserverIvan("Ivan", fourty_years_ago, "ReserverID9");
    ReservationSystem<ConcertTicket>::Reserver reserverJohn("John", fourty_years_ago, "ReserverID10");

    // Reservations with int and adding multiple reservations at once
    ReservationSystem<int> intReservations;
    vector<ReservationSystem<int>::Reservation> intResList = {
        {"Int Item 1", 42, reserverAlice, "ID1", now},
        {"Int Item 2", 7, reserverBob, "ID2", now}};
    intReservations.add_reservations(intResList);
    cout << "Int Reservations:\n"
         << intReservations << endl;

    // Reservations with double and adding single item at a time
    ReservationSystem<double> doubleReservations;
    doubleReservations.reserve_item("Double Item 1", 3.14, reserverCharlie, "ID3", now);
    doubleReservations.reserve_item("Double Item 2", 2.71, reserverDave, "ID4", now);
    cout << "Double Reservations before update:\n"
         << doubleReservations << endl;

    // Update a reservation
    doubleReservations.reserve_item("Double Item 2", 1.71, reserverDave, "ID4", now);
    cout << "Double Reservations after update:\n"
         << doubleReservations << endl;

    // Reservations with string
    ReservationSystem<string> stringReservations;
    stringReservations.reserve_item("String Item 1", "Hello", reserverEve, "ID5", three_days_ago);
    stringReservations.reserve_item("String Item 2", "World", reserverFrank, "ID6", now);
    cout << "String Reservations:\n"
         << stringReservations << endl;

    // Reservations with type Book
    ReservationSystem<Book> bookReservations;
    bookReservations.reserve_item("Book Item 1", Book{"1984", "George Orwell"}, reserverGrace, "ID7", now);
    bookReservations.reserve_item("Book Item 2", Book{"Brave New World", "Aldous Huxley"}, reserverHeidi, "ID8", now);
    cout << "Book Reservations:\n"
         << bookReservations << endl;

    // Reservations with type ConcertTicket
    ReservationSystem<ConcertTicket> concertReservations;
    concertReservations.reserve_item("Concert Ticket 1", ConcertTicket{"The Beatles", "Wembley", "2024-07-01"}, reserverIvan, "ID9", now);
    concertReservations.reserve_item("Concert Ticket 2", ConcertTicket{"Pink Floyd", "Madison Square Garden", "2024-08-15"}, reserverJohn, "ID10", now);
    cout << "Concert Reservations:\n"
         << concertReservations << endl;

    // Getting reservation duration and number of reservations
    cout << "\nDuration of reservation with ID5 (in days): " << stringReservations.get_reservation_duration("ID5") << endl;
    cout << "Total number of reservations for books: " << bookReservations.get_number_of_reservations() << endl;

    // Remove a single reservation and show remaining reservations
    stringReservations.remove_reservation("ID5");
    cout << "\nString Reservations after removing ID5:\n"
         << stringReservations << endl;

    // Remove multiple reservations from concertReservations
    vector<string> concertReservationIDs = {"ID9", "ID10"};
    concertReservations.remove_reservations(concertReservationIDs);
    cout << "\nConcert Reservations after removing ID9 and ID10:\n"
         << concertReservations << endl;

    return 0;
}
