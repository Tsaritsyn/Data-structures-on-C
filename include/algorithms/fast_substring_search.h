//
// Created by Mikhail Tsaritsyn on 18.10.2021.
//

#ifndef MY_CLIB_FAST_SUBSTRING_SEARCH_H
#define MY_CLIB_FAST_SUBSTRING_SEARCH_H

#include "data_structures/my_string.h"

/**
 * Searches for all occurrences of the second string_object in the first one. Writes their starting positions into the given
 * array.
 *
 * @return number of substring occurrences
 */
unsigned long find_substrings(const_string, const_string, unsigned long**);

/**
 * For each substring computes the maximal length of its prefix that is at the same time its suffix.
 *
 * @return array of the values for each substring, ith value corresponds to the substring ending on the ith position
 */
unsigned long* get_prefix_functions(const_string);

#endif //MY_CLIB_FAST_SUBSTRING_SEARCH_H
