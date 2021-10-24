//
// Created by Mikhail Tsaritsyn on 20.10.2021.
//

#include "test_substring_search.h"


int validate_negative_test_case(const char *s, const char *sub, unsigned int testcase_num) {
    string_ptr str = new_string(s), substr = new_string(sub);
    array_u_long_ptr found_positions = find_substrings(str, substr);
    unsigned long num_substr_found = found_positions->length;
    delete_string(str);
    delete_string(substr);
    delete_array(found_positions);
    return validate_u_long_value(num_substr_found, 0, testcase_num);
}


int validate_positive_test_case(const char *s, const char *sub,
                                unsigned long target_value, unsigned long target_array[],
                                unsigned int testcase_num) {
    string_ptr str = new_string(s), substr = new_string(sub);
    array_u_long_ptr found_positions = find_substrings(str, substr);
    delete_string(str);
    delete_string(substr);

    array_u_long_ptr target_arr = new_array_u_long(target_array, target_value);
    int passed = are_arrays_u_long_equal(found_positions, target_arr);

    delete_array(found_positions);
    delete_array(target_arr);
    return passed;
}


int test_search_on_empty_string(void) {
    unsigned int checks_total = 0, checks_passed = 0;
    checks_passed += validate_negative_test_case("", "abc", checks_total++);
    return validate_test("search in empty string", checks_total, checks_passed);
}


int test_search_of_empty_substring(void) {
    unsigned int checks_total = 0, checks_passed = 0;
    checks_passed += validate_negative_test_case("abc", "", checks_total++);
    return validate_test("search for empty substring", checks_total, checks_passed);
}


int test_search_of_non_existent_substring(void) {
    unsigned int checks_total = 0, checks_passed = 0;

    checks_passed += validate_negative_test_case("abcdefg", "hij", checks_total++);
    checks_passed += validate_negative_test_case("abcdefg", "fgh", checks_total++);
    checks_passed += validate_negative_test_case("abcdefg", "0ab", checks_total++);
    checks_passed += validate_negative_test_case("abcdefg", "edc", checks_total++);

    return validate_test("search for non-existent substring", checks_total, checks_passed);
}


int test_correct_search(void) {
    unsigned int checks_total = 0, checks_passed = 0;
    const char* s = "abacabadabacabafabacabadabacabagabacabadabacabafabacabadabacaba";

    unsigned long target_array[] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62};
    checks_passed += validate_positive_test_case(s, "a", 32, target_array, checks_total++);
    unsigned long target_array1[] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60};
    checks_passed += validate_positive_test_case(s, "ab", 16, target_array1, checks_total++);
    unsigned long target_array2[] = {2, 10, 18, 26, 34, 42, 50, 58};
    checks_passed += validate_positive_test_case(s, "acab", 8, target_array2, checks_total++);
    unsigned long target_array3[] = {30};
    checks_passed += validate_positive_test_case(s, "aga", 1, target_array3, checks_total++);
    unsigned long target_array4[] = {7, 39};
    checks_passed += validate_positive_test_case(s, "dabacabaf", 2, target_array4, checks_total++);

    return validate_test("correct search", checks_total, checks_passed);
}


int full_substring_search_testset(void) {
    char* test_set_name = "substring search";
    print_test_series_start_message(test_set_name);

    unsigned int num_passed = 0, num_total = 0;

    num_passed += test_search_on_empty_string();
    num_total++;

    num_passed += test_search_of_empty_substring();
    num_total++;

    num_passed += test_search_of_non_existent_substring();
    num_total++;

    num_passed += test_correct_search();
    num_total++;

    return validate_test_series(test_set_name, num_total, num_passed);
}
