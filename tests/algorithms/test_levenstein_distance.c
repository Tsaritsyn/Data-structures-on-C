//
// Created by Mikhail Tsaritsyn on 20.10.2021.
//

#include "test_levenstein_distance.h"


int validate_test_case(const char *s1, const char* s2, unsigned long target_value, unsigned int testcase_num) {
    string_ptr str1 = new_string(s1), str2 = new_string(s2);
    unsigned long distance = get_levenstein_distance(str1, str2);
    delete_string(str1);
    delete_string(str2);
    return validate_u_long_value(distance, target_value, testcase_num);
}


int test_empty_string(void) {
    unsigned int checks_total = 0, checks_passed = 0;
    checks_passed += validate_test_case("", "abc", 3, checks_total++);
    checks_passed += validate_test_case("abc", "", 3, checks_total++);
    checks_passed += validate_test_case("", "", 0, checks_total++);
    return validate_test("empty string distance", checks_total, checks_passed);
}


int test_distance_symmetry(void) {
    unsigned int checks_total = 0, checks_passed = 0;
    checks_passed += validate_test_case("abcdef", "bcd", 3, checks_total++);
    checks_passed += validate_test_case("bcd", "abcdef", 3, checks_total++);
    return validate_test("distance symmetry", checks_total, checks_passed);
}


int test_equal_strings(void) {
    unsigned int checks_total = 0, checks_passed = 0;
    checks_passed += validate_test_case("abcdef", "abcdef", 0, checks_total++);
    checks_passed += validate_test_case("a;l34987gb", "a;l34987gb", 0, checks_total++);
    checks_passed += validate_test_case("luytvlyaf;augabr;ugWYEvfLUFEYVLWYUbriubvaeriuH[WO;IB;IUIUB;REIUB;;IUGVYhvLUYV;iyvBYvuv;YVlyvluYV jhvcvkytfvb;iuGVYTCvivullyv;ubguybIPYV;iyv;IUB:IYVBOU{iuvhvb'ougvlhgjvb;iyfvcLUYKV YFGjvbiu;yfvcvkljhkgbo675ed65788yG)F^($Er0t8p7yif96c45&RF)57dci76o8ufd6r9oytuvybo75ufou",
                                        "luytvlyaf;augabr;ugWYEvfLUFEYVLWYUbriubvaeriuH[WO;IB;IUIUB;REIUB;;IUGVYhvLUYV;iyvBYvuv;YVlyvluYV jhvcvkytfvb;iuGVYTCvivullyv;ubguybIPYV;iyv;IUB:IYVBOU{iuvhvb'ougvlhgjvb;iyfvcLUYKV YFGjvbiu;yfvcvkljhkgbo675ed65788yG)F^($Er0t8p7yif96c45&RF)57dci76o8ufd6r9oytuvybo75ufou",
                                        0, checks_total++);
    return validate_test("equal strings", checks_total, checks_passed);
}


int test_arbitrary_strings(void) {
    unsigned int checks_total = 0, checks_passed = 0;
    checks_passed += validate_test_case("moloko", "kolokol", 2, checks_total++);
    checks_passed += validate_test_case("0fagbnmc8de", "8atrbxcd56e.", 10, checks_total++);
    return validate_test("arbitrary strings", checks_total, checks_passed);
}


int full_levenstein_distance_test_set(void) {
    char* test_set_name = "levenstein distance";
    print_test_series_start_message(test_set_name);

    unsigned int num_passed = 0, num_total = 0;

    num_passed += test_empty_string();
    num_total++;

    num_passed += test_distance_symmetry();
    num_total++;

    num_passed += test_equal_strings();
    num_total++;

    num_passed += test_arbitrary_strings();
    num_total++;

    return validate_test_series(test_set_name, num_total, num_passed);
}
