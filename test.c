//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#include "tests/test_bs_tree.h"

// CHECK THAT YOU USE THE DEBUG CONFIGURATION BEFORE RUNNING THESE TESTS!
// Since assert() statements do nothing in release configuration, these tests will always pass in this case.
int main() {
    if (!DEBUG_CONF) {
        printf("Error: it is not the debug configuration, tests will have no effect.\n");
        return -1;
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

    return 0;
}

