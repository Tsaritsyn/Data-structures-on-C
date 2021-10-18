//
// Created by Mikhail Tsaritsyn on 18.10.2021.
//

#include "algorithms/fast_substring_search.h"

unsigned long find_substrings(const_string str, const_string substr, unsigned long** result) {
    char rare_symbol = '`';

//    construct a string substr + rare_symbol + str
    string_object *temp = copy_string(substr);
    string_append(temp, rare_symbol);
    string_concat_to(temp, str);

    unsigned long* p_functions = get_prefix_functions(temp);

    unsigned long num_substr_found = 0;
    unsigned long i;
    for (i = substr->length + 2; i < temp->length; i++)
        if (p_functions[i] == substr->length)
            num_substr_found++;

    unsigned long* positions = malloc(sizeof(unsigned long) * num_substr_found);
    unsigned long k = 0;
    for (i = substr->length + 1; i < temp->length; i++)
        if (p_functions[i] == substr->length)
            positions[k++] = i - 2 * substr->length;
    result[0] = positions;

    delete_string(temp);
    free(p_functions);
    return num_substr_found;
}

unsigned long* get_prefix_functions(const_string s) {
    unsigned long* result = malloc(sizeof(unsigned long) * s->length);
    unsigned long i;
    unsigned long init_value = s->length + 1;
    result[0] = 0;

    for (i = 1; i < s->length; i++) {
        unsigned long p = result[i-1];
        do {
            if (s->c_string[i] == s->c_string[p]) {
                p++;
                break;
            }
            else {
                p = (p != 0) ? result[p-1] : 0;
            }
        } while (p != 0);
        result[i] = p;
    }

    return result;
}