//
// Created by Mikhail Tsaritsyn on 20.10.2021.
//

#include "test_helpers.h"


int validate_u_long_value(unsigned long value, unsigned long target_value, unsigned int cur_check) {
    if (value == target_value)
        return 1;
    else {
        printf("Check %u failed: expected %ld, got %ld\n", cur_check, target_value, value);
        return 0;
    }
}


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
    else {
        printf("%c%s test failed (%u/%u checks passed).\n", toupper(test_name[0]), test_name + 1, checks_passed, checks_total);
        return 0;
    }
}