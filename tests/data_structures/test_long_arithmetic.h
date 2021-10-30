//
// Created by Mikhail Tsaritsyn on 29.10.2021.
//

#ifndef MY_CLIB_TEST_LONG_ARITHMETIC_H
#define MY_CLIB_TEST_LONG_ARITHMETIC_H

#include "data_structures/long_arithmetics.h"
#include "../test_helpers.h"


int validate_long_long_operation(const char* literal1,
                                 const char* literal2,
                                 const char* target_literal,
                                 LongNum* (*tested_operation)(const LongNum*, const LongNum*),
                                 unsigned int testcase_num);


int test_long_addition(void);


int test_long_subtraction(void);


int test_long_multiplication(void);


int test_long_division(void);


int test_long_modulo(void);


int full_long_arithmetic_test_set(void);



#endif //MY_CLIB_TEST_LONG_ARITHMETIC_H
