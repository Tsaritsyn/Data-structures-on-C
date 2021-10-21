//
// Created by Mikhail Tsaritsyn on 18.10.2021.
//

#include "algorithms/levenstein_distance.h"


unsigned long get_levenstein_distance(const_string_ptr s1, const_string_ptr s2) {
    if (s1->length == 0)
        return s2->length;
    if (s2->length == 0)
        return s1->length;

//    we will allocate temporary arrays of the length of the shortest string to save memory
    const_string_ptr str_short = (s1->length < s2->length) ? s1 : s2;
    const_string_ptr str_long = (s1->length < s2->length) ? s2 : s1;

//    these arrays will be swapped on each iteration
    array_u_long_ptr previous_results = new_empty_array_u_long(str_short->length + 1);
    array_u_long_ptr current_results = new_constant_array_u_long(str_short->length + 1, 0);

//    initialize the distances for an empty second string
    unsigned long i;
    for (i = 0; i <= str_short->length; i++)
        array_u_long_append(previous_results, i);

    unsigned int j;
    for (i = 1; i <= str_long->length; i++) {
//        the case of empty first string
        current_results->elements[0] = i;
        for (j = 1; j <= str_short->length; j++)
            if (str_short->c_string[j-1] == str_long->c_string[i-1])
                current_results->elements[j] = previous_results->elements[j-1];
            else
//                minimum of dist(str1[:j-1], str2[:j]), dist(str1[:j], str2[:j-1]) and dist(str1[:j-1], str2[:j-1])
                current_results->elements[j] = 1 + MIN3(previous_results->elements[j],
                                                        previous_results->elements[j-1],
                                                        current_results->elements[j-1]);

//        swap the arrays, so current results will be used as the previous ones on the next iteration
        array_u_long_ptr temp = previous_results;
        previous_results = current_results;
        current_results = temp;
    }

//    remember, that the arrays have been swapped, so the last results are in the previous_results
    unsigned long result = previous_results->elements[previous_results->length - 1];
    delete_array_u_long(current_results);
    delete_array_u_long(previous_results);
    return result;
}

