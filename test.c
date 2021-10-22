//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#include "tests/data_structures_tests.h"
#include "tests/algorithms_tests.h"


void full_tree_test_set() {
    if (!DEBUG_CONF) {
        printf("Error in full_tree_test_set: it is not the debug configuration, tests will have no effect.\n");
        return;
    }

    print_tree_size();
    test_node_creation();
    test_find_node();
    test_put_value();
    test_tree_from_array();
    test_tree_displaying();
    test_tree_depth_and_size();
    test_tree2array();
    test_copy_tree();
    test_extremal_values_valid();
    test_extremal_values_general();
    test_validity();
    test_equality();
    test_remove();
    test_equivalency();
    test_balancing();
    test_creating_balanced_tree();
    test_merging_balanced_trees();
}


int full_set_testset() {
    unsigned int num_passed = 0, num_total = 0;
    int passed = 1;

    printf("\nTEST SERIES FOR SET CONTAINER STARTED.\n");

    int current_res = test_set_creation();
    num_passed += current_res;
    passed &= current_res;
    num_total++;

    printf("\n%u/%u tests passed.\n", num_passed, num_total);
    printf("SET TEST SERIES %s.\n", (passed == 1) ? "PASSED" : "FAILED");
    return passed;
}


// CHECK THAT YOU USE THE DEBUG CONFIGURATION BEFORE RUNNING THESE TESTS!
// Since assert() statements do nothing in release configuration, these tests will always pass in this case.
int main() {

    full_tree_test_set();
    full_set_testset();

    full_substring_search_testset();
    full_levenstein_distance_test_set();
    full_gcs_test_set();
    full_sorting_test_set();

    return 0;
}

