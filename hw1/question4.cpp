/*
Laith Taher (5/8/2024)

This program finds and replaces all occurences of inputted strings and replaces
them with their reversed spellings.
*/

#include <cctype>
#include <iostream>
#include <vector>
// Including algorithm for the find() function
#include <algorithm>
using namespace std;

int main() {

  cout << "Input a paragraph: " << endl;
  string paragraph;

  getline(cin, paragraph);

  cout << " " << endl;

  cout << "Input (case sensitive) words (must be seperated by spaces) or a "
          "sentence that you would like to find and replace."
       << endl;

  string word_input;

  getline(cin, word_input);

  cout << " " << endl;

  // Using vectors to avoid predefining array sizes
  vector<string> paragraph_words;
  vector<int> words_location;

  // Count the number of words in the paragraph and store them
  for (int i = 0; i < paragraph.length(); i++) {
    string word = "";
    while (isalpha(paragraph[i])) {
      word += paragraph[i];
      i++;
    }
    words_location.push_back(i - word.length());
    paragraph_words.push_back(word);
  }

  vector<string> inputted_words;
  vector<int> inputted_words_location;

  // Keep track of inputted words to replace and make sure they're contained in
  // the paragraph
  for (int i = 0; i < word_input.length(); i++) {
    string word = "";
    while (isalpha(word_input[i])) {
      word += word_input[i];
      i++;
    }

    // Check to see if the inputted word exists in the paragraph
    if (find(paragraph_words.begin(), paragraph_words.end(), word) == paragraph_words.end()) {
      cout << "Word: " << word << " does not exist in the paragraph" << endl;
      return 0;
    }

    // Add the inputted word to the words to be replaced vector
    inputted_words.push_back(word);

    // Find the location of the inputted word using the paragraph words indexes
    // and then their respective start indexes
    for (int i = 0; i < paragraph_words.size(); i++) {
      if (paragraph_words[i] == word) {
        inputted_words_location.push_back(words_location[i]);
      }
    }
  }

  vector<string> reversed_words;
  // Reverse the inputted words
  for (int i = 0; i < inputted_words.size(); i++) {
    string reversed_word = "";
    for (int j = inputted_words[i].length() - 1; j >= 0; j--) {
      reversed_word += inputted_words[i][j];
    }
    reversed_words.push_back(reversed_word);
  }

  // Print out the amount of occurences of each word and the index(es) it is
  // found at. Sort it by index
  /*
   * Input paragraph: hello world hello test
   * Input words: hello world
   * Word: hello | Occurence: 1 | Index: 0
   * Word: hello | Occurence: 2 | Index 7
   * Word: world | Occurence: 1 | Index: 6
   */
  for (int i = 0; i < inputted_words.size(); i++) {
    int occurence = 0;
    for (int j = 0; j < paragraph_words.size(); j++) {
      if (paragraph_words[j] == inputted_words[i]) {
        occurence++;
        cout << "Word: " << inputted_words[i] << " | Occurence: " << occurence
             << " | Index: " << words_location[j] << endl;
      }
    }
  }

  cout << " " << endl;

  cout << "Old paragraph: " << endl;
  cout << paragraph << endl;

  // Place the reverse words back into the paragraph, and replace the old words
  for (int i = 0; i < inputted_words.size(); i++) {
    for (int j = 0; j < paragraph.length(); j++) {
      // Check if a substring of the paragraph is equal to the inputted word
      if (paragraph.substr(j, inputted_words[i].length()) == inputted_words[i]) {
        // Replace the word with the reversed word
        paragraph.replace(j, inputted_words[i].length(), reversed_words[i]);
      }
    }
  }

  cout << "New paragraph: " << endl;
  cout << paragraph << endl;

  return 0;
}
