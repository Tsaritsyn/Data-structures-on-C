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
//    initial tree:
//        0
    Tree_ptr root = new_node(0);

//    modified tree:
//        0 -> NULL
//          -> 2
    int res = put_value(root, 2);
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
    res = put_value(root, -1);
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
    res = put_value(root, 1);
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
    res = put_value(root, 3);
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
    res = put_value(root, 2);
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
    res = put_value(root, 3);
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

    long array[] = {0, 1, 2, 3, 4};
//    we expect the following tree:
//        0 -> NULL
//          -> 1 -> NULL
//               -> 2 -> NULL
//                    -> 3 -> NULL
//                         -> 4
    Tree_ptr root = new_tree(array, 5);
    assert(root != NULL);
    assert(root->value == 0);
    assert(root->right != NULL);
    assert(root->left == NULL);
    assert(root->right->value == 1);
    assert(root->right->right != NULL);
    assert(root->right->left == NULL);
    assert(root->right->right->value == 2);
    assert(root->right->right->right != NULL);
    assert(root->right->right->left == NULL);
    assert(root->right->right->right->value == 3);
    assert(root->right->right->right->right != NULL);
    assert(root->right->right->right->left == NULL);
    assert(root->right->right->right->right->value == 4);
    delete_tree(root);
    printf("Subtest 1 passed.\n");

    long array1[] = {0, -1, -2, -3, -4};
    //    we expect the following tree:
//        0 -> -1 -> -2 -> -3 -> -4
//                            -> NULL
//                      -> NULL
//                -> NULL
//          -> NULL
    root = new_tree(array1, 5);
    assert(root != NULL);
    assert(root->value == 0);
    assert(root->left != NULL);
    assert(root->right == NULL);
    assert(root->left->value == -1);
    assert(root->left->left != NULL);
    assert(root->left->right == NULL);
    assert(root->left->left->value == -2);
    assert(root->left->left->left != NULL);
    assert(root->left->left->right == NULL);
    assert(root->left->left->left->value == -3);
    assert(root->left->left->left->left != NULL);
    assert(root->left->left->left->right == NULL);
    assert(root->left->left->left->left->value == -4);
    delete_tree(root);
    printf("Subtest 2 passed.\n");

    long array2[] = {1, 4, 18, 573, -2, 573, -3564, 1, -8, 9005, 4, 1463, -8, 1746, -8, 4, 245, 83, -8};
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
    root = new_tree(array2, sizeof(array2) / sizeof(long));
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

    long array[] = {1, 4, 18, 573, -2, 573, -3564, 1, -8, 9005, 4, 1463, -8, 1746, -8, 4, 245, 83, -8};
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
    Tree_ptr root = new_tree(array, sizeof(array) / sizeof(long));
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

    long array[] = {0, 1, 2, 3, 4};
//    we expect the following tree:
//        0 -> NULL
//          -> 1 -> NULL
//               -> 2 -> NULL
//                    -> 3 -> NULL
//                         -> 4
    Tree_ptr root = new_tree(array, 5);
    assert(tree_depth(root) == 5);
    assert(tree_size(root) == 5);
    delete_tree(root);
    printf("Subtest 1 passed.\n");

    long array1[] = {0, -1, -2, -3, -4};
    //    we expect the following tree:
//        0 -> -1 -> -2 -> -3 -> -4
//                            -> NULL
//                      -> NULL
//                -> NULL
//          -> NULL
    root = new_tree(array1, 5);
    assert(tree_depth(root) == 5);
    assert(tree_size(root) == 5);
    delete_tree(root);
    printf("Subtest 2 passed.\n");

    long array2[] = {1, 4, 18, 573, -2, 573, -3564, 1, -8, 9005, 4, 1463, -8, 1746, -8, 4, 245, 83, -8};
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
    root = new_tree(array2, sizeof(array2) / sizeof(long));
    assert(tree_depth(root) == 7);
    assert(tree_size(root) == 12);
    delete_tree(root);
    printf("Subtest 3 passed.\n");

    printf("Test passed.\n");
}


void test_tree2array(void) {
    printf("\nTest tree to array conversion started.\n");

    long array[] = {0, 1, 2, 3, 4};
//    we expect the following tree:
//        0 -> NULL
//          -> 1 -> NULL
//               -> 2 -> NULL
//                    -> 3 -> NULL
//                         -> 4
    Tree_ptr root = new_tree(array, 5);
    long *res = tree_to_array(root);
    int i;
    for (i = 0; i < 5; i++)
        assert(res[i] == array[i]);
    delete_tree(root);
    free(res);
    printf("Subtest 1 passed.\n");

    long array1[] = {0, -1, -2, -3, -4};
    //    we expect the following tree:
//        0 -> -1 -> -2 -> -3 -> -4
//                            -> NULL
//                      -> NULL
//                -> NULL
//          -> NULL
    root = new_tree(array1, 5);
    res = tree_to_array(root);
    for (i = 0; i < 5; i++)
        assert(res[i] == array1[4-i]);
    free(res);
    delete_tree(root);
    printf("Subtest 2 passed.\n");

    long array2[] = {1, 4, 18, 573, -2, 573, -3564, 1, -8, 9005, 4, 1463, -8, 1746, -8, 4, 245, 83, -8};
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
    root = new_tree(array2, sizeof(array2) / sizeof(long));
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

    long array[] = {0, 1, 2, 3, 4};
//    we expect the following tree:
//        0 -> NULL
//          -> 1 -> NULL
//               -> 2 -> NULL
//                    -> 3 -> NULL
//                         -> 4
    root = new_tree(array, 5);
    root_copy = copy_tree(root);
    assert(root_copy != NULL);
    assert(root_copy->value == 0);
    assert(root_copy->right != NULL);
    assert(root_copy->left == NULL);
    assert(root_copy->right->value == 1);
    assert(root_copy->right->right != NULL);
    assert(root_copy->right->left == NULL);
    assert(root_copy->right->right->value == 2);
    assert(root_copy->right->right->right != NULL);
    assert(root_copy->right->right->left == NULL);
    assert(root_copy->right->right->right->value == 3);
    assert(root_copy->right->right->right->right != NULL);
    assert(root_copy->right->right->right->left == NULL);
    assert(root_copy->right->right->right->right->value == 4);
    delete_tree(root);
    delete_tree(root_copy);
    printf("Subtest 3 passed.\n");

    long array2[] = {1, 4, 18, 573, -2, 573, -3564, 1, -8, 9005, 4, 1463, -8, 1746, -8, 4, 245, 83, -8};
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
    root = new_tree(array2, sizeof(array2) / sizeof(long));
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
    printf("Subtest 2 passed.\n");

    long array[] = {0, 1, 2, 3, 4};
//    we expect the following tree:
//        0 -> NULL
//          -> 1 -> NULL
//               -> 2 -> NULL
//                    -> 3 -> NULL
//                         -> 4
    root = new_tree(array, 5);
    max_node = max_node_valid(root), min_node = min_node_valid(root);
    assert(max_node != NULL);
    assert(min_node != NULL);
    assert(max_node->value == 4);
    assert(min_node->value == 0);
    delete_tree(root);
    printf("Subtest 3 passed.\n");

    long array1[] = {0, -1, -2, -3, -4};
    //    we expect the following tree:
//        0 -> -1 -> -2 -> -3 -> -4
//                            -> NULL
//                      -> NULL
//                -> NULL
//          -> NULL
    root = new_tree(array1, 5);
    max_node = max_node_valid(root), min_node = min_node_valid(root);
    assert(max_node != NULL);
    assert(min_node != NULL);
    assert(max_node->value == 0);
    assert(min_node->value == -4);
    delete_tree(root);
    printf("Subtest 4 passed.\n");

    long array2[] = {1, 4, 18, 573, -2, 573, -3564, 1, -8, 9005, 4, 1463, -8, 1746, -8, 4, 245, 83, -8};
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
    root = new_tree(array2, sizeof(array2) / sizeof(long));
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
    printf("Subtest 2 passed.\n");

    long array[] = {1, 4, 18, 573, -2, 573, -3564, 1, -8, 9005, 4, 1463, -8, 1746, -8, 4, 245, 83, -8};
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
    root = new_tree(array, sizeof(array) / sizeof(long));
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

    long array1[] = {1, 2, 3, 4, 5};
    long array2[] = {1, 2, 3, 4, -5};
    long array3[] = {1, 2, 3, -4, 5};
    long array4[] = {-1, 2, 3, 4, 5};
    long array5[] = {1, 2, 3, 4, 5, 6};
    long array6[] = {5, 4, 3, 2, 1};
    long array7[] = {-5, -4, -3, -2, -1};

    Tree_ptr root1 = new_tree(array1, 5);
    Tree_ptr root2 = new_tree(array1, 5);
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
}


#endif //MY_CLIB_TEST_BS_TREE_H
