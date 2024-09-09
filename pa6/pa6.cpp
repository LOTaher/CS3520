// Laith Taher and Aaryan Jain

// Include cstring for strcpy
#include <cstring> 
#include <iostream>
#include <string>
using namespace std;

struct tv_series {
  char *series_name;
  int first_release_year;
  int first_release_month;
  struct tv_episode {
    char episode_name[30];
    int episode_number;
    string episode_release_date;
    double episode_rating;
  };
  struct {
    int season_number;
    tv_episode episodes[7];
  } seasons[3], *seasons_ptr = seasons;
} the_office, *ptr_the_office = &the_office;

int main() {
  // Part A
  the_office.series_name = (char *)"The Office";
  the_office.first_release_year = 2005;
  the_office.first_release_month = 3;

  // Part B
  // Create objects for each episode for Season 1
  tv_series::tv_episode episode_1_1 = {"Pilot", 1, "2005-03-24", 7.3};
  tv_series::tv_episode episode_1_2 = {"Diversity Day", 2, "2005-03-29", 8.1};
  tv_series::tv_episode episode_1_3 = {"Health Care", 3, "2005-04-05", 7.6};
  tv_series::tv_episode episode_1_4 = {"The Alliance", 4, "2005-04-12", 7.8};
  tv_series::tv_episode episode_1_5 = {"Basketball", 5, "2005-04-19", 8.2};
  tv_series::tv_episode episode_1_6 = {"Hot Girl", 6, "2005-04-26", 7.5};
  tv_series::tv_episode episode_1_7 = {"The Dundies", 7, "2005-05-03", 8.6};

  // Assign episodes to Season 1
  the_office.seasons[0].season_number = 1;
  the_office.seasons[0].episodes[0] = episode_1_1;
  the_office.seasons[0].episodes[1] = episode_1_2;
  the_office.seasons[0].episodes[2] = episode_1_3;
  the_office.seasons[0].episodes[3] = episode_1_4;
  the_office.seasons[0].episodes[4] = episode_1_5;
  the_office.seasons[0].episodes[5] = episode_1_6;
  the_office.seasons[0].episodes[6] = episode_1_7;

  // Create objects for each episode for Season 2
  tv_series::tv_episode episode_2_1 = {"Sexual Harassment", 1, "2005-09-27", 8.1};
  tv_series::tv_episode episode_2_2 = {"Office Olympics", 2, "2005-10-04", 8.2};
  tv_series::tv_episode episode_2_3 = {"The Fire", 3, "2005-10-11", 8.1};
  tv_series::tv_episode episode_2_4 = {"Halloween", 4, "2005-10-18", 7.9};
  tv_series::tv_episode episode_2_5 = {"The Fight", 5, "2005-11-01", 7.9};
  tv_series::tv_episode episode_2_6 = {"The Client", 6, "2005-11-08", 8.5};
  tv_series::tv_episode episode_2_7 = {"Performance Review", 7, "2005-11-15", 8.0};

  // Assign episodes to Season 2
  the_office.seasons[1].season_number = 2;
  the_office.seasons[1].episodes[0] = episode_2_1;
  the_office.seasons[1].episodes[1] = episode_2_2;
  the_office.seasons[1].episodes[2] = episode_2_3;
  the_office.seasons[1].episodes[3] = episode_2_4;
  the_office.seasons[1].episodes[4] = episode_2_5;
  the_office.seasons[1].episodes[5] = episode_2_6;
  the_office.seasons[1].episodes[6] = episode_2_7;

  // Create objects for each episode for Season 3
  tv_series::tv_episode episode_3_1 = {"The Convention", 1, "2006-09-28", 8.0};
  tv_series::tv_episode episode_3_2 = {"The Coup", 2, "2006-10-05", 8.4};
  tv_series::tv_episode episode_3_3 = {"Grief Counseling", 3, "2006-10-12", 7.8};
  tv_series::tv_episode episode_3_4 = {"Initiation", 4, "2006-10-19", 7.9};
  tv_series::tv_episode episode_3_5 = {"Diwali", 5, "2006-11-02", 7.7};
  tv_series::tv_episode episode_3_6 = {"Branch Closing", 6, "2006-11-09", 8.5};
  tv_series::tv_episode episode_3_7 = {"The Merger", 7, "2006-11-16", 8.6};

  // Assign episodes to Season 3
  the_office.seasons[2].season_number = 3;
  the_office.seasons[2].episodes[0] = episode_3_1;
  the_office.seasons[2].episodes[1] = episode_3_2;
  the_office.seasons[2].episodes[2] = episode_3_3;
  the_office.seasons[2].episodes[3] = episode_3_4;
  the_office.seasons[2].episodes[4] = episode_3_5;
  the_office.seasons[2].episodes[5] = episode_3_6;
  the_office.seasons[2].episodes[6] = episode_3_7;

  // Output the data
  cout << "Series Name: " << the_office.series_name << endl;
  cout << "First Release Year: " << the_office.first_release_year << endl;
  cout << "First Release Month: " << the_office.first_release_month << endl;

  // Test data for the 3 seasons
  for (int i = 0; i < 3; ++i) {
    cout << "Season " << the_office.seasons[i].season_number << ":" << endl;
    for (int j = 0; j < 7; ++j) {
      cout << "  Episode " << the_office.seasons[i].episodes[j].episode_number
           << ": " << the_office.seasons[i].episodes[j].episode_name << ", "
           << the_office.seasons[i].episodes[j].episode_release_date << ", "
           << the_office.seasons[i].episodes[j].episode_rating << endl;
    }
  }
  cout << endl;

  // Part C
  the_office.series_name = new char[11]; // Allocate memory for the series name
  strcpy(the_office.series_name, "The Office");
  ptr_the_office->first_release_year = 2003;
  ptr_the_office->first_release_month = 3;

  // Assign episodes to Season 1
  ptr_the_office->seasons_ptr[0].season_number = 1;
  ptr_the_office->seasons_ptr[0].episodes[0] = episode_1_1;
  ptr_the_office->seasons_ptr[0].episodes[1] = episode_1_2;
  ptr_the_office->seasons_ptr[0].episodes[2] = episode_1_3;
  ptr_the_office->seasons_ptr[0].episodes[3] = episode_1_4;
  ptr_the_office->seasons_ptr[0].episodes[4] = episode_1_5;
  ptr_the_office->seasons_ptr[0].episodes[5] = episode_1_6;
  ptr_the_office->seasons_ptr[0].episodes[6] = episode_1_7;


  // Assign episodes to Season 2
  ptr_the_office->seasons_ptr[1].season_number = 2;
  ptr_the_office->seasons_ptr[1].episodes[0] = episode_2_1;
  ptr_the_office->seasons_ptr[1].episodes[1] = episode_2_2;
  ptr_the_office->seasons_ptr[1].episodes[2] = episode_2_3;
  ptr_the_office->seasons_ptr[1].episodes[3] = episode_2_4;
  ptr_the_office->seasons_ptr[1].episodes[4] = episode_2_5;
  ptr_the_office->seasons_ptr[1].episodes[5] = episode_2_6;
  ptr_the_office->seasons_ptr[1].episodes[6] = episode_2_7;

  // Assign episodes to Season 3
  ptr_the_office->seasons_ptr[2].season_number = 3;
  ptr_the_office->seasons_ptr[2].episodes[0] = episode_3_1;
  ptr_the_office->seasons_ptr[2].episodes[1] = episode_3_2;
  ptr_the_office->seasons_ptr[2].episodes[2] = episode_3_3;
  ptr_the_office->seasons_ptr[2].episodes[3] = episode_3_4;
  ptr_the_office->seasons_ptr[2].episodes[4] = episode_3_5;
  ptr_the_office->seasons_ptr[2].episodes[5] = episode_3_6;
  ptr_the_office->seasons_ptr[2].episodes[6] = episode_3_7;


  // Output the data using the pointer to the series structure
  cout << "Using pointer to the series structure:" << endl;
  cout << "Series Name: " << ptr_the_office->series_name << endl;
  cout << "First Release Year: " << ptr_the_office->first_release_year << endl;
  cout << "First Release Month: " << ptr_the_office->first_release_month << endl;

  // Test data for the 3 seasons using the pointer
  for (int i = 0; i < 3; ++i) {
    cout << "Season " << ptr_the_office->seasons_ptr[i].season_number << ":" << endl;
    for (int j = 0; j < 7; ++j) {
      cout << "  Episode " << ptr_the_office->seasons_ptr[i].episodes[j].episode_number
           << ": " << ptr_the_office->seasons_ptr[i].episodes[j].episode_name << ", "
           << ptr_the_office->seasons_ptr[i].episodes[j].episode_release_date << ", "
           << ptr_the_office->seasons_ptr[i].episodes[j].episode_rating << endl;
    }
  }

  // Clean up dynamically allocated memory
  delete[] the_office.series_name;

  return 0;
}
