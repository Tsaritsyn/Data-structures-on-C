//
// Created by Mikhail Tsaritsyn on 20.10.2021.
//

#ifndef MY_CLIB_TEST_HELPERS_H
#define MY_CLIB_TEST_HELPERS_H

#include <stdio.h>
#include <string.h>

#include "common.h"


int validate_u_long_value(unsigned long value, unsigned long target_value, unsigned int cur_check);


void print_test_series_start_message(const char* test_series_name);


int validate_test_series(const char* test_series_name, unsigned int tests_total, unsigned int tests_passed);


void print_test_start_message(const char* test_name);


int validate_test(const char *test_name, unsigned int checks_total, unsigned int checks_passed);


#endif //MY_CLIB_TEST_HELPERS_H
