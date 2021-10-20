//
// Created by Mikhail Tsaritsyn on 20.10.2021.
//

#ifndef MY_CLIB_TEST_SUBSTRING_SEARCH_H
#define MY_CLIB_TEST_SUBSTRING_SEARCH_H

#include "../test_helpers.h"
#include "algorithms/fast_substring_search.h"


int validate_negative_test_case(const char *s, const char *sub, unsigned int testcase_num);


int validate_positive_test_case(const char *s, const char *sub,
                                unsigned long target_value, unsigned long target_array[],
                                unsigned int testcase_num);


int test_search_on_empty_string(void);


int test_search_of_empty_substring(void);


int test_search_of_non_existent_substring(void);


int test_correct_search(void);


int full_substring_search_testset(void);



#endif //MY_CLIB_TEST_SUBSTRING_SEARCH_H
