//
// Created by Mikhail Tsaritsyn on 29.10.2021.
//

#include "test_long_arithmetic.h"


int validate_long_long_operation(const char* literal1,
                                 const char* literal2,
                                 const char* target_literal,
                                 LongNum* (*tested_operation)(const LongNum*, const LongNum*),
                                 unsigned int testcase_num) {
    LongNum* lnum1 = new_long_num_from_string(literal1);
    LongNum* lnum2 = new_long_num_from_string(literal2);
    LongNum* target = new_long_num_from_string(target_literal);

    LongNum* result = tested_operation(lnum1, lnum2);
    int passed = validate_long_int_value(result, target, testcase_num);

    delete_long_num(lnum1);
    delete_long_num(lnum2);
    delete_long_num(target);
    delete_long_num(result);
    return passed;
}


int test_long_addition(void) {
    unsigned int checks_total = 0, checks_passed = 0;
    void* operation = &add_long_num;
    checks_passed += validate_long_long_operation("0", "1234", "1234", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "0", "1234", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "1234", "2468", operation, checks_total++);
    checks_passed += validate_long_long_operation("-1234", "-1234", "-2468", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "-1234", "0", operation, checks_total++);
    checks_passed += validate_long_long_operation("-1234", "1234", "0", operation, checks_total++);
    checks_passed += validate_long_long_operation("1", "999999999999999999999999999999999999999999999", "1000000000000000000000000000000000000000000000",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation("-1", "-999999999999999999999999999999999999999999999", "-1000000000000000000000000000000000000000000000",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation("-1", "1000000000000000000000000000000000000000000000", "999999999999999999999999999999999999999999999",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation("1", "-1000000000000000000000000000000000000000000000", "-999999999999999999999999999999999999999999999",
                                                  operation, checks_total++);
    return validate_test("long addition", checks_total, checks_passed);
}


int test_long_subtraction(void) {
    unsigned int checks_total = 0, checks_passed = 0;
    void* operation = &sub_long_num;
    checks_passed += validate_long_long_operation("0", "1234", "-1234", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "0", "1234", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "1234", "0", operation, checks_total++);
    checks_passed += validate_long_long_operation("-1234", "-1234", "-0", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "-1234", "2468", operation, checks_total++);
    checks_passed += validate_long_long_operation("-1234", "1234", "-2468", operation, checks_total++);
    checks_passed += validate_long_long_operation("1000000000000000001", "2", "999999999999999999", operation, checks_total++);
    checks_passed += validate_long_long_operation("1", "-999999999999999999999999999999999999999999999", "1000000000000000000000000000000000000000000000",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation("-1", "999999999999999999999999999999999999999999999", "-1000000000000000000000000000000000000000000000",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation("-1", "-1000000000000000000000000000000000000000000000", "999999999999999999999999999999999999999999999",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation("1", "1000000000000000000000000000000000000000000000", "-999999999999999999999999999999999999999999999",
                                                  operation, checks_total++);
    return validate_test("long subtraction", checks_total, checks_passed);
}


int test_long_multiplication(void) {
    unsigned int checks_total = 0, checks_passed = 0;
    void* operation = &mul_long_num;
    checks_passed += validate_long_long_operation("0", "1234", "0", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "0", "0", operation, checks_total++);
    checks_passed += validate_long_long_operation("1", "1234", "1234", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "1", "1234", operation, checks_total++);
    checks_passed += validate_long_long_operation("-1", "1234", "-1234", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "-1", "-1234", operation, checks_total++);
    checks_passed += validate_long_long_operation("1", "-1234", "-1234", operation, checks_total++);
    checks_passed += validate_long_long_operation("-1234", "1", "-1234", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "1234", "1522756", operation, checks_total++);
    checks_passed += validate_long_long_operation("-1234", "-1234", "1522756", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "-1234", "-1522756", operation, checks_total++);
    checks_passed += validate_long_long_operation("-1234", "1234", "-1522756", operation, checks_total++);
    checks_passed += validate_long_long_operation("123456789123456789", "987654321987654321", "121932631356500531347203169112635269",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation("-123456789123456789", "987654321987654321", "-121932631356500531347203169112635269",
                                                  operation, checks_total++);
    return validate_test("long multiplication", checks_total, checks_passed);
}


int test_long_division(void) {
    unsigned int checks_total = 0, checks_passed = 0;
    void* operation = &div_long_num;
    checks_passed += validate_long_long_operation("0", "1234", "0", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "0", "", operation, checks_total++);
    checks_passed += validate_long_long_operation("1", "1234", "0", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "1", "1234", operation, checks_total++);
    checks_passed += validate_long_long_operation("-1", "1234", "-1", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "-1", "-1234", operation, checks_total++);
    checks_passed += validate_long_long_operation("1", "-1234", "-1", operation, checks_total++);
    checks_passed += validate_long_long_operation("-1234", "1", "-1234", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "1234", "1", operation, checks_total++);
    checks_passed += validate_long_long_operation("-1234", "-1234", "1", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "-1234", "-1", operation, checks_total++);
    checks_passed += validate_long_long_operation("-1234", "1234", "-1", operation, checks_total++);
    checks_passed += validate_long_long_operation("121932631356500531347203169112635269", "123456789123456789", "987654321987654321",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation("-121932631356500531347203169112635269", "-123456789123456789", "987654321987654321",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation("121932631356500531347203169222635269", "123456789123456789", "987654321987654321",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation("-121932631356500531347203169222635269", "-123456789123456789", "987654321987654321",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation("121932631356500531347203169222635269", "-123456789123456789", "-987654321987654322",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation("-121932631356500531347203169222635269", "123456789123456789", "-987654321987654322",
                                                  operation, checks_total++);
    return validate_test("long division", checks_total, checks_passed);
}


int test_long_modulo(void) {
    unsigned int checks_total = 0, checks_passed = 0;
    void* operation = &mod_long_num;
    checks_passed += validate_long_long_operation("0", "1234", "0", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "0", "", operation, checks_total++);
    checks_passed += validate_long_long_operation("1", "1234", "1", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "1", "0", operation, checks_total++);
    checks_passed += validate_long_long_operation("-1234", "1", "0", operation, checks_total++);
    checks_passed += validate_long_long_operation("-1", "1234", "1233", operation, checks_total++);
    checks_passed += validate_long_long_operation("-1", "-1234", "-1", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "-1", "0", operation, checks_total++);
    checks_passed += validate_long_long_operation("-1234", "-1", "0", operation, checks_total++);
    checks_passed += validate_long_long_operation("1", "-1234", "-1233", operation, checks_total++);
    checks_passed += validate_long_long_operation("-1234", "1", "0", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "1234", "0", operation, checks_total++);
    checks_passed += validate_long_long_operation("-1234", "-1234", "0", operation, checks_total++);
    checks_passed += validate_long_long_operation("1234", "-1234", "0", operation, checks_total++);
    checks_passed += validate_long_long_operation("-1234", "1234", "0", operation, checks_total++);
    checks_passed += validate_long_long_operation("121932631356500531347203169112635269", "123456789123456789", "0",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation("-121932631356500531347203169112635269", "-123456789123456789", "0",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation("121932631356500531347203169112635269", "-123456789123456789", "0",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation("-121932631356500531347203169112635269", "123456789123456789", "0",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation("121932631356500531347203169222635269", "123456789123456789", "110000000",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation("-121932631356500531347203169222635269", "-123456789123456789", "110000000",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation("121932631356500531347203169222635269", "-123456789123456789", "-123456789013456789",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation("-121932631356500531347203169222635269", "123456789123456789", "123456789013456789",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation( "123456789123456789", "121932631356500531347203169112635269","123456789123456789",
                                                   operation, checks_total++);
    checks_passed += validate_long_long_operation("-123456789123456789", "-121932631356500531347203169112635269", "-123456789123456789",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation( "123456789123456789", "-121932631356500531347203169112635269","-121932631356500531223746379989178480",
                                                   operation, checks_total++);
    checks_passed += validate_long_long_operation("-123456789123456789", "121932631356500531347203169112635269", "121932631356500531223746379989178480",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation( "123456789123456789", "121932631356500531347203169222635269","123456789123456789",
                                                   operation, checks_total++);
    checks_passed += validate_long_long_operation( "-123456789123456789", "-121932631356500531347203169222635269","-123456789123456789",
                                                   operation, checks_total++);
    checks_passed += validate_long_long_operation("-123456789123456789", "121932631356500531347203169222635269", "121932631356500531223746380099178480",
                                                  operation, checks_total++);
    checks_passed += validate_long_long_operation("123456789123456789", "-121932631356500531347203169222635269", "-121932631356500531223746380099178480",
                                                  operation, checks_total++);
    return validate_test("long modulo", checks_total, checks_passed);
}


int full_long_arithmetic_test_set(void) {
    char* test_set_name = "long arithmetics";
    print_test_series_start_message(test_set_name);

    unsigned int num_passed = 0, num_total = 0;

    num_passed += test_long_addition();
    num_total++;

    num_passed += test_long_subtraction();
    num_total++;

    num_passed += test_long_multiplication();
    num_total++;

    num_passed += test_long_division();
    num_total++;

    num_passed += test_long_modulo();
    num_total++;

    return validate_test_series(test_set_name, num_total, num_passed);
}
