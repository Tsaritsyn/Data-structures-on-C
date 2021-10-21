//
// Created by Mikhail Tsaritsyn on 21.10.2021.
//

#include "test_subsequence_search.h"


#define implement_test_case_validation(type) \
int validate_array_##type##_test_case(const array_##type* arr1, const array_##type* arr2, const array_##type* target_array, unsigned int testcase_num) { \
    array_##type##_ptr result = greatest_common_##type##_subsequence(arr1, arr2);                                                                             \
    int passed = validate_array_##type(result, target_array, testcase_num);                                                                        \
    delete_array_##type(result);                   \
    return passed;                                 \
}

implement_test_case_validation(int)
implement_test_case_validation(short)
implement_test_case_validation(char)
implement_test_case_validation(long)
implement_test_case_validation(float)
implement_test_case_validation(double)
implement_test_case_validation(u_int)
implement_test_case_validation(u_short)
implement_test_case_validation(u_char)
implement_test_case_validation(u_long)


int test_empty_arrays(void) {
    const int c_array[] = {0, 1, 2, 3};
    const array_int* empty_target_array = new_empty_array_int(0);
    unsigned int checks_total = 0, checks_passed = 0;

    array_int_ptr arr1 = new_empty_array_int(0);
    array_int_ptr arr2 = new_empty_array_int(0);
    checks_passed += validate_array_int_test_case(arr1, arr2, empty_target_array, checks_total++);
    delete_array_int(arr1);
    delete_array_int(arr2);

    arr1 = new_empty_array_int(0);
    arr2 = new_array_int(c_array, sizeof(c_array) / sizeof(int));
    checks_passed += validate_array_int_test_case(arr1, arr2, empty_target_array, checks_total++);
    delete_array_int(arr1);
    delete_array_int(arr2);

    arr1 = new_array_int(c_array, sizeof(c_array) / sizeof(int));
    arr2 = new_empty_array_int(0);
    checks_passed += validate_array_int_test_case(arr1, arr2, empty_target_array, checks_total++);
    delete_array_int(arr1);
    delete_array_int(arr2);

    return validate_test("empty array subsequence", checks_total, checks_passed);
}


int test_for_swapped_arrays(void) {
    const int c_array1[] = {0, 1, 2, 3, 4};
    const int c_array2[] = {1, 3, 5};
    const int c_array3[] = {1, 3};
    const array_int* target_array = new_array_int(c_array3, sizeof(c_array3) / sizeof(int));
    unsigned int checks_total = 0, checks_passed = 0;

    array_int_ptr arr1 = new_array_int(c_array1, sizeof(c_array1) / sizeof(int));
    array_int_ptr arr2 = new_array_int(c_array2, sizeof(c_array2) / sizeof(int));
    checks_passed += validate_array_int_test_case(arr1, arr2, target_array, checks_total++);
    delete_array_int(arr1);
    delete_array_int(arr2);

    arr1 = new_array_int(c_array2, sizeof(c_array2) / sizeof(int));
    arr2 = new_array_int(c_array1, sizeof(c_array1) / sizeof(int));
    checks_passed += validate_array_int_test_case(arr1, arr2, target_array, checks_total++);
    delete_array_int(arr1);
    delete_array_int(arr2);

    return validate_test("subsequence for swapped arrays", checks_total, checks_passed);
}


int test_equal_arrays(void) {
    const int c_array[] = {0, 1, 2, 3, 4};
    const array_int* target_array = new_array_int(c_array, sizeof(c_array) / sizeof(int));
    unsigned int checks_total = 0, checks_passed = 0;

    array_int_ptr arr1 = new_array_int(c_array, sizeof(c_array) / sizeof(int));
    array_int_ptr arr2 = new_array_int(c_array, sizeof(c_array) / sizeof(int));
    checks_passed += validate_array_int_test_case(arr1, arr2, target_array, checks_total++);
    delete_array_int(arr1);
    delete_array_int(arr2);

    return validate_test("subsequence for equal arrays", checks_total, checks_passed);
}


int test_array_with_no_common_elements(void) {
    const int c_array1[] = {0, 2, 4, 6, 8};
    const int c_array2[] = {1, 3, 5, 7};
    const array_int* empty_target_array = new_empty_array_int(0);
    unsigned int checks_total = 0, checks_passed = 0;

    array_int_ptr arr1 = new_array_int(c_array1, sizeof(c_array1) / sizeof(int));
    array_int_ptr arr2 = new_array_int(c_array2, sizeof(c_array2) / sizeof(int));
    checks_passed += validate_array_int_test_case(arr1, arr2, empty_target_array, checks_total++);
    delete_array_int(arr1);
    delete_array_int(arr2);

    const int c_array3[] = {0, 2, 4, 6, 8};
    const int c_array4[] = {-1, -3, -5, -7};
    arr1 = new_array_int(c_array3, sizeof(c_array3) / sizeof(int));
    arr2 = new_array_int(c_array4, sizeof(c_array4) / sizeof(int));
    checks_passed += validate_array_int_test_case(arr1, arr2, empty_target_array, checks_total++);
    delete_array_int(arr1);
    delete_array_int(arr2);

    return validate_test("subsequence for arrays with no common elements", checks_total, checks_passed);
}


int test_correct_arrays(void) {
    const int c_array1[] = {1, 4, 2, 6, 8, 3, 10, -3, -100, 15, -2, 96, 35, 44, -64};
    const int c_array2[] = {3, 4, 6, 28, 37, 10, 15, 41, -20, 96, 66, -34, -78, 44, -322, 278, 34};
    const int c_array3[] = {4, 6, 10, 15, 96, 44};
    const array_int* target_array = new_array_int(c_array3, sizeof(c_array3) / sizeof(int));
    unsigned int checks_total = 0, checks_passed = 0;

    array_int_ptr arr1 = new_array_int(c_array1, sizeof(c_array1) / sizeof(int));
    array_int_ptr arr2 = new_array_int(c_array2, sizeof(c_array2) / sizeof(int));
    checks_passed += validate_array_int_test_case(arr1, arr2, target_array, checks_total++);
    delete_array_int(arr1);
    delete_array_int(arr2);


    const char c_array4[] = {'a', 'b', 'c', 'd', 'e'};
    const char c_array5[] = {'b', ';', 'r', 'd', 'n', 'l', 'e', 'g', '7'};
    const char c_array6[] = {'b', 'd', 'e'};
    const array_char* target_array_c = new_array_char(c_array6, sizeof(c_array6) / sizeof(int));

    array_char_ptr arr3 = new_array_char(c_array4, sizeof(c_array4) / sizeof(int));
    array_char_ptr arr4 = new_array_char(c_array5, sizeof(c_array5) / sizeof(int));
    checks_passed += validate_array_char_test_case(arr3, arr4, target_array_c, checks_total++);
    delete_array_char(arr3);
    delete_array_char(arr4);

    return validate_test("subsequence for swapped arrays", checks_total, checks_passed);
}


int full_gcs_test_set(void) {
    char* test_set_name = "array subsequence";
    print_test_series_start_message(test_set_name);

    unsigned int num_passed = 0, num_total = 0;

    num_passed += test_empty_arrays();
    num_total++;

    num_passed += test_for_swapped_arrays();
    num_total++;

    num_passed += test_equal_arrays();
    num_total++;

    num_passed += test_array_with_no_common_elements();
    num_total++;

    num_passed += test_correct_arrays();
    num_total++;

    return validate_test_series(test_set_name, num_total, num_passed);
}
