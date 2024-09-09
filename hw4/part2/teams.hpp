#ifndef TEAMS_HPP
#define TEAMS_HPP

#include "student.hpp"
#include <map>
#include <string>
#include <vector>

using namespace std;

/*
 * @brief This function creates teams of students based on the team size and
 * student preferences
 *
 * @param students: The vector of students to create teams from
 * @param team_size: The size of the teams to create
 * @param teams: The map of teams, with a team number as the key and a vector of
 * students as the value
 * @param preference: The preference of the students to prioritize
 *
 * @return: void
 */
void create_teams(vector<Student> &students, int team_size,
                  map<int, vector<Student>> &teams, string preference);

/*
 * @brief This function prints the teams of students
 *
 * @param students: The vector of students to print the teams from
 *
 * @return: void
 */
void print_teams(map<int, vector<Student>> &teams);

/*
 * @brief This function calculates the total score of a team based on the skill
 *
 * @param team: The vector of students to calculate the total score from
 * @param skill: The skill to calculate the total score from
 *
 * @return: int
 */
int calculate_total_score(const vector<Student> &team, string skill);

/*
 * @brief This function determines if a student is allowed to work with a team
 *
 * @param team_not_work_with: The vector of students that a student is not
 * allowed to work with
 * @param student: The student to determine if they are allowed to work with the
 * team
 *
 * @return: bool
 */
bool allowed_to_work_with(const vector<string> &team_not_work_with,
                          const Student &student, const vector<Student> &team);

Student find_student_by_username(const vector<Student> &students,
                                 const string &username);

/*
 * @brief This function adds students to a team based on the skill level
 *
 * @param skill_levels: The vector of skill levels to add students to the team
 * @param current_team: The vector of students in the current team
 * @param team_not_work_with: The vector of students that a student is not
 * allowed to work with
 * @param programming_students: The map of programming students to add students
 * to the team
 * @param students_not_in_team: The vector of students that are not in the team
 *
 * @return: void
 */
void add_students_to_team(const vector<int> &skill_levels,
                          vector<Student> &current_team,
                          vector<string> &team_not_work_with,
                          map<int, vector<Student>> &programming_students,
                          vector<Student> &students_not_in_team);

/*
 * @brief This function adds student to the not work with list
 *
 * @param team_not_work_with: The vector of students that a student is not
 * allowed to work with
 * @param student: The student to add to the not work with list
 *
 * @return: void
 */
void add_to_team_not_work_with(vector<string> &team_not_work_with,
                               Student &student);

/*
 * @brief This function creates a csv file of the teams
 *
 * @param teams: The map of teams to create the csv file from
 *
 * @return: void
 */
void create_teams_csv(map<int, vector<Student>> &teams);

/*
 * @brief This function finds the students that favors (prefers) the specified student
 *
 * @param students: The vector of students to search from
 * @param student: The student to find the students that favors them
 *
 * @return: vector<Student>
 */
vector<Student> students_that_favor_user(vector<Student> &students, const string &username);

/*
 * @brief This function removes the specified student from the preferred students list
 *
 * @param students_with_preferred_students: The vector of students with preferred students
 * @param student: The student to remove from the preferred students list
 *
 * @return: void
 */
void remove_from_preferred_students(vector<Student> &students_with_preferred_students, Student &student);

/*
 * @brief This function converts a string to lowercase
 *
 * @param str: The string to convert to lowercase
 *
 * @return: string
 */
string to_lower(const string &str);

#endif
