//
// Created by Mikhail Tsaritsyn on 16.07.2021.
//

#include "../data_structures/set_long.h"


Set_long_ptr create_set(void) {
    Set_long_ptr set = malloc(sizeof(Set_long));
    set->tree = NULL;
    set->size = 0;
    set->min_element = LONG_MAX;
    set->max_element = LONG_MIN;
    return set;
}


void delete_set(Set_long_ptr set) {
    delete_tree(set->tree);
    free(set);
}


int set_is_empty(Set_long_ptr_c set) {
    return (set->size == 0) ? 1 : 0;
}


int set_insert_element(Set_long_ptr set, long element) {
//    create a new tree
    if (set->tree == NULL) {
        set->tree = new_node(element);
        set->size = 1;
        set->max_element = set->min_element = element;
        return 1;
    }
//    insert into the existing tree
    else {
        int res = tree_insert_value(set->tree, element);
//        if the element has not been there yet, update the set statistics and rebalance the tree
        if (res) {
            set->max_element = MAX(set->max_element, element);
            set->min_element = MIN(set->min_element, element);
            set->size++;
            balance_tree(set->tree);
        }
        return res;
    }
}


int set_remove_element(Set_long_ptr set, long element) {
    if (set->tree == NULL)
        return 0;

//    if the element is not in the range of contained elements, we know that it's not in the set
    if (element > set->max_element || element < set->min_element)
        return 0;

    int res = remove_value(set->tree, element);

//    if the element has been removed, update the statistics and rebalance the tree
    if (res == 1) {
        balance_tree(set->tree);

        set->size--;
        if (set->max_element == element)
            set->max_element = max_tree_value(set->tree);
        if (set->min_element == element)
            set->min_element = min_tree_value(set->tree);
    }
//    the element may not be deleted because it's not present or the tree set_contains only one element
//    if the tree consists of only one element, we'll remove it manually, if needed
    else if (set->size == 1) {
        if (set->tree->value == element) {
            delete_tree(set->tree);
            set->size = 0;
            set->min_element = LONG_MAX;
            set->max_element = LONG_MIN;
            return 1;
        }
    }
    return res;
}


int set_contains(Set_long_ptr_c set, long element) {
    if (set->tree == NULL)
        return 0;

//    if the element is not in the range of contained elements, we know that it's not in the set
    if (element > set->max_element || element < set->min_element)
        return 0;

    return (find_node(set->tree, element, 0) == NULL) ? 0 : 1;
}


long* set_to_array(Set_long_ptr_c set) {
    return tree_to_array(set->tree);
}


void print_set(Set_long_ptr_c set) {
    if (set_is_empty(set)) {
        printf("EMPTY\n");
        return;
    }

    print_tree(set->tree);
    printf("\n");
}


int set_is_included(Set_long_ptr_c set1, Set_long_ptr_c set2) {
    if (set_is_empty(set1))
        return 1;

//    consider knowingly false cases
    if (set1->min_element <= set2->min_element ||
        set1->max_element >= set2->max_element ||
        set1->size >= set2->size)
        return 0;

//    check if all the elements of the first set are contained in the second one
    long *arr = tree_to_array(set1->tree);
    size_t i;
    int res = 1;
    for (i = 0; i < set1->size; i++) {
        if (!set_contains(set2, arr[i])) {
            res = 0;
            break;
        }
    }

    free(arr);
    return res;
}


int set_is_equal(Set_long_ptr_c set1, Set_long_ptr_c set2) {
//    all empty sets are always equal to each other
    if (set_is_empty(set1) && set_is_empty(set2))
        return 1;

//    consider knowingly false cases
    if (set1->min_element != set2->min_element ||
        set1->max_element != set2->max_element ||
        set1->size >= set2->size)
        return 0;

    return trees_equivalent(set1->tree, set2->tree);
}


Set_long_ptr copy_set(Set_long_ptr_c src) {
    if (src == NULL)
        return NULL;

    Set_long_ptr dst = create_set();
    dst->size = src->size;
    dst->max_element = src->max_element;
    dst->min_element = src->min_element;
    dst->tree = copy_tree(src->tree);
    return dst;
}


Set_long_ptr get_union(Set_long_ptr_c set1, Set_long_ptr_c set2) {
//    check special cases
    if (set_is_equal(set1, set2))
        return copy_set(set1);

    if (set_is_included(set1, set2))
        return copy_set(set2);

    if (set_is_included(set2, set1))
        return copy_set(set1);

//    create a new set and fill it with the values from the given sets
    Set_long_ptr res = create_set();
    res->tree = merge_balanced_trees(set1->tree, set2->tree);
    res->size = tree_size(res->tree);
    res->max_element = MAX(set1->max_element, set2->max_element);
    res->min_element = MIN(set1->min_element, set2->min_element);
    return res;
}


int sets_intersect(Set_long_ptr_c set1, Set_long_ptr_c set2) {
    if (set_is_empty(set1) || set_is_empty(set2))
        return 0;

    if (set1->max_element < set2->min_element || set1->min_element > set2->max_element)
        return 0;

//    check if any element of the first set is contained in the second one
    long *arr = tree_to_array(set1->tree);
    size_t i;
    int res = 0;
    for (i = 0; i < set1->size; i++) {
        if (set_contains(set2, arr[i])) {
            res = 1;
            break;
        }
    }

    free(arr);
    return res;
}


Set_long_ptr get_intersection(Set_long_ptr_c set1, Set_long_ptr_c set2) {
    Set_long_ptr res = create_set();

    if (set_is_empty(set1) || set_is_empty(set2))
        return res;

    if (set1->max_element < set2->min_element || set1->min_element > set2->max_element)
        return res;

//    add all elements of the first set that are contained in the second one to the resulting set
    long *arr = tree_to_array(set1->tree);
    size_t i;
    for (i = 0; i < set1->size; i++) {
        if (set_contains(set2, arr[i]))
            set_insert_element(res, arr[i]);
    }

    free(arr);
    return res;
}