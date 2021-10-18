/**
 * Created by Mikhail Tsaritsyn on 16.07.2021.
 *
 * Implements a set container based on the Binary Search tree. The tree is guaranteed to be balanced at any point of
 * time, therefore the complexity of adding, search and deleting an element is O(log(n))
 */

#ifndef MY_CLIB_SET_LONG_H
#define MY_CLIB_SET_LONG_H

#include "BS_tree.h"
#include "stdlib.h"
#include "limits.h"
#include "common.h"

typedef struct {
    Tree_ptr tree;
    size_t size;
    long min_element, max_element;
} Set_long;
typedef Set_long* Set_long_ptr;
#define Set_long_ptr_c const Set_long*


/**
 * Allocates memory for the set structure and initializes its fields.
 *
 * @return pointer to the new empty set
 */
Set_long_ptr create_set(void);


/// Frees all the memory occupied by this set.
void delete_set(Set_long_ptr set);


/// @return 1 if the given set is empty and 0 otherwise
int set_is_empty(Set_long_ptr_c set);


/**
 * Inserts the given element in the given set, if it's not already there.
 *
 * @return 1 if the element has been inserted and 0 otherwise
 */
int set_insert_element(Set_long_ptr set, long element);


/**
 * Removes the given element from the given set, if it is contained there.
 *
 * @return 1 if the element has been removed and 0 otherwise
 */
int set_remove_element(Set_long_ptr set, long element);


/// @return 1 if the given set set_contains the given element and 0 otherwise
int set_contains(Set_long_ptr_c set, long element);


/// @return the array containing all the values of the given set in the ascending order
long* set_to_array(Set_long_ptr_c set);


/// Displays all the elements of the set in the ascending order.
void print_set(Set_long_ptr_c set);


/// @return 1 if the first set is strictly included in the second one and 0 otherwise
int set_is_included(Set_long_ptr_c set1, Set_long_ptr_c set2);


/// @return 1 if two sets are equal and 0 otherwise
int set_is_equal(Set_long_ptr_c set1, Set_long_ptr_c set2);


/// @return a copy of the given src; note that it occupies its own memory and must be deleted separately
Set_long_ptr copy_set(Set_long_ptr_c src);


/// @return the union of the given two sets
Set_long_ptr get_union(Set_long_ptr_c set1, Set_long_ptr_c set2);


/// @return 1 if two sets have non-empty intersection and 0 otherwise
int sets_intersect(Set_long_ptr_c set1, Set_long_ptr_c set2);


/// @return the intersection of the given two sets
Set_long_ptr get_intersection(Set_long_ptr_c set1, Set_long_ptr_c set2);


#endif //MY_CLIB_SET_LONG_H
