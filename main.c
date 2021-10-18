//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#include "my_clib.h"
#include "stdio.h"

void test_substrings() {
    string s = new_string("abacabadabacabafabacabadabacabagabacabadabacabafabacabadabacaba");
    unsigned long i;

    string substr = new_string("cabafabacabad");
    unsigned long* positions = NULL;
    unsigned long num_of_occurrences = find_substrings(s, substr, &positions);
    printf("%lu occurrences found:\n", num_of_occurrences);
    for (i = 0; i < num_of_occurrences; i++)
        printf("%lu ", positions[i]);
    printf("\n");

    delete_string(s);
    delete_string(substr);
    free(positions);
}


int main() {
    string s1 = new_string("moloko");
    string s2 = new_string("kolokol");
    printf("%lu\n", get_levenstein_distance(s1, s2));

    delete_string(s1);
    delete_string(s2);

    return 0;
}

