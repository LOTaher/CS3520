#include <stdio.h>

#define MAX_LETTERS 26

char alphabet[MAX_LETTERS];

void initialize_array(char *a) {
    char *p;
    char current_letter = 'a';

    // changed <= to <
    for (p = a; p < (a + MAX_LETTERS); p++) {
        *p = current_letter++;
    }
}

void print_characters_in_reverse(char *b) {
    // removed var initalization and checks
    char *p;

    printf("\nReversing alphabets...\n");

    for (p = (b + MAX_LETTERS - 1); p >= b; p--) {
        printf("%c ", *p);
    }
    printf("\n");
}

int main(void) {
    // moved initialize array to the main function
    initialize_array(alphabet);

    // changed i < 5 to i < 10 to have the alphabet get printed 10 times
    for (int i = 1; i <= 10; i++) {
        print_characters_in_reverse(alphabet);
    }

    return 0;
}

