//
// Created by Mikhail Tsaritsyn on 22.10.2021.
//

#ifndef MY_CLIB_TEST_ARRAY_SORTING_H
#define MY_CLIB_TEST_ARRAY_SORTING_H

#include "algorithms/array_sorting.h"
#include "../test_helpers.h"

//#define declare_test_case_validation(array_type) \
//int validate_##array_type##_test_case(const array_type* arr1, const array_type* arr2, const array_type* target_array, unsigned int testcase_num);
//
//declare_test_case_validation(array_int)
//declare_test_case_validation(array_short)
//declare_test_case_validation(array_char)
//declare_test_case_validation(array_long)
//declare_test_case_validation(array_float)
//declare_test_case_validation(array_double)
//declare_test_case_validation(array_u_int)
//declare_test_case_validation(array_u_short)
//declare_test_case_validation(array_u_char)
//declare_test_case_validation(array_u_long)

int validate_array_int_sorting_test_case(array_int_ptr arr, const array_int* target_arr, unsigned int testcase_num);


int test_empty_array(void);


int test_sorted_array(void);


int test_reversely_sorted_array(void);


int test_arbitrary_array(void);


int full_sorting_test_set(void);

#endif //MY_CLIB_TEST_ARRAY_SORTING_H
