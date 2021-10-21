//
// Created by Mikhail Tsaritsyn on 20.10.2021.
//

#ifndef MY_CLIB_TEST_HELPERS_H
#define MY_CLIB_TEST_HELPERS_H

#include <stdio.h>
#include <string.h>

#include "common.h"
#include "data_structures.h"


#define declare_numeric_value_validation(type) \
int validate_##type##_value(type value, type target_value, unsigned int cur_check);

declare_numeric_value_validation(int)
declare_numeric_value_validation(short)
declare_numeric_value_validation(char)
declare_numeric_value_validation(long)
declare_numeric_value_validation(float)
declare_numeric_value_validation(double)
declare_numeric_value_validation(u_int)
declare_numeric_value_validation(u_short)
declare_numeric_value_validation(u_char)
declare_numeric_value_validation(u_long)


#define declare_array_validation(array_type) \
int validate_##array_type(const array_type* arr, const array_type* target_arr, unsigned int cur_check);

declare_array_validation(array_int)
declare_array_validation(array_short)
declare_array_validation(array_char)
declare_array_validation(array_long)
declare_array_validation(array_float)
declare_array_validation(array_double)
declare_array_validation(array_u_int)
declare_array_validation(array_u_short)
declare_array_validation(array_u_char)
declare_array_validation(array_u_long)


void print_test_series_start_message(const char* test_series_name);


int validate_test_series(const char* test_series_name, unsigned int tests_total, unsigned int tests_passed);


void print_test_start_message(const char* test_name);


int validate_test(const char *test_name, unsigned int checks_total, unsigned int checks_passed);


#endif //MY_CLIB_TEST_HELPERS_H
