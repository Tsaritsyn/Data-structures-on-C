//
// Created by Mikhail Tsaritsyn on 21.10.2021.
//

#ifndef MY_CLIB_TEST_SUBSEQUENCE_SEARCH_H
#define MY_CLIB_TEST_SUBSEQUENCE_SEARCH_H

#include "algorithms/greatest_common_subsequence.h"
#include "../test_helpers.h"


#define declare_test_case_validation(array_type) \
int validate_##array_type##_test_case(const array_type* arr1, const array_type* arr2, const array_type* target_array, unsigned int testcase_num);

declare_test_case_validation(array_int)
declare_test_case_validation(array_short)
declare_test_case_validation(array_char)
declare_test_case_validation(array_long)
declare_test_case_validation(array_float)
declare_test_case_validation(array_double)
declare_test_case_validation(array_u_int)
declare_test_case_validation(array_u_short)
declare_test_case_validation(array_u_char)
declare_test_case_validation(array_u_long)


int test_empty_arrays(void);


int test_for_swapped_arrays(void);


int test_equal_arrays(void);


int test_array_with_no_common_elements(void);


int test_correct_arrays(void);


int full_gcs_test_set(void);

#endif //MY_CLIB_TEST_SUBSEQUENCE_SEARCH_H
