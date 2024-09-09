/*
Laith Taher (5/8/2024)
This program reads a paragraph from the keyboard, prints it, then calculates and
prints the following statistics:
 - Number of total words in the paragraph
 - Number of vowels and consonants used
 - Number of words that use exactly two vowels
 - Number of words that use any one of these eight punctuation marks: ! . , ; "
' ? $ It then prompts the user to enter a number (i.e., length of a word) and
calculates and prints the following:
 - Number of words with length smaller or equal to the user provided length.
It then updates the program to automatically select a random number (i.e.,
length of a word) between [3-9] and prints:
 - Number of words with length smaller than the random length. Use punctuation
marks in calculating length of words.
*/

#include <cctype>
#include <iostream>
#include <string>

using namespace std;

int main() {

  string paragraph;
  cout << "Enter a paragraph: ";
  // Gets the entire line of input
  getline(cin, paragraph);

  // Accounting for no space at the beginning of the paragraph
  int total_words = 1;
  int vowels = 0;
  int consonants = 0;
  int two_vowels = 0;
  int punctuation = 0;

  char all_vowels[10] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
  char all_punctuation[8] = {'!', '.', ',', ';', '"', '?', '$'};

  bool current_word = false;
  int current_word_vowels = 0;

  for (int i = 0; i < paragraph.length(); i++) {
    // Check if the character is a letter OR an apostrophe for words like
    // "can't"
    if (isalpha(paragraph[i]) || paragraph[i] == '\'') {
      // If the character is not being accounted as a current word, set it to be
      // one.
      if (!current_word) {
        current_word = true;
        current_word_vowels = 0;
      }
      // For each letter, check if it is any of the vowels
      bool is_vowel = false;
      for (char vowel : all_vowels) {
        if (paragraph[i] == vowel) {
          vowels++;
          current_word_vowels++;
          // If the letter is a vowel, set the flag to true. It will be set back
          // to false after.
          is_vowel = true;
        }
      }
      // If the letter is not a vowel or an apostrophe, increment the consonant
      if (!is_vowel && paragraph[i] != '\'') { 
        consonants++;
      }

      if (paragraph[i] == '\'') {
        // If the character is an apostrophe, check if it is a part of a
        // contraction.
        if (i + 1 < paragraph.length() && isalpha(paragraph[i + 1])) {
          consonants++;
        }
        punctuation++;
      }
    } else {
      // At this point there is only a space or punctuation, meaning the word
      // ended.
      if (current_word) {
        // Because there is only a space or punctuation, the word ended, meaning
        // there will be no more vowels.
        if (current_word_vowels == 2) {
          two_vowels++;
        }
        // The word is no longer being accounted for because it has ended.
        current_word = false;
        total_words++;
      }
      // Check if the character is a punctuation mark
      if (!isalpha(paragraph[i]) && paragraph[i] != ' ') {
        for (char punc : all_punctuation) {
          if (paragraph[i] == punc) {
            punctuation++;
          }
        }
      }
    }
  }

  // Accounting for the possibility of no space or punctuation at the end of the
  // paragraph
  if (current_word) {
    if (current_word_vowels == 2) {
      two_vowels++;
    }
  }

  cout << "Total words: " << total_words << endl;
  cout << "Total vowels: " << vowels << endl;
  cout << "Total consonants: " << consonants << endl;
  cout << "Words with exactly two vowels: " << two_vowels << endl;
  cout << "Total punctuation marks: " << punctuation << endl;

  cout << " " << endl;

  cout << "Enter a number: ";

  //   Now, prompt the user to enter a number (i.e., length of a word) and then
  //   calculate {and print}
  // the following:
  // • Number of words with length smaller or equal to the user provided length.
  // Don’t count the punctuation marks in word length.
  int user_length;
  int total_provided_length = 0;
  cin >> user_length;

  if (user_length < 0) {
    cout << "Invalid input" << endl;
    return 0;
  }

  for (int i = 0; i < paragraph.length(); i++) {
    if (isalpha(paragraph[i]) || paragraph[i] == '\'') {
      int word_length = 0;
      while (isalpha(paragraph[i]) || paragraph[i] == '\'') {
        word_length++;
        i++;
      }
      if (word_length <= user_length) {
        total_provided_length++;
      }
    }
  }

  cout << "Words with length smaller or equal to " << user_length << ": "
       << total_provided_length << endl;

  cout << " " << endl;

  //   Now, update your program to {automatically} select a random number (i.e.,
  //   length of a word)
  // between [3-9] and then print:
  // • Number of words with length smaller than the random length. Use
  // punctuation marks in calculating length of words.
  int random_length = rand() % 7 + 3;
  int total_random_length = 0;

  for (int i = 0; i < paragraph.length(); i++) {
    if (isalpha(paragraph[i]) || paragraph[i] == '\'') {
      int word_length = 0;
      while (isalpha(paragraph[i]) || paragraph[i] == '\'') {
        word_length++;
        i++;
      }
      if (word_length < random_length) {
        total_random_length++;
      }
    }
  }

  cout << "Random length: " << random_length << endl;
  cout << "Words with length smaller than the random length: "
       << total_random_length << endl;

  return 0;
}
