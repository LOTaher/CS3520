#include "teams.hpp"
#include "student.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

string to_lower(const string &str)
{
    string lower_str;
    for (char ch : str)
    {
        lower_str += tolower(ch);
    }
    return lower_str;
}

bool allowed_to_work_with(const vector<string> &team_not_work_with, const Student &student, const vector<Student> &team)
{
    // Check if the student is in the team_not_work_with list
    string student_username_lower = to_lower(student.username);
    bool student_in_team_not_work_with =
        find_if(team_not_work_with.begin(), team_not_work_with.end(),
                [&student_username_lower](const string &name)
                {
                    return to_lower(name) == student_username_lower;
                }) != team_not_work_with.end();

    // Check if any student in the team is in the student's do_not_work_with list
    for (const auto &team_member : team)
    {
        string team_member_username_lower = to_lower(team_member.username);
        if (find_if(student.do_not_work_with.begin(), student.do_not_work_with.end(),
                    [&team_member_username_lower](const string &name)
                    {
                        return to_lower(name) == team_member_username_lower;
                    }) != student.do_not_work_with.end() ||
            find_if(team_member.do_not_work_with.begin(), team_member.do_not_work_with.end(),
                    [&student_username_lower](const string &name)
                    {
                        return to_lower(name) == student_username_lower;
                    }) != team_member.do_not_work_with.end())
        {
            return false;
        }
    }

    return !student_in_team_not_work_with;
}

Student find_student_by_username(const vector<Student> &students, const string &username)
{
    string username_lower = to_lower(username);
    for (const auto &student : students)
    {
        if (to_lower(student.username) == username_lower)
        {
            return student;
        }
    }
    return Student();
}

vector<Student> students_that_favor_user(vector<Student> &students, const string &username)
{
    string username_lower = to_lower(username);
    vector<Student> students_that_favor_user;
    for (const auto &student : students)
    {
        if (find_if(student.prefer_to_work_with.begin(), student.prefer_to_work_with.end(),
                    [&username_lower](const string &name)
                    {
                        return to_lower(name) == username_lower;
                    }) != student.prefer_to_work_with.end())
        {
            students_that_favor_user.push_back(student);
        }
    }
    return students_that_favor_user;
}

void remove_from_preferred_students(vector<Student> &students_with_preferred_students, Student &student)
{
    auto it = find(students_with_preferred_students.begin(), students_with_preferred_students.end(), student);
    if (it != students_with_preferred_students.end())
    {
        students_with_preferred_students.erase(it);
    }
}

void add_students_to_team(const vector<int> &skill_levels, vector<Student> &current_team, vector<string> &team_not_work_with,
                          map<int, vector<Student>> &programming_students, vector<Student> &students_not_in_team)
{
    for (const auto skill_level : skill_levels)
    {
        if (!programming_students[skill_level].empty())
        {
            Student student = programming_students[skill_level].back();
            programming_students[skill_level].pop_back();
            if (allowed_to_work_with(team_not_work_with, student, current_team))
            {
                current_team.push_back(student);
                add_to_team_not_work_with(team_not_work_with, student);
            }
            else
            {
                students_not_in_team.push_back(student);
            }
            return;
        }
    }
}

void add_to_team_not_work_with(vector<string> &team_not_work_with, Student &student)
{
    for (const auto &partner : student.do_not_work_with)
    {
        team_not_work_with.push_back(partner);
    }
}

int calculate_total_score(const vector<Student> &team, string skill)
{
    int sum = 0;
    if (skill == "programming")
    {
        for (const auto &student : team)
        {
            sum += student.programming;
        }
    }
    if (skill == "debugging")
    {
        for (const auto &student : team)
        {
            sum += student.debugging;
        }
    }
    if (skill == "design")
    {
        for (const auto &student : team)
        {
            sum += student.design;
        }
    }
    return sum;
}

void print_teams(map<int, vector<Student>> &teams)
{
    cout << "All teams: " << endl;
    for (const auto &team : teams)
    {
        int total_programming = calculate_total_score(team.second, "programming");
        int total_debugging = calculate_total_score(team.second, "debugging");
        int total_design = calculate_total_score(team.second, "design");
        cout << "Team " << team.first << ": " << endl;
        for (const auto &student : team.second)
        {
            cout << student.username << " ";
        }
        cout << endl;
        cout << "Programming score: " << total_programming << endl;
        cout << "Debugging score: " << total_debugging << endl;
        cout << "Design score: " << total_design << endl;
        cout << "Total score: "
             << total_debugging + total_design + total_programming << endl;
        cout << "---------------------" << endl;
    }
}

void create_teams_csv(map<int, vector<Student>> &teams)
{
    // calling the file teams.csv everytime
    ofstream file("teams.csv");
    if (!file.is_open())
    {
        cout << "Could not open file" << endl;
        return;
    }

    for (const auto &team : teams)
    {
        file << "Team " << team.first << ": ";
        for (const auto &student : team.second)
        {
            file << student.username << ", ";
        }
        file << endl;
    }
    cout << "Teams have been saved to teams.csv" << endl;
}

void create_teams(vector<Student> &students, int team_size,
                  map<int, vector<Student>> &teams, string preference)
{
    // user specifies they want to create teams based on level
    if (preference == "L")
    {
        map<int, vector<Student>> programming_students;
        for (const auto &student : students)
        {
            programming_students[student.programming].push_back(student);
        }

        // map which describes the levels we want the students to have
        map<int, vector<int>> priority_map = {
            {1, {3, 2, 1}}, {2, {2, 1, 3}}, {3, {1, 2, 3}}};

        if (team_size == 4)
        {
            priority_map[4] = {2, 3, 1};
        }

        int team_number = 1;
        while (!programming_students[1].empty() ||
               !programming_students[2].empty() ||
               !programming_students[3].empty())
        {
            vector<Student> current_team;
            vector<string> team_not_work_with;
            vector<Student> students_not_in_team;

            for (const auto &entry : priority_map)
            {
                add_students_to_team(entry.second, current_team, team_not_work_with,
                                     programming_students, students_not_in_team);
            }

            for (const auto &student : students_not_in_team)
            {
                programming_students[student.programming].push_back(student);
            }

            teams[team_number++] = current_team;
        }
    }
    // user decides to create teams by preference
    else if (preference == "P")
    {
        int team_number = 1;
        vector<Student> students_copy = students;
        vector<Student> students_with_preferred_students;

        // Collect students who have preferences
        for (const auto &student : students)
        {
            if (!student.prefer_to_work_with.empty())
            {
                students_with_preferred_students.push_back(student);
            }
        }

        while (!students_copy.empty())
        {
            vector<string> team_not_work_with;
            vector<Student> current_team;
            Student current_student;

            // try to get a student with preferred students otherwise get a random student
            if (!students_with_preferred_students.empty())
            {
                current_student = students_with_preferred_students.back();
                students_with_preferred_students.pop_back();
                auto it = find(students_copy.begin(), students_copy.end(), current_student);
                if (it != students_copy.end())
                {
                    students_copy.erase(it);
                }
            }
            else
            {
                current_student = students_copy.back();
                students_copy.pop_back();
            }

            // add student to current team
            current_team.push_back(current_student);
            add_to_team_not_work_with(team_not_work_with, current_student);
            vector<string> attempted_students;

            // Add preferred students to the current team
            while (!current_student.prefer_to_work_with.empty() && current_team.size() < team_size)
            {
                string next_student_string = current_student.prefer_to_work_with.back();
                current_student.prefer_to_work_with.pop_back();
                Student next_student = find_student_by_username(students, next_student_string);
                // ensure the student exists, is allowed to work with the team, and is not in a team already
                if (!next_student.username.empty() && allowed_to_work_with(team_not_work_with, next_student, current_team) &&
                    find(students_copy.begin(), students_copy.end(), next_student) != students_copy.end())
                {
                    current_team.push_back(next_student);
                    add_to_team_not_work_with(team_not_work_with, next_student);
                    auto it = find(students_copy.begin(), students_copy.end(), next_student);
                    if (it != students_copy.end())
                    {
                        students_copy.erase(it);
                    }
                    remove_from_preferred_students(students_with_preferred_students, next_student);
                }
                else
                {
                    attempted_students.push_back(next_student.username);
                }
            }

            // repopulate the current students preferred to work with with all of the failed students
            for (const auto &student : attempted_students)
            {
                current_student.prefer_to_work_with.push_back(student);
            }

            // Add students who favor current team members
            for (auto &student : current_team)
            {
                vector<Student> students_who_favor_user = students_that_favor_user(students, student.username);
                for (auto &favoring_student : students_who_favor_user)
                {
                    if (allowed_to_work_with(team_not_work_with, favoring_student, current_team) && current_team.size() < team_size &&
                        find(students_copy.begin(), students_copy.end(), favoring_student) != students_copy.end())
                    {
                        current_team.push_back(favoring_student);
                        add_to_team_not_work_with(team_not_work_with, favoring_student);

                        // remove the student from students_copy
                        auto it = find(students_copy.begin(), students_copy.end(), favoring_student);
                        if (it != students_copy.end())
                        {
                            students_copy.erase(it);
                        }
                        remove_from_preferred_students(students_with_preferred_students, favoring_student);
                    }
                }
            }

            // Fill the team with remaining students
            for (auto it = students_copy.begin(); it != students_copy.end() && current_team.size() < team_size;)
            {
                if (allowed_to_work_with(team_not_work_with, *it, current_team))
                {
                    current_team.push_back(*it);
                    add_to_team_not_work_with(team_not_work_with, *it);
                    remove_from_preferred_students(students_with_preferred_students, *it);
                    it = students_copy.erase(it);
                }
                else
                {
                    ++it;
                }
            }

            // add the team to the list of teams and increment the teams counter
            teams[team_number++] = current_team;
        }
    }
}
