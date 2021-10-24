//
// Created by Mikhail Tsaritsyn on 22.10.2021.
//

#include "test_array_sorting.h"


int validate_array_int_sorting_test_case(array_int_ptr arr, const array_int* target_arr, unsigned int testcase_num) {
    ascending_sort_array_int(arr, 0, arr->length);
    return validate_array_int(arr, target_arr, testcase_num);
}


int test_empty_array(void) {
    array_int_ptr empty_target_array = new_empty_array_int(0);
    unsigned int checks_total = 0, checks_passed = 0;

    array_int_ptr arr = new_empty_array_int(0);
    checks_passed += validate_array_int_sorting_test_case(arr, empty_target_array, checks_total++);
    delete_array(arr);
    delete_array(empty_target_array);

    return validate_test("empty array sorting", checks_total, checks_passed);
}


int test_sorted_array(void) {
    unsigned int checks_total = 0, checks_passed = 0;
    const int c_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    array_int_ptr arr = new_array_int(c_array, sizeof(c_array) / sizeof(int));
    checks_passed += validate_array_int_sorting_test_case(arr, arr, checks_total++);
    delete_array(arr);

    return validate_test("sorted array sorting", checks_total, checks_passed);
}


int test_reversely_sorted_array(void) {
    unsigned int checks_total = 0, checks_passed = 0;
    const int c_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const int c_array_reversed[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    array_int* target_array = new_array_int(c_array, sizeof(c_array) / sizeof(int));

    array_int_ptr arr = new_array_int(c_array_reversed, sizeof(c_array_reversed) / sizeof(int));
    checks_passed += validate_array_int_sorting_test_case(arr, target_array, checks_total++);
    delete_array(arr);
    delete_array(target_array);


    return validate_test("reversely sorted array sorting", checks_total, checks_passed);
}


int test_arbitrary_array(void) {
    unsigned int checks_total = 0, checks_passed = 0;
    const int c_array[] = {0, 5, 3, 18, 10, -1, 16, -5, 0, 7};
    const int c_array_target[] = {-5, -1, 0, 0, 3, 5, 7, 10, 16, 18};
    array_int* target_array = new_array_int(c_array_target, sizeof(c_array_target) / sizeof(int));

    array_int_ptr arr = new_array_int(c_array, sizeof(c_array) / sizeof(int));
    checks_passed += validate_array_int_sorting_test_case(arr, target_array, checks_total++);
    delete_array(arr);
    delete_array(target_array);

    return validate_test("arbitrary array sorting", checks_total, checks_passed);
}


int full_sorting_test_set(void) {
    char* test_set_name = "array sorting";
    print_test_series_start_message(test_set_name);

    unsigned int num_passed = 0, num_total = 0;

    num_passed += test_empty_array();
    num_total++;

    num_passed += test_sorted_array();
    num_total++;

    num_passed += test_reversely_sorted_array();
    num_total++;

    num_passed += test_arbitrary_array();
    num_total++;

    return validate_test_series(test_set_name, num_total, num_passed);
}
