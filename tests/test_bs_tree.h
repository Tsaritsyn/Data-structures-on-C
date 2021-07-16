//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#ifndef MY_CLIB_TEST_BS_TREE_H
#define MY_CLIB_TEST_BS_TREE_H

#ifndef NDEBUG
const char DEBUG_CONF = 1;
#else
const char DEBUG_CONF = 0;
#endif

#include "stdio.h"
#include "assert.h"
#include "stdlib.h"

#include "../my_clib.h"


const long BIG_ARRAY[] = {1, 4, 18, 573, -2, 573, -3564, 1, -8, 9005, 4, 1463, -8, 1746, -8, 4, 245, 83, -8};
const long ASCENDING_ARRAY[] = {1, 2, 3, 4, 5};
const long DESCENDING_ARRAY[] = {-1, -2, -3, -4, -5};


void print_tree_size(void) {
    printf("Size of the node is %lu bytes.\n", sizeof(Tree));
}


void test_node_creation(void) {
    printf("\nNode creation test started.\n");

    long value = 0;
    Tree_ptr node = new_node(value);
    assert(node != NULL);
    assert(node->left == NULL);
    assert(node->right == NULL);
    assert(node->value == value);
    free(node);
    printf("Subtest 1 passed\n");

    value = 1000;
    node = new_node(value);
    assert(node != NULL);
    assert(node->left == NULL);
    assert(node->right == NULL);
    assert(node->value == value);
    free(node);
    printf("Subtest 2 passed\n");

    value = -10;
    node = new_node(value);
    assert(node != NULL);
    assert(node->left == NULL);
    assert(node->right == NULL);
    assert(node->value == value);
    free(node);
    printf("Subtest 3 passed\n");

    printf("Test passed\n");
}


void test_find_node(void) {
    printf("\nFind node test started.\n");
//    create tree with the following structure:
//        0 -> -1
//          -> 4 -> 2
//               -> 10
    Tree_ptr root = new_node(0);
    root->left = new_node(-1);
    root->right = new_node(4);
    root->right->left = new_node(2);
    root->right->right = new_node(10);

    Tree_ptr parent = NULL, node = NULL;

    printf("Testing search in NULL tree...\n");
    node = find_node(NULL, 1, 0);
    assert(node == NULL);
    node = find_node(NULL, 1, 1, &parent);
    assert(node == NULL);
    assert(parent == NULL);
    printf("Subtest 0 passed.\n");

    printf("Testing without the parent node...\n");
    node = find_node(root, 0, 0);
    assert(node == root);
    printf("Subtest 1 passed.\n");

    node = find_node(root, 4, 0);
    assert(node == root->right);
    printf("Subtest 2 passed.\n");

    node = find_node(root, 10, 0);
    assert(node == root->right->right);
    printf("Subtest 3 passed.\n");

    node = find_node(root, -3, 0);
    assert(node == NULL);
    printf("Subtest 4 passed.\n");

    printf("Testing with the parent node...\n");
    node = find_node(root, 0, 1, &parent);
    assert(node == root);
    assert(parent == NULL);
    printf("Subtest 5 passed.\n");

    node = find_node(root, -1, 1, &parent);
    assert(node == root->left);
    assert(parent == root);
    printf("Subtest 6 passed.\n");

    node = find_node(root, 2, 1, &parent);
    assert(node == root->right->left);
    assert(parent == root->right);
    printf("Subtest 7 passed.\n");

    node = find_node(root, -4, 1, &parent);
    assert(node == NULL);
    assert(parent == root->left);
    printf("Subtest 8 passed.\n");

    node = find_node(root, 1, 1, &parent);
    assert(node == NULL);
    assert(parent == root->right->left);
    printf("Subtest 9 passed.\n");

    node = find_node(root, 20, 1, &parent);
    assert(node == NULL);
    assert(parent == root->right->right);
    printf("Subtest 10 passed.\n");

    printf("Test passed\n");
    delete_tree(root);
}


void test_put_value(void) {
    printf("\nPut value test started.\n");

    int res = tree_insert_value(NULL, 0);
    assert(res == -1);
    printf("Subtest 0 passed.\n");

//    initial tree:
//        0
    Tree_ptr root = new_node(0);

//    modified tree:
//        0 -> NULL
//          -> 2
    res = tree_insert_value(root, 2);
    assert(res == 1);
    assert(root->right != NULL);
    assert(root->left == NULL);
    assert(root->right->value == 2);
    assert(root->right->left == NULL);
    assert(root->right->right == NULL);
    printf("Subtest 1 passed\n");

//    modified tree:
//        0 -> -1
//          -> 2
    res = tree_insert_value(root, -1);
    assert(res == 1);
    assert(root->left != NULL);
    assert(root->left->value == -1);
    assert(root->left->left == NULL);
    assert(root->left->right == NULL);
    printf("Subtest 2 passed\n");

//    modified tree:
//        0 -> -1
//          -> 2 -> 1
//               -> NULL
    res = tree_insert_value(root, 1);
    assert(res == 1);
    assert(root->right->right == NULL);
    assert(root->right->left != NULL);
    assert(root->right->left->value == 1);
    assert(root->right->left->left == NULL);
    assert(root->right->left->right == NULL);
    printf("Subtest 3 passed\n");

//    modified tree:
//        0 -> -1
//          -> 2 -> 1
//               -> 3
    res = tree_insert_value(root, 3);
    assert(res == 1);
    assert(root->right->right != NULL);
    assert(root->right->right->value == 3);
    assert(root->right->right->left == NULL);
    assert(root->right->right->right == NULL);
    printf("Subtest 4 passed\n");

//    check that the tree has not changed
//        0 -> -1
//          -> 2 -> 1
//               -> 3
    res = tree_insert_value(root, 2);
    assert(res == 0);
    assert(root->value == 0);
    assert(root->left != NULL);
    assert(root->right != NULL);
    assert(root->left->value == -1);
    assert(root->right->value == 2);
    assert(root->left->left == NULL);
    assert(root->left->right == NULL);
    assert(root->right->left != NULL);
    assert(root->right->right != NULL);
    assert(root->right->left->value == 1);
    assert(root->right->right->value == 3);
    assert(root->right->left->left == NULL);
    assert(root->right->left->right == NULL);
    assert(root->right->right->left == NULL);
    assert(root->right->right->right == NULL);
    printf("Subtest 5 passed\n");

    //    check that the tree has not changed
//        0 -> -1
//          -> 2 -> 1
//               -> 3
    res = tree_insert_value(root, 3);
    assert(res == 0);
    assert(root->value == 0);
    assert(root->left != NULL);
    assert(root->right != NULL);
    assert(root->left->value == -1);
    assert(root->right->value == 2);
    assert(root->left->left == NULL);
    assert(root->left->right == NULL);
    assert(root->right->left != NULL);
    assert(root->right->right != NULL);
    assert(root->right->left->value == 1);
    assert(root->right->right->value == 3);
    assert(root->right->left->left == NULL);
    assert(root->right->left->right == NULL);
    assert(root->right->right->left == NULL);
    assert(root->right->right->right == NULL);
    printf("Subtest 6 passed\n");

    printf("Test passed\n");
    delete_tree(root);
}


void test_tree_from_array(void) {
    printf("\nTree initialization from array test started.\n");

//    we expect the following tree:
//        1 -> NULL
//          -> 2 -> NULL
//               -> 3 -> NULL
//                    -> 4 -> NULL
//                         -> 5
    Tree_ptr root = new_tree(ASCENDING_ARRAY, 5);
    assert(root != NULL);
    assert(root->value == 1);
    assert(root->right != NULL);
    assert(root->left == NULL);
    assert(root->right->value == 2);
    assert(root->right->right != NULL);
    assert(root->right->left == NULL);
    assert(root->right->right->value == 3);
    assert(root->right->right->right != NULL);
    assert(root->right->right->left == NULL);
    assert(root->right->right->right->value == 4);
    assert(root->right->right->right->right != NULL);
    assert(root->right->right->right->left == NULL);
    assert(root->right->right->right->right->value == 5);
    delete_tree(root);
    printf("Subtest 1 passed.\n");

//    we expect the following tree:
//        -1 -> -2 -> -3 -> -4 -> -5
//                            -> NULL
//                      -> NULL
//                -> NULL
//          -> NULL
    root = new_tree(DESCENDING_ARRAY, 5);
    assert(root != NULL);
    assert(root->value == -1);
    assert(root->left != NULL);
    assert(root->right == NULL);
    assert(root->left->value == -2);
    assert(root->left->left != NULL);
    assert(root->left->right == NULL);
    assert(root->left->left->value == -3);
    assert(root->left->left->left != NULL);
    assert(root->left->left->right == NULL);
    assert(root->left->left->left->value == -4);
    assert(root->left->left->left->left != NULL);
    assert(root->left->left->left->right == NULL);
    assert(root->left->left->left->left->value == -5);
    delete_tree(root);
    printf("Subtest 2 passed.\n");

//    we expect the following tree:
//        1 -> -2 -> -3564 -> NULL
//                         -> -8 (leaf)
//                -> NULL
//          -> 4 -> NULL
//               -> 18 -> NULL
//                     -> 573 -> 245 -> 83 (leaf)
//                                   -> NULL
//                            -> 9005 -> 1463 -> NULL
//                                            -> 1746 (leaf)
//                                    -> NULL
    root = new_tree(BIG_ARRAY, sizeof(BIG_ARRAY) / sizeof(long));
    assert(root != NULL);
    assert(root->value == 1);
//    check that left subtree of 1 starts from -2
    assert(root->left != NULL);
    assert(root->left->value == -2);
//    check that left subtree of -2 starts with -3564
    assert(root->left->left != NULL);
    assert(root->left->left->value == -3564);
//    check empty left subtree of -3564
    assert(root->left->left->left == NULL);
//    check that right subtree of -3564 starts with -8
    assert(root->left->left->right != NULL);
    assert(root->left->left->right->value == -8);
//    check that -8 is a leaf
    assert(root->left->left->right->left == NULL);
    assert(root->left->left->right->left == NULL);
//    check that right subtree of -2 is empty
    assert(root->left->right == NULL);
//    check that right subtree of 1 starts with 4
    assert(root->right != NULL);
    assert(root->right->value == 4);
//    check that left subtree of 4 is empty
    assert(root->right->left == NULL);
//    check that right subtree of 4 starts with 18
    assert(root->right->right != NULL);
    assert(root->right->right->value == 18);
//    check that left subtree of 18 is empty
    assert(root->right->right->left == NULL);
//    check that right subtree of 18 starts with 573
    assert(root->right->right->right != NULL);
    assert(root->right->right->right->value == 573);
//    check that left subtree of 573 starts with 245
    assert(root->right->right->right->left != NULL);
    assert(root->right->right->right->left->value == 245);
//    check that left subtree of 245 starts with 83
    assert(root->right->right->right->left->left != NULL);
    assert(root->right->right->right->left->left->value == 83);
//    check that 83 is a leaf
    assert(root->right->right->right->left->left->left == NULL);
    assert(root->right->right->right->left->left->right == NULL);
//    check that right subtree of 85 is empty
    assert(root->right->right->right->left->right == NULL);
//    check that right subtree of 573 starts with 9005
    assert(root->right->right->right->right != NULL);
    assert(root->right->right->right->right->value == 9005);
//    check that left subtree of 9005 starts with 1463
    assert(root->right->right->right->right->left != NULL);
    assert(root->right->right->right->right->left->value == 1463);
//    check that left subtree of 1463 is empty
    assert(root->right->right->right->right->left->left == NULL);
//    check that right subtree of 1463 starts with 1746
    assert(root->right->right->right->right->left->right != NULL);
    assert(root->right->right->right->right->left->right->value == 1746);
//    check that 1746 is a leaf
    assert(root->right->right->right->right->left->right->left == NULL);
    assert(root->right->right->right->right->left->right->right == NULL);
//    check that right subtree of 9005 is empty
    assert(root->right->right->right->right->right == NULL);
    delete_tree(root);
    printf("Subtest 3 passed.\n");

    printf("Test passed.\n");
}


void test_tree_displaying(void) {
    printf("\nTree displaying demonstration started.\n");

//    we expect the following tree:
//        1 -> -2 -> -3564 -> NULL
//                         -> -8 (leaf)
//                -> NULL
//          -> 4 -> NULL
//               -> 18 -> NULL
//                     -> 573 -> 245 -> 83 (leaf)
//                                   -> NULL
//                            -> 9005 -> 1463 -> NULL
//                                            -> 1746 (leaf)
//                                    -> NULL
    Tree_ptr root = new_tree(BIG_ARRAY, sizeof(BIG_ARRAY) / sizeof(long));
    printf("Printing the stored values in the ascending order:\n");
    print_tree(root);
    printf("\n");

    printf("Draw the tree using indentations:\n");
    draw_tree(root);

    delete_tree(root);
    printf("Demonstration ended\n");
}


void test_tree_depth_and_size(void) {
    printf("\nTree depth and size test started.\n");

//    we expect the following tree:
//        1 -> NULL
//          -> 2 -> NULL
//               -> 3 -> NULL
//                    -> 4 -> NULL
//                         -> 5
    Tree_ptr root = new_tree(ASCENDING_ARRAY, 5);
    assert(tree_depth(root) == 5);
    assert(tree_size(root) == 5);
    delete_tree(root);
    printf("Subtest 1 passed.\n");

//    we expect the following tree:
//        -1 -> -2 -> -3 -> -4 -> -5
//                             -> NULL
//                       -> NULL
//                 -> NULL
//           -> NULL
    root = new_tree(DESCENDING_ARRAY, 5);
    assert(tree_depth(root) == 5);
    assert(tree_size(root) == 5);
    delete_tree(root);
    printf("Subtest 2 passed.\n");

//    we expect the following tree:
//        1 -> -2 -> -3564 -> NULL
//                         -> -8 (leaf)
//                -> NULL
//          -> 4 -> NULL
//               -> 18 -> NULL
//                     -> 573 -> 245 -> 83 (leaf)
//                                   -> NULL
//                            -> 9005 -> 1463 -> NULL
//                                            -> 1746 (leaf)
//                                    -> NULL
    root = new_tree(BIG_ARRAY, sizeof(BIG_ARRAY) / sizeof(long));
    assert(tree_depth(root) == 7);
    assert(tree_size(root) == 12);
    delete_tree(root);
    printf("Subtest 3 passed.\n");

    printf("Test passed.\n");
}


void test_tree2array(void) {
    printf("\nTest tree to array conversion started.\n");

//    we expect the following tree:
//        1 -> NULL
//          -> 2 -> NULL
//               -> 3 -> NULL
//                    -> 4 -> NULL
//                         -> 5
    Tree_ptr root = new_tree(ASCENDING_ARRAY, 5);
    long *res = tree_to_array(root);
    int i;
    for (i = 0; i < 5; i++)
        assert(res[i] == ASCENDING_ARRAY[i]);
    delete_tree(root);
    free(res);
    printf("Subtest 1 passed.\n");

    //    we expect the following tree:
//        -1 -> -2 -> -3 -> -4 -> -5
//                            -> NULL
//                      -> NULL
//                -> NULL
//          -> NULL
    root = new_tree(DESCENDING_ARRAY, 5);
    res = tree_to_array(root);
    for (i = 0; i < 5; i++)
        assert(res[i] == DESCENDING_ARRAY[4-i]);
    free(res);
    delete_tree(root);
    printf("Subtest 2 passed.\n");

//    we expect the following tree:
//        1 -> -2 -> -3564 -> NULL
//                         -> -8 (leaf)
//                -> NULL
//          -> 4 -> NULL
//               -> 18 -> NULL
//                     -> 573 -> 245 -> 83 (leaf)
//                                   -> NULL
//                            -> 9005 -> 1463 -> NULL
//                                            -> 1746 (leaf)
//                                    -> NULL
    root = new_tree(BIG_ARRAY, sizeof(BIG_ARRAY) / sizeof(long));
    long valid[] = {-3564, -8, -2, 1, 4, 18, 83, 245, 573, 1463, 1746, 9005};
    res = tree_to_array(root);
    for (i = 0; i < tree_size(root); i++)
        assert(res[i] == valid[i]);
    free(res);
    delete_tree(root);
    printf("Subtest 3 passed.\n");

    printf("Test passed.\n");
}


void test_copy_tree() {
    printf("\nTree copying test started.\n");

    Tree_ptr root = new_node(10);
    Tree_ptr root_copy = copy_tree(root);
    assert(root_copy != NULL);
    assert(root_copy->left == NULL);
    assert(root_copy->right == NULL);
    assert(root_copy->value == 10);
    delete_tree(root);
    delete_tree(root_copy);
    printf("Subtest 1 passed\n");

    root_copy = copy_tree(NULL);
    assert(root_copy == NULL);
    printf("Subtest 2 passed\n");

//    we expect the following tree:
//        1 -> NULL
//          -> 2 -> NULL
//               -> 3 -> NULL
//                    -> 4 -> NULL
//                         -> 5
    root = new_tree(ASCENDING_ARRAY, 5);
    root_copy = copy_tree(root);
    assert(root_copy != NULL);
    assert(root_copy->value == 1);
    assert(root_copy->right != NULL);
    assert(root_copy->left == NULL);
    assert(root_copy->right->value == 2);
    assert(root_copy->right->right != NULL);
    assert(root_copy->right->left == NULL);
    assert(root_copy->right->right->value == 3);
    assert(root_copy->right->right->right != NULL);
    assert(root_copy->right->right->left == NULL);
    assert(root_copy->right->right->right->value == 4);
    assert(root_copy->right->right->right->right != NULL);
    assert(root_copy->right->right->right->left == NULL);
    assert(root_copy->right->right->right->right->value == 5);
    delete_tree(root);
    delete_tree(root_copy);
    printf("Subtest 3 passed.\n");

//    we expect the following tree:
//        1 -> -2 -> -3564 -> NULL
//                         -> -8 (leaf)
//                -> NULL
//          -> 4 -> NULL
//               -> 18 -> NULL
//                     -> 573 -> 245 -> 83 (leaf)
//                                   -> NULL
//                            -> 9005 -> 1463 -> NULL
//                                            -> 1746 (leaf)
//                                    -> NULL
    root = new_tree(BIG_ARRAY, sizeof(BIG_ARRAY) / sizeof(long));
    root_copy = copy_tree(root);
    assert(root_copy != NULL);
    assert(root_copy->value == 1);
//    check that left subtree of 1 starts from -2
    assert(root_copy->left != NULL);
    assert(root_copy->left->value == -2);
//    check that left subtree of -2 starts with -3564
    assert(root_copy->left->left != NULL);
    assert(root_copy->left->left->value == -3564);
//    check empty left subtree of -3564
    assert(root_copy->left->left->left == NULL);
//    check that right subtree of -3564 starts with -8
    assert(root_copy->left->left->right != NULL);
    assert(root_copy->left->left->right->value == -8);
//    check that -8 is a leaf
    assert(root_copy->left->left->right->left == NULL);
    assert(root_copy->left->left->right->left == NULL);
//    check that right subtree of -2 is empty
    assert(root_copy->left->right == NULL);
//    check that right subtree of 1 starts with 4
    assert(root_copy->right != NULL);
    assert(root_copy->right->value == 4);
//    check that left subtree of 4 is empty
    assert(root_copy->right->left == NULL);
//    check that right subtree of 4 starts with 18
    assert(root_copy->right->right != NULL);
    assert(root_copy->right->right->value == 18);
//    check that left subtree of 18 is empty
    assert(root_copy->right->right->left == NULL);
//    check that right subtree of 18 starts with 573
    assert(root_copy->right->right->right != NULL);
    assert(root_copy->right->right->right->value == 573);
//    check that left subtree of 573 starts with 245
    assert(root_copy->right->right->right->left != NULL);
    assert(root_copy->right->right->right->left->value == 245);
//    check that left subtree of 245 starts with 83
    assert(root_copy->right->right->right->left->left != NULL);
    assert(root_copy->right->right->right->left->left->value == 83);
//    check that 83 is a leaf
    assert(root_copy->right->right->right->left->left->left == NULL);
    assert(root_copy->right->right->right->left->left->right == NULL);
//    check that right subtree of 85 is empty
    assert(root_copy->right->right->right->left->right == NULL);
//    check that right subtree of 573 starts with 9005
    assert(root_copy->right->right->right->right != NULL);
    assert(root_copy->right->right->right->right->value == 9005);
//    check that left subtree of 9005 starts with 1463
    assert(root_copy->right->right->right->right->left != NULL);
    assert(root_copy->right->right->right->right->left->value == 1463);
//    check that left subtree of 1463 is empty
    assert(root_copy->right->right->right->right->left->left == NULL);
//    check that right subtree of 1463 starts with 1746
    assert(root_copy->right->right->right->right->left->right != NULL);
    assert(root_copy->right->right->right->right->left->right->value == 1746);
//    check that 1746 is a leaf
    assert(root_copy->right->right->right->right->left->right->left == NULL);
    assert(root_copy->right->right->right->right->left->right->right == NULL);
//    check that right subtree of 9005 is empty
    assert(root_copy->right->right->right->right->right == NULL);
    delete_tree(root);
    delete_tree(root_copy);
    printf("Subtest 4 passed.\n");
}


void test_extremal_values_valid(void) {
    printf("\nFinding extremal values in valid trees test started.\n");

    Tree_ptr max_node = max_node_valid(NULL), min_node = min_node_valid(NULL);
    assert(min_node == NULL);
    assert(max_node == NULL);
    printf("Subtest 1 passed.\n");

    Tree_ptr root = new_node(1);
    max_node = max_node_valid(root), min_node = min_node_valid(root);
    assert(max_node == root);
    assert(min_node == root);
    delete_tree(root);
    printf("Subtest 2 passed.\n");

//    we expect the following tree:
//        1 -> NULL
//          -> 2 -> NULL
//               -> 3 -> NULL
//                    -> 4 -> NULL
//                         -> 5
    root = new_tree(ASCENDING_ARRAY, 5);
    max_node = max_node_valid(root), min_node = min_node_valid(root);
    assert(max_node != NULL);
    assert(min_node != NULL);
    assert(max_node->value == 5);
    assert(min_node->value == 1);
    delete_tree(root);
    printf("Subtest 3 passed.\n");

    //    we expect the following tree:
//        -1 -> -2 -> -3 -> -4 -> -5
//                            -> NULL
//                      -> NULL
//                -> NULL
//          -> NULL
    root = new_tree(DESCENDING_ARRAY, 5);
    max_node = max_node_valid(root), min_node = min_node_valid(root);
    assert(max_node != NULL);
    assert(min_node != NULL);
    assert(max_node->value == -1);
    assert(min_node->value == -5);
    delete_tree(root);
    printf("Subtest 4 passed.\n");

//    we expect the following tree:
//        1 -> -2 -> -3564 -> NULL
//                         -> -8 (leaf)
//                -> NULL
//          -> 4 -> NULL
//               -> 18 -> NULL
//                     -> 573 -> 245 -> 83 (leaf)
//                                   -> NULL
//                            -> 9005 -> 1463 -> NULL
//                                            -> 1746 (leaf)
//                                    -> NULL
    root = new_tree(BIG_ARRAY, sizeof(BIG_ARRAY) / sizeof(long));
    max_node = max_node_valid(root), min_node = min_node_valid(root);
    assert(max_node != NULL);
    assert(min_node != NULL);
    assert(max_node->value == 9005);
    assert(min_node->value == -3564);
    delete_tree(root);
    printf("Subtest 5 passed.\n");

    printf("Test passed.\n");
}


void test_extremal_values_general(void) {
    printf("\nFinding extremal values in general trees test started.\n");

    printf("Testing special cases and valid trees...\n");

    Tree_ptr max_node = max_node_general(NULL), min_node = min_node_general(NULL);
    assert(min_node == NULL);
    assert(max_node == NULL);
    printf("Subtest 1 passed.\n");

    Tree_ptr root = new_node(1);
    max_node = max_node_general(root), min_node = min_node_general(root);
    assert(max_node == root);
    assert(min_node == root);
    delete_tree(root);
    printf("Subtest 2 passed.\n");

//    we expect the following tree:
//        1 -> -2 -> -3564 -> NULL
//                         -> -8 (leaf)
//                -> NULL
//          -> 4 -> NULL
//               -> 18 -> NULL
//                     -> 573 -> 245 -> 83 (leaf)
//                                   -> NULL
//                            -> 9005 -> 1463 -> NULL
//                                            -> 1746 (leaf)
//                                    -> NULL
    root = new_tree(BIG_ARRAY, sizeof(BIG_ARRAY) / sizeof(long));
    max_node = max_node_general(root), min_node = min_node_general(root);
    assert(max_node != NULL);
    assert(min_node != NULL);
    assert(max_node->value == 9005);
    assert(min_node->value == -3564);
    delete_tree(root);
    printf("Subtest 3 passed.\n");

    printf("Testing non-valid trees...\n");
    root = new_node(0);
    root->right = new_node(-1);
    root->left = new_node(1);
    max_node = max_node_general(root), min_node = min_node_general(root);
    assert(max_node != NULL);
    assert(min_node != NULL);
    assert(max_node->value == 1);
    assert(min_node->value == -1);
    printf("Subtest 4 passed.\n");

    root->right->right = new_node(2);
    max_node = max_node_general(root), min_node = min_node_general(root);
    assert(max_node != NULL);
    assert(min_node != NULL);
    assert(max_node->value == 2);
    assert(min_node->value == -1);
    printf("Subtest 5 passed.\n");

    root->right->left = new_node(-2);
    root->left->left = new_node(-2);
    max_node = max_node_general(root), min_node = min_node_general(root);
    assert(max_node != NULL);
    assert(min_node != NULL);
    assert(max_node->value == 2);
    assert(min_node->value == -2);
    printf("Subtest 6 passed.\n");

    delete_tree(root);
    printf("Test passed.\n");
}


void test_validity(void) {
    printf("\nValidity test started.\n");

    assert(tree_valid(NULL) == 1);
    printf("Subtest 1 passed.\n");

    Tree_ptr root = new_node(0);
    assert(tree_valid(root) == 1);
    delete_tree(root);
    printf("Subtest 2 passed.\n");

    root = new_node(1);
    root->left = new_node(0);
    assert(tree_valid(root) == 1);
    printf("Subtest 3 passed.\n");

    root->right = new_node(2);
    assert(tree_valid(root) == 1);
    printf("Subtest 4 passed.\n");

    root->left->left = new_node(-1);
    assert(tree_valid(root) == 1);
    printf("Subtest 5 passed.\n");

    root->right->left = new_node(-2);
    assert(tree_valid(root) == 0);
    delete_tree(root);
    printf("Subtest 6 passed.\n");

    root = new_node(0);
    root->left = new_node(-1);
    root->right = new_node(1);
    root->right->left = new_node(-1);
    assert(tree_valid(root) == 0);
    delete_tree(root);
    printf("Subtest 7 passed.\n");

    root = new_node(0);
    root->left = new_node(1);
    root->right = new_node(2);
    assert(tree_valid(root) == 0);
    delete_tree(root);
    printf("Subtest 8 passed.\n");

    root = new_node(0);
    root->left = new_node(0);
    root->right = new_node(2);
    assert(tree_valid(root) == 0);
    delete_tree(root);
    printf("Subtest 9 passed.\n");

    root = new_node(0);
    root->left = new_node(-1);
    root->right = new_node(0);
    assert(tree_valid(root) == 0);
    delete_tree(root);
    printf("Subtest 10 passed.\n");

    root = new_node(0);
    root->left = new_node(-1);
    root->right = new_node(10);
    root->right->left = new_node(15);
    assert(tree_valid(root) == 0);
    delete_tree(root);
    printf("Subtest 11 passed.\n");

    root = new_node(0);
    root->left = new_node(-5);
    root->right = new_node(1);
    root->left->right = new_node(-6);
    assert(tree_valid(root) == 0);
    delete_tree(root);
    printf("Subtest 12 passed.\n");

    root = new_node(0);
    root->left = new_node(-5);
    root->right = new_node(1);
    root->left->right = new_node(2);
    assert(tree_valid(root) == 0);
    delete_tree(root);
    printf("Subtest 13 passed.\n");

    root = new_node(0);
    root->left = new_node(-5);
    root->right = new_node(1);
    root->left->right = new_node(0);
    assert(tree_valid(root) == 0);
    delete_tree(root);
    printf("Subtest 14 passed.\n");

    printf("Test passed\n");
}


void test_equality(void) {
    printf("\nEquality test started.\n");

    assert(trees_equal(NULL, NULL) == 1);
    printf("Subtest 1 passed.\n");

    Tree_ptr root = new_node(1);
    assert(trees_equal(root, NULL) == 0);
    assert(trees_equal(NULL, root) == 0);
    delete_tree(root);
    printf("Subtest 2 passed.\n");

    long array2[] = {1, 2, 3, 4, -5};
    long array3[] = {1, 2, 3, -4, 5};
    long array4[] = {-1, 2, 3, 4, 5};
    long array5[] = {1, 2, 3, 4, 5, 6};
    long array6[] = {5, 4, 3, 2, 1};
    long array7[] = {-5, -4, -3, -2, -1};

    Tree_ptr root1 = new_tree(ASCENDING_ARRAY, 5);
    Tree_ptr root2 = new_tree(ASCENDING_ARRAY, 5);
    assert(trees_equal(root1, root2) == 1);
    assert(trees_equal(root2, root1) == 1);
    delete_tree(root2);
    printf("Subtest 3 passed.\n");

    root2 = new_tree(array2, 5);
    assert(trees_equal(root1, root2) == 0);
    assert(trees_equal(root2, root1) == 0);
    delete_tree(root2);
    printf("Subtest 4 passed.\n");

    root2 = new_tree(array3, 5);
    assert(trees_equal(root1, root2) == 0);
    assert(trees_equal(root2, root1) == 0);
    delete_tree(root2);
    printf("Subtest 5 passed.\n");

    root2 = new_tree(array4, 5);
    assert(trees_equal(root1, root2) == 0);
    assert(trees_equal(root2, root1) == 0);
    delete_tree(root2);
    printf("Subtest 5 passed.\n");

    root2 = new_tree(array5, 6);
    assert(trees_equal(root1, root2) == 0);
    assert(trees_equal(root2, root1) == 0);
    delete_tree(root2);
    printf("Subtest 6 passed.\n");

    root2 = new_tree(array6, 5);
    assert(trees_equal(root1, root2) == 0);
    assert(trees_equal(root2, root1) == 0);
    delete_tree(root2);
    printf("Subtest 7 passed.\n");

    root2 = new_tree(array7, 5);
    assert(trees_equal(root1, root2) == 0);
    assert(trees_equal(root2, root1) == 0);
    delete_tree(root2);
    printf("Subtest 8 passed.\n");

    printf("Test passed.\n");
    delete_tree(root1);
}


void test_remove(void) {
    printf("\nRemove value test started.\n");

    printf("Testing removing existing element from simple trees...\n");

    Tree_ptr root = new_tree(ASCENDING_ARRAY, 5);

    Tree_ptr root_copy = copy_tree(root);
    int res = remove_value(root_copy, 1);
    long array1[] = {2, 3, 4, 5};
    Tree_ptr control = new_tree(array1, 4);
    assert(res == 1);
    assert(tree_valid(root_copy) == 1);
    assert(trees_equal(root_copy, control) == 1);
    delete_tree(root_copy);
    delete_tree(control);
    printf("Subtest 1 passed.\n");

    root_copy = copy_tree(root);
    res = remove_value(root_copy, 3);
    assert(res == 1);
    long array2[] = {1, 2, 4, 5};
    control = new_tree(array2, 4);
    assert(tree_valid(root_copy) == 1);
    assert(trees_equal(root_copy, control) == 1);
    delete_tree(root_copy);
    delete_tree(control);
    printf("Subtest 2 passed.\n");

    root_copy = copy_tree(root);
    res = remove_value(root_copy, 5);
    assert(res == 1);
    long array3[] = {1, 2, 3, 4};
    control = new_tree(array3, 4);
    assert(tree_valid(root_copy) == 1);
    assert(trees_equal(root_copy, control) == 1);
    delete_tree(root_copy);
    delete_tree(control);
    printf("Subtest 3 passed.\n");

    delete_tree(root);

    root = new_tree(DESCENDING_ARRAY, 5);

    root_copy = copy_tree(root);
    res = remove_value(root_copy, -1);
    assert(res == 1);
    long array5[] = {-2, -3, -4, -5};
    control = new_tree(array5, 4);
    assert(tree_valid(root_copy) == 1);
    assert(trees_equal(root_copy, control) == 1);
    delete_tree(root_copy);
    delete_tree(control);
    printf("Subtest 4 passed.\n");

    root_copy = copy_tree(root);
    res = remove_value(root_copy, -3);
    assert(res == 1);
    long array6[] = {-1, -2, -4, -5};
    control = new_tree(array6, 4);
    assert(tree_valid(root_copy) == 1);
    assert(trees_equal(root_copy, control) == 1);
    delete_tree(root_copy);
    delete_tree(control);
    printf("Subtest 5 passed.\n");

    root_copy = copy_tree(root);
    res = remove_value(root_copy, -5);
    assert(res == 1);
    long array7[] = {-1, -2, -3, -4};
    control = new_tree(array7, 4);
    assert(tree_valid(root_copy) == 1);
    assert(trees_equal(root_copy, control) == 1);
    delete_tree(root_copy);
    delete_tree(control);
    printf("Subtest 6 passed.\n");

    delete_tree(root);

    printf("Testing special cases...\n");

    root = NULL;
    res = remove_value(root, 1);
    assert(res == 0);
    assert(root == NULL);
    printf("Subtest 7 passed.\n");

    root = new_node(1);
    root_copy = root;
    res = remove_value(root_copy, 1);
    assert(res == 0);
    assert(root == root_copy);
    printf("Subtest 8 passed.\n");

    root_copy = root;
    res = remove_value(root, 2);
    assert(res == 0);
    assert(root == root_copy);
    printf("Subtest 9 passed.\n");

    root_copy = root;
    res = remove_value(root, -1);
    assert(res == 0);
    assert(root == root_copy);
    delete_tree(root);
    printf("Subtest 10 passed.\n");

    printf("Testing removing non-existing element from simple trees...\n");

    root = new_tree(ASCENDING_ARRAY, 5);
    root_copy = copy_tree(root);
    res = remove_value(root_copy, -1);
    assert(res == 0);
    control = new_tree(ASCENDING_ARRAY, 5);
    assert(tree_valid(root_copy) == 1);
    assert(trees_equal(root_copy, control) == 1);
    delete_tree(root_copy);
    printf("Subtest 11 passed.\n");

    root_copy = copy_tree(root);
    res = remove_value(root_copy, 6);
    assert(res == 0);
    assert(tree_valid(root_copy) == 1);
    assert(trees_equal(root_copy, control) == 1);
    delete_tree(root_copy);
    delete_tree(control);
    delete_tree(root);
    printf("Subtest 12 passed.\n");

    printf("Testing complex tree...\n");

    root = new_tree(BIG_ARRAY, sizeof(BIG_ARRAY) / sizeof(long));

    root_copy = copy_tree(root);
    res = remove_value(root_copy, 1);
    assert(res == 1);
    assert(tree_valid(root_copy) == 1);
    long control_array1[] = {-3564, -8, -2, 4, 18, 83, 245, 573, 1463, 1746, 9005};
    long *res_array = tree_to_array(root_copy);
    int i;
    for (i = 0; i < sizeof(control_array1) / sizeof(long); i++) {
        assert(res_array[i] == control_array1[i]);
    }
    delete_tree(root_copy);
    free(res_array);
    printf("Subtest 13 passed.\n");

    root_copy = copy_tree(root);
    res = remove_value(root_copy, 245);
    assert(res == 1);
    assert(tree_valid(root_copy) == 1);
    long control_array2[] = {-3564, -8, -2, 1, 4, 18, 83, 573, 1463, 1746, 9005};
    res_array = tree_to_array(root_copy);
    for (i = 0; i < sizeof(control_array2) / sizeof(long); i++) {
        assert(res_array[i] == control_array2[i]);
    }
    delete_tree(root_copy);
    free(res_array);
    printf("Subtest 14 passed.\n");

    root_copy = copy_tree(root);
    res = remove_value(root_copy, 1746);
    assert(res == 1);
    assert(tree_valid(root_copy) == 1);
    long control_array3[] = {-3564, -8, -2, 1, 4, 18, 83, 245, 573, 1463, 9005};
    res_array = tree_to_array(root_copy);
    for (i = 0; i < sizeof(control_array3) / sizeof(long); i++) {
        assert(res_array[i] == control_array3[i]);
    }
    delete_tree(root_copy);
    free(res_array);
    printf("Subtest 15 passed.\n");


    root_copy = copy_tree(root);
    res = remove_value(root_copy, -3564);
    assert(res == 1);
    assert(tree_valid(root_copy) == 1);
    long control_array4[] = {-8, -2, 1, 4, 18, 83, 245, 573, 1463, 1746, 9005};
    res_array = tree_to_array(root_copy);
    for (i = 0; i < sizeof(control_array4) / sizeof(long); i++) {
        assert(res_array[i] == control_array4[i]);
    }
    delete_tree(root_copy);
    free(res_array);
    printf("Subtest 16 passed.\n");

    root_copy = copy_tree(root);
    res = remove_value(root_copy, 4);
    assert(res == 1);
    assert(tree_valid(root_copy) == 1);
    long control_array5[] = {-3564, -8, -2, 1, 18, 83, 245, 573, 1463, 1746, 9005};
    res_array = tree_to_array(root_copy);
    for (i = 0; i < sizeof(control_array5) / sizeof(long); i++) {
        assert(res_array[i] == control_array5[i]);
    }
    delete_tree(root_copy);
    free(res_array);
    printf("Subtest 17 passed.\n");

//    now we'll delete non-existing elements
    long control_array6[] = {-3564, -8, -2, 1, 4, 18, 83, 245, 573, 1463, 1746, 9005};

    root_copy = copy_tree(root);
    res = remove_value(root_copy, 100);
    assert(res == 0);
    assert(tree_valid(root_copy) == 1);
    res_array = tree_to_array(root_copy);
    for (i = 0; i < sizeof(control_array6) / sizeof(long); i++) {
        assert(res_array[i] == control_array6[i]);
    }
    delete_tree(root_copy);
    free(res_array);
    printf("Subtest 18 passed.\n");

    root_copy = copy_tree(root);
    res = remove_value(root_copy, 10000);
    assert(res == 0);
    assert(tree_valid(root_copy) == 1);
    res_array = tree_to_array(root_copy);
    for (i = 0; i < sizeof(control_array6) / sizeof(long); i++) {
        assert(res_array[i] == control_array6[i]);
    }
    delete_tree(root_copy);
    free(res_array);
    printf("Subtest 19 passed.\n");

    root_copy = copy_tree(root);
    res = remove_value(root_copy, -1000);
    assert(res == 0);
    assert(tree_valid(root_copy) == 1);
    res_array = tree_to_array(root_copy);
    for (i = 0; i < sizeof(control_array6) / sizeof(long); i++) {
        assert(res_array[i] == control_array6[i]);
    }
    delete_tree(root_copy);
    free(res_array);
    printf("Subtest 20 passed.\n");

    root_copy = copy_tree(root);
    res = remove_value(root_copy, -4000);
    assert(res == 0);
    assert(tree_valid(root_copy) == 1);
    res_array = tree_to_array(root_copy);
    for (i = 0; i < sizeof(control_array6) / sizeof(long); i++) {
        assert(res_array[i] == control_array6[i]);
    }
    delete_tree(root_copy);
    free(res_array);
    printf("Subtest 21 passed.\n");

    delete_tree(root);
    printf("Test passed.\n");
}


void test_equivalency(void) {
    printf("\nEquivalency check test started.\n");

    printf("Testing special cases...\n");

    assert(trees_equivalent(NULL, NULL) == 1);
    printf("Subtest 1 passed.\n");

    Tree_ptr root1 = new_node(1);
    Tree_ptr root2 = new_node(1);
    assert(trees_equivalent(root1, root2) == 1);
    assert(trees_equivalent(root2, root1) == 1);
    delete_tree(root2);
    printf("Subtest 2 passed.\n");

    root2 = new_node(2);
    assert(trees_equivalent(root1, root2) == 0);
    assert(trees_equivalent(root2, root1) == 0);
    delete_tree(root2);
    printf("Subtest 3 passed.\n");

    delete_tree(root1);

    printf("Testing simple trees...\n");

    root1 = new_tree(ASCENDING_ARRAY, 5);
    assert(trees_equivalent(root1, NULL) == 0);
    assert(trees_equivalent(NULL, root1) == 0);
    printf("Subtest 4 passed.\n");

    long array2[] = {5, 4, 3, 2, 1};
    root2 = new_tree(array2, 5);
    assert(trees_equivalent(root1, root2) == 1);
    assert(trees_equivalent(root2, root1) == 1);
    delete_tree(root2);
    printf("Subtest 5 passed.\n");

    long array3[] = {2, 4, 3, 1, 5};
    root2 = new_tree(array3, 5);
    assert(trees_equivalent(root1, root2) == 0);
    assert(trees_equivalent(root2, root1) == 0);
    delete_tree(root2);
    printf("Subtest 6 passed.\n");

    long array4[] = {-1, 2, 3, 4, 5};
    root2 = new_tree(array4, 5);
    assert(trees_equivalent(root1, root2) == 0);
    assert(trees_equivalent(root2, root1) == 0);
    delete_tree(root2);
    delete_tree(root1);
    printf("Subtest 5 passed.\n");

    printf("Testing complex trees...\n");

    root1 = new_tree(BIG_ARRAY, sizeof(BIG_ARRAY) / sizeof(long));

    long big_array1[] = {1, 4, 18, 573, -2, -3564, -8, 9005, 1463, -8, 1746, 245, 83};
    root2 = new_tree(big_array1, sizeof(big_array1) / sizeof(long));
    assert(trees_equivalent(root1, root2) == 1);
    assert(trees_equivalent(root2, root1) == 1);
    delete_tree(root2);
    printf("Subtest 6 passed.\n");

    long big_array2[] = {573, 18, 4, 1, -2, -3564, -8, 9005, 1463, -8, 1746, 245, 83};
    root2 = new_tree(big_array2, sizeof(big_array2) / sizeof(long));
    assert(trees_equivalent(root1, root2) == 1);
    assert(trees_equivalent(root2, root1) == 1);
    delete_tree(root2);
    printf("Subtest 7 passed.\n");

    long big_array3[] = {4, 1, 18, 573, -2, -3564, -8, 9005, 1463, -8, 1746, 245, 83};
    root2 = new_tree(big_array3, sizeof(big_array3) / sizeof(long));
    assert(trees_equivalent(root1, root2) == 0);
    assert(trees_equivalent(root2, root1) == 0);
    delete_tree(root2);
    printf("Subtest 8 passed.\n");

    long big_array4[] = {1, 4, 18, 573, 3, -2, -3564, -8, 9005, 1463, -8, 1746, 245, 83};
    root2 = new_tree(big_array4, sizeof(big_array4) / sizeof(long));
    assert(trees_equivalent(root1, root2) == 0);
    assert(trees_equivalent(root2, root1) == 0);
    delete_tree(root2);
    printf("Subtest 9 passed.\n");

    long big_array5[] = {1, 4, 18, 573, -3564, -8, 9005, 1463, -8, 1746, 245, 83};
    root2 = new_tree(big_array5, sizeof(big_array5) / sizeof(long));
    assert(trees_equivalent(root1, root2) == 0);
    assert(trees_equivalent(root2, root1) == 0);
    delete_tree(root2);
    printf("Subtest 10 passed.\n");

    long big_array6[] = {1, 3, 18, 573, -2, -3564, -8, 9005, 1463, -8, 1746, 245, 83};
    root2 = new_tree(big_array6, sizeof(big_array6) / sizeof(long));
    assert(trees_equivalent(root1, root2) == 0);
    assert(trees_equivalent(root2, root1) == 0);
    delete_tree(root2);
    printf("Subtest 10 passed.\n");

    delete_tree(root1);
    printf("Test passed.\n");
}


void test_balancing(void) {
    printf("\nTree balancing test started.\n");

    Tree_ptr root = balance_tree(NULL);
    assert(root == NULL);
    printf("Subtest 1 passed.\n");

    root = new_node(1);
    Tree_ptr root_copy = root;
    root = balance_tree(root);
    assert(root != NULL);
    assert(root == root_copy);
    delete_tree(root);
    printf("Subtest 2 passed.\n");

    root = new_tree(ASCENDING_ARRAY, 5);
    root = balance_tree(root);
    assert(root != NULL);
    assert(tree_valid(root) == 1);
    long control_array1[] = {3, 2, 1, 4, 5};
    Tree_ptr control = new_tree(control_array1, 5);
    assert(trees_equivalent(root, control) == 1);
    delete_tree(root);
    delete_tree(control);
    printf("Subtest 3 passed.\n");

    root = new_tree(DESCENDING_ARRAY, 5);
    root = balance_tree(root);
    assert(root != NULL);
    assert(tree_valid(root) == 1);
    long control_array2[] = {-3, -2, -1, -4, -5};
    control = new_tree(control_array2, 5);
    assert(trees_equivalent(root, control) == 1);
    delete_tree(root);
    delete_tree(control);
    printf("Subtest 4 passed.\n");

    root = new_tree(BIG_ARRAY, sizeof BIG_ARRAY / sizeof(long));
    root = balance_tree(root);
    assert(root != NULL);
    assert(tree_valid(root) == 1);
    long control_array3[] = {18, -2, 9005, -3564, 1, 573, -8, 4, 245, 1463, 83, 1746};
    control = new_tree(control_array3, sizeof control_array3 / sizeof(long));
    assert(trees_equivalent(root, control) == 1);
    delete_tree(root);
    delete_tree(control);
    printf("Subtest 5 passed.\n");

    printf("Test passed.\n");
}


void test_creating_balanced_tree() {
    printf("\nBalanced tree creation test started.\n");

    Tree_ptr root = new_balanced_tree(NULL, 10);
    assert(root == NULL);
    printf("Subtest 1 passed.\n");

    root = new_balanced_tree(ASCENDING_ARRAY, 0);
    assert(root == NULL);
    printf("Subtest 2 passed.\n");

    root = new_balanced_tree(ASCENDING_ARRAY, 5);
    assert(root != NULL);
    assert(tree_valid(root) == 1);
    assert(tree_size(root) == 5);
    assert(tree_depth(root) == 3);
    long *values = tree_to_array(root);
    size_t i;
    for (i = 0; i < 5; i++)
        assert(values[i] == ASCENDING_ARRAY[i]);
    free(values);
    delete_tree(root);
    printf("Subtest 3 passed.\n");

    printf("Test passed.\n");
}


void test_merging_balanced_trees() {
    printf("\nBalanced trees merging test started.\n");

    Tree_ptr root = merge_balanced_trees(NULL, NULL);
    assert(root == NULL);
    printf("Subtest 1 passed.\n");

    Tree_ptr root2 = new_balanced_tree(ASCENDING_ARRAY, 5);
    root = merge_balanced_trees(NULL, root2);
    assert(root != NULL);
    assert(trees_equivalent(root, root2));
    delete_tree(root);
    printf("Subtest 2 passed.\n");

    root = merge_balanced_trees(root2, NULL);
    assert(root != NULL);
    assert(trees_equivalent(root, root2));
    delete_tree(root);
    printf("Subtest 3 passed.\n");

    long arr[] = {-5, -4, -3, -2, -1};
    root = new_balanced_tree(arr, 5);
    Tree_ptr res1 = merge_balanced_trees(root, root2);
    assert(res1 != NULL);
    assert(tree_valid(res1) == 1);
    assert(tree_size(res1) == 10);
    assert(tree_depth(res1) == 4);
    printf("Subtest 4 passed.\n");

    Tree_ptr res2 = merge_balanced_trees(root2, root);
    assert(res2 != NULL);
    assert(tree_valid(res2) == 1);
    assert(tree_size(res2) == 10);
    assert(tree_depth(res2) == 4);
    assert(trees_equivalent(res1, res2));
    printf("Subtest 5 passed.\n");

    delete_tree(root);
    delete_tree(root2);
    delete_tree(res1);
    delete_tree(res2);
    printf("Test passed.\n");
}


#endif //MY_CLIB_TEST_BS_TREE_H
