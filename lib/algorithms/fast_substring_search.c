//
// Created by Mikhail Tsaritsyn on 18.10.2021.
//

#include "algorithms/fast_substring_search.h"

array_u_long_ptr find_substrings(const_string_ptr str, const_string_ptr substr) {
    char rare_symbol = '`';

    if (str->length == 0 || substr->length == 0)
        return new_empty_array_u_long(0);

//    construct a string_ptr substr + rare_symbol + str
    string_ptr temp = copy_string(substr);
    string_append(temp, rare_symbol);
    string_concat_to(temp, str);

    array_u_long_ptr p_functions = get_prefix_functions(temp);

    array_u_long_ptr result = new_empty_array_u_long(0);
    unsigned long i;
    for (i = 0; i < p_functions->length; i++)
        if (p_functions->elements[i] == substr->length)
            append_to_array(result, i - 2 * substr->length);

    delete_string(temp);
    delete_array(p_functions);

    return result;
}

array_u_long_ptr get_prefix_functions(const_string_ptr s) {
    array_u_long_ptr result = new_empty_array_u_long(s->length);
    unsigned long i;
    append_to_array(result, 0);

    for (i = 1; i < s->length; i++) {
        unsigned long p = result->elements[i-1];
        do {
            if (s->c_string[i] == s->c_string[p]) {
                p++;
                break;
            }
            else {
                p = (p != 0) ? result->elements[p-1] : 0;
            }
        } while (p != 0);
        append_to_array(result, p);
    }

    return result;
}