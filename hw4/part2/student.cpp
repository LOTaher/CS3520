#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "student.hpp"
#include <algorithm>

using namespace std;

// given a skill rating will return the enum related to the level
skill_rating convert_skill_rating(const string &level)
{
    if (level == "Beginner")
    {
        return Beginner;
    }
    else if (level == "Intermediate")
    {
        return Intermediate;
    }
    else if (level == "Advanced")
    {
        return Advanced;
    }
    else
    {
        throw invalid_argument("Invalid skill rating level");
    }
}

// Function to trim trailing whitespace from a string
void trim_trailing_whitespace(string &str)
{
    str.erase(find_if_not(str.rbegin(), str.rend(), [](int ch)
                          { return isspace(ch); })
                  .base(),
              str.end());
}

// reads all the students from the csv and populates a students vector
void read_students_results(const string &file_name, vector<Student> &students)
{
    ifstream file(file_name);
    if (!file.is_open())
    {
        throw runtime_error("Could not open file");
    }

    string line;
    getline(file, line); // Skip the header line

    while (getline(file, line))
    {
        stringstream ss(line);
        string username, level_prog, level_debug, level_design, do_not_work_with, prefer_to_work_with;

        getline(ss, username, ',');
        getline(ss, level_prog, ',');
        getline(ss, level_debug, ',');
        getline(ss, level_design, ',');
        getline(ss, do_not_work_with, ',');
        getline(ss, prefer_to_work_with);

        // Remove trailing whitespace
        trim_trailing_whitespace(prefer_to_work_with);

        Student student;
        student.username = username;
        student.programming = convert_skill_rating(level_prog);
        student.debugging = convert_skill_rating(level_debug);
        student.design = convert_skill_rating(level_design);

        // populates the do_not_work_with and prefer_to_work_with by seperated by ;
        stringstream ss_donot(do_not_work_with);
        string name;
        while (getline(ss_donot, name, ';'))
        {
            student.do_not_work_with.push_back(name);
        }

        stringstream ss_prefer(prefer_to_work_with);
        while (getline(ss_prefer, name, ';'))
        {
            student.prefer_to_work_with.push_back(name);
        }

        students.push_back(student);
    }
    file.close();
}
