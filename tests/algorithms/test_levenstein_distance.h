//
// Created by Mikhail Tsaritsyn on 20.10.2021.
//

#ifndef MY_CLIB_TEST_LEVENSTEIN_DISTANCE_H
#define MY_CLIB_TEST_LEVENSTEIN_DISTANCE_H

#include "algorithms/levenstein_distance.h"
#include "../test_helpers.h"


int validate_test_case(const char *s1, const char* s2, unsigned long target_value, unsigned int testcase_num);


int test_empty_string(void);


int test_distance_symmetry(void);


int test_equal_strings(void);


int test_arbitrary_strings(void);


int full_levenstein_distance_test_set(void);


#endif //MY_CLIB_TEST_LEVENSTEIN_DISTANCE_H
