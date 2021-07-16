//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//
// Implements the Binary Search Tree containing values of the type long.
//

#ifndef MY_CLIB_BS_TREE_H
#define MY_CLIB_BS_TREE_H

#include "stddef.h"
#include <stdio.h>
#include "stdlib.h"
#include "stdarg.h"
#include "../common.h"

typedef struct bs_node Tree;
typedef struct bs_node* Tree_ptr;
// signals that the structure being pointed at must not be changed
#define Tree_ptr_c const struct bs_node*


struct bs_node {
    // since pointers are of type unsigned long, the structure will align the value field,
    // so that it will also take 8 bytes no matter if it is shorter really, so usage of types int or short will not
    // gain memory
    long value;
    Tree_ptr left, right;
};


/**
 * Allocates memory for a new node and puts the given value inside it.
 *
 * @param value value to be stored in the new node
 * @return pointer to the memory allocated for the new node
 */
Tree_ptr new_node(long value);


/**
 * Creates a new tree and initializes it with the values from the given array. The tree is guaranteed to be valid.
 *
 * @param array array of values that will be stored in the tree according to BS tree rules;
 *  if some values are repeated, only one copy of each will be stored
 * @param size size of the array (size of the tree will be less, if the values are repeated)
 * @return the pointer to the root of this tree
 */
Tree_ptr new_tree(const long *array, size_t size);


/**
 * Frees the memory taken by the whole tree with given root.
 *
 * @param root pointer to the root of the tree; if it's not a root, then only its subtrees and itself will be deleted
 */
void delete_tree(Tree_ptr root);


/**
 * Adds the value to the tree. If it is already present, then the operation will have no effect. The resulting tree is
 * guaranteed to be valid.
 *
 * @param root pointer to the root of the tree
 * @param value value to be put
 * @return 1 if the value has been added and 0 otherwise
 */
int tree_insert_value(Tree_ptr root, long value);


/**
 * Searches for the node that set_contains the given value in the valid tree. If the tree is not valid, the result may not
 * be correct. <br>
 * <br>
 * Example: <br>
 * We have tree of the following structure (numbers represent contained values) <br>
 * 2 <br>
 * | \ <br>
 * 1  3 <br>
 * and we execute the following code:
 *
 * \code{.c}
 * Tree_ptr parent, node;
 * node = find_node(value, 1, &parent);
 * \endcode
 *
 * <ul>
 * <li> If value == 1, then node == &1 and parent == &2.
 * <li> If value == 4, then node == NULL and parent == &3.
 * <li> If value == 2, then node == &2 and parent == NULL.
 * </ul>
 *
 * If we do not need the parent, we execute it as follows:
 *
 * \code{.c}
 * node = find_node(value, 0).
 * \endcode
 *
 * @param root root to the tree; if it's not a root, then the search will be done only among its subtrees and itself
 * @param value value to be found
 * @param get_parent should be 0 or 1. It indicates if the pointer to parent node must be provided, too
 * @param ... if get_parent != 0, then the fourth argument must be given of type Tree_ptr*. The pointer to the parent will
 * be written in it or NULL, if the value is contained in the root
 * @return the pointer to the node containing the desired value, or NULL if the value is not present in the tree
 */
Tree_ptr find_node(Tree_ptr_c root, long value, long get_parent, ...);


/**
 * Deletes the node containing the given value from the tree, while preserving the pointer to the root untouched. If
 * the tree was valid, it is guaranteed to remain valid. Otherwise, the desired value may not be deleted. If it is not
 * present in the tree, then the operation will have no effect.
 *
 * @param root pointer to the root of the tree
 * @param value value to be deleted
 * @return 1 if the value has been removed and 0 otherwise
 */
int remove_value(Tree_ptr root, long value);


/**
 * Allocates the memory and copies the content of the given tree there. NOTE that this copy need to be deleted
 * independently from the original tree!
 *
 * @param src the tree to be copied
 * @return the pointer to the root of a copy of the given tree with preserved structure and values
 */
Tree_ptr copy_tree(Tree_ptr src);


/**
 * Depth of NULL is considered 0. Depth of a single node with no children is 1.
 *
 * @param root pointer to the root of the tree
 * @return the depth of the given tree
 */
size_t tree_depth(Tree_ptr_c root);


/**
 * @return 1 if both trees have the same structure and contain the same values, and 0 otherwise.
 */
char trees_equal(Tree_ptr_c root1, Tree_ptr_c root2);


/**
 * We call a BS tree valid if any node's left subtree, if exists, set_contains smaller values than the node itself, while
 * right subtree, if exists, set_contains bigger values than the node itself. Moreover, each value in the tree must be
 * unique. <br>
 * NOTE that NULL is a valid tree.
 *
 * @param root pointer to the root of the tree
 * @return 1 if the given tree is a valid BS tree and 0 otherwise
 */
char tree_valid(Tree_ptr_c root);


/**
 * We call two trees equivalent if they are both valid, contain the same set of values and have the same size and depth.
 * Both trees are assumed to be valid, otherwise the result may be any. <br>
 * Two NULLs are equivalent to each other, but NULL is not equivalent to not NULL tree.
 *
 * @return 1 if two trees are equivalent and 0 otherwise
 */
char trees_equivalent(Tree_ptr_c root1, Tree_ptr_c root2);


/// Displays the contained values in the ascending order (if the tree is not valid, the order is not guaranteed).
void print_tree(Tree_ptr_c root);


/// Displays the tree with its structure (children have bigger indentation than parent).
void draw_tree(Tree_ptr_c root);


/// @return the number of nodes in the given tree
size_t tree_size(Tree_ptr_c root);


/**
 *
 * @return the array of the values contained in the tree; if the tree is a valid BS, then the order will be ascending,
 * otherwise no guarantees on the order are given
 */
long* tree_to_array(Tree_ptr_c root);


/// @return the pointer to the node containing the maximum value, given that the tree is valid
Tree_ptr max_node_valid(Tree_ptr_c root);


/// @return the pointer to the node containing the minimum value, given that the tree is valid
Tree_ptr min_node_valid(Tree_ptr_c root);


/// @return the pointer to the node containing the minimum value with no assumption on the tree; if several such nodes
/// exist, returns any of them
Tree_ptr min_node_general(Tree_ptr_c root);


/// @return the pointer to the node containing the maximum value with no assumption on the tree; if several such nodes
/// exist, returns any of them
Tree_ptr max_node_general(Tree_ptr_c root);


/**
 * We call the tree balanced, if for any node the depths of its left and right subtrees differ at most by 1.
 * Reorganizes the nodes of the given tree so that it becomes balanced.
 *
 * @param root pointer to the root of a tree (may not be a valid BS)
 * @return pointer to the new root of the tree (since it may change)
 */
Tree_ptr balance_tree(Tree_ptr root);


/// @return the maximum value stored in the valid BS tree or LONG_MIN if the tree is empty
long max_tree_value(Tree_ptr_c root);


/// @return the minimum value stored in the valid BS tree or LONG_MAX if the tree is empty
long min_tree_value(Tree_ptr_c root);

#endif //MY_CLIB_BS_TREE_H
