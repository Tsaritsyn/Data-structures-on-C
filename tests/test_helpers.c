//
// Created by Mikhail Tsaritsyn on 20.10.2021.
//

#include "test_helpers.h"

#define print_validation_error(type, target_value, value) \
printf("Check %u failed: expected ", cur_check);          \
print_##type(target_value);                               \
printf(", got ");                                         \
print_##type(value);                                      \
printf("\n");                                             \

#define implement_numeric_value_validation(type) \
int validate_##type##_value(type value, type target_value, unsigned int cur_check) { \
    if (value == target_value)                   \
        return 1;                                \
    else {                                       \
        print_validation_error(type, target_value, value)                            \
        return 0;                                \
    }                                            \
}

implement_numeric_value_validation(int)
implement_numeric_value_validation(short)
implement_numeric_value_validation(char)
implement_numeric_value_validation(long)
implement_numeric_value_validation(float)
implement_numeric_value_validation(double)
implement_numeric_value_validation(u_int)
implement_numeric_value_validation(u_short)
implement_numeric_value_validation(u_char)
implement_numeric_value_validation(u_long)


#define implement_array_validation(type) \
int validate_array_##type(const array_##type* arr, const array_##type* target_arr, unsigned int cur_check) { \
    if (arr->length != target_arr->length) {                                                                         \
        print_validation_error(u_long, target_arr->length, arr->length)                                              \
        return 0;                        \
    }                                    \
                                         \
    unsigned long i;                     \
    for (i = 0; i < arr->length; i++) {  \
        if (arr->elements[i] != target_arr->elements[i]) {                                                           \
            print_validation_error(type, target_arr->elements[i], arr->elements[i])                          \
            printf("Index of incorrect element: %lu\n", i);                                                  \
            return 0;                    \
        }                                \
    }                                    \
                                         \
    return 1;                            \
}

implement_array_validation(int)
implement_array_validation(short)
implement_array_validation(char)
implement_array_validation(long)
implement_array_validation(float)
implement_array_validation(double)
implement_array_validation(u_int)
implement_array_validation(u_short)
implement_array_validation(u_char)
implement_array_validation(u_long)


void print_test_series_start_message(const char* test_series_name) {
    char* upper_name = strupr(test_series_name);
    printf("\nTEST SERIES FOR %s STARTED.\n", upper_name);
    free(upper_name);
}


int validate_test_series(const char* test_series_name, unsigned int tests_total, unsigned int tests_passed) {
    int passed = (tests_passed == tests_total);
    char* upper_name = strupr(test_series_name);
    printf("%s TEST SERIES %s.\n", upper_name, (passed) ? "PASSED" : "FAILED");
    free(upper_name);
    return passed;
}


void print_test_start_message(const char* test_name) {
    printf("%c%s test started.\n", toupper(test_name[0]), test_name + 1);
}


int validate_test(const char *test_name, unsigned int checks_total, unsigned int checks_passed) {
    if (checks_passed == checks_total) {
        printf("%c%s test passed.\n", toupper(test_name[0]), test_name + 1);
        return 1;
    }
    else if (checks_passed > checks_total) {
        printf("Incorrect count of tests: passed %u tests out of %u.\n", checks_passed, checks_total);
        return 0;
    }
    else {
        printf("%c%s test failed (%u/%u checks passed).\n", toupper(test_name[0]), test_name + 1, checks_passed, checks_total);
        return 0;
    }
}