#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include "student.hpp"
#include "teams.hpp"

using namespace std;

int main()
{
    vector<Student> students;
    map<int, vector<Student>> teams;

    string file_name;
    ifstream file;

    // prompts the user for a filename until they provide a valid one
    while (true)
    {
        cout << "Enter the file name: ";
        cin >> file_name;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Invalid input. Please enter a valid file name." << endl;
            continue;
        }

        file.open(file_name);
        if (file.is_open())
        {
            break;
        }
        else
        {
            cerr << "File not found. Please enter a valid file name." << endl;
        }
    }

    // prompt the user for a valid team size until they provide one
    int team_size;
    while (true)
    {
        cout << "Enter the team size (3 or 4): ";
        cin >> team_size;
        if (cin.fail() || (team_size != 3 && team_size != 4))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Invalid input. Please enter a valid team size name." << endl;
            continue;
        }
        else
        {
            break;
        }
    }

    // prompt the user for a valid preference until they provide one
    string preference;
    while (true)
    {
        cout << "Student Preference or Skill Level? (P or L): ";
        cin >> preference;
        if (cin.fail() || (preference != "P" && preference != "L"))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Invalid input. Please enter a valid preference." << endl;
            continue;
        }
        else
        {
            break;
        }
    }

    read_students_results(file_name, students);
    create_teams(students, team_size, teams, preference);
    print_teams(teams);
    create_teams_csv(teams);
}
