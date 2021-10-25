//
// Created by Mikhail Tsaritsyn on 25.10.2021.
//

#include "data_structures/linked_list.h"


list_node* new_list_node(size_t data) {
    list_node* node = malloc(sizeof(list_node));
    node->data = data;
    node->next = NULL;
    return node;
}


void attach_list_node(list_node* dst, list_node *src) {
    dst->next = src;
}


void delete_list_node(list_node* node, void (*delete_data)(void *)) {
    delete_data((void *) node->data);
    free(node);
}