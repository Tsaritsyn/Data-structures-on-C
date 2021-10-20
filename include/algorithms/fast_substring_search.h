//
// Created by Mikhail Tsaritsyn on 18.10.2021.
//

#ifndef MY_CLIB_FAST_SUBSTRING_SEARCH_H
#define MY_CLIB_FAST_SUBSTRING_SEARCH_H

#include "data_structures/my_string.h"
#include "data_structures/array.h"

/**
 * Searches for all occurrences of the second string in the first one.
 *
 * @return array of occurrence positions
 */
array_u_long_ptr find_substrings(const_string_ptr, const_string_ptr);

/**
 * For each substring computes the maximal length of its prefix that is at the same time its suffix.
 *
 * @return array of the values for each substring, ith value corresponds to the substring ending on the ith position
 */
array_u_long_ptr get_prefix_functions(const_string_ptr);

#endif //MY_CLIB_FAST_SUBSTRING_SEARCH_H
