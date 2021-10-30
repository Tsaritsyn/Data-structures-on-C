//
// Created by Mikhail Tsaritsyn on 25.10.2021.
//

#ifndef MY_CLIB_LINKED_LIST_H
#define MY_CLIB_LINKED_LIST_H

#include <glob.h>
#include <stdlib.h>


/**
 * The data stored inside is a size_t value, which allows to interpret it as a pointer to some complex structure.
 */
typedef struct list_node {
    struct list_node* next;
    size_t data;
} list_node;


/**
 * Creates a list node with NULL pointer to next and given data stored.
 *
 * @return pointer to the created node
 */
list_node* new_list_node(size_t data);


/**
 * Attaches the second node to the first one as its next, so that dst->next = src
 *
 * @param dst node to attach to
 * @param src node to be attached
 */
void attach_list_node(list_node* dst, list_node *src);


/**
 * Removes the given node, deleting also the data stored in it.
 *
 * @param node
 * @param delete_data function that will handle the deletion of the data structure being pointed at by the data
 */
void delete_list_node(list_node* node, void (*delete_data)(void *));


#endif //MY_CLIB_LINKED_LIST_H
