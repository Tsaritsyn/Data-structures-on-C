//
// Created by Mikhail Tsaritsyn on 25.10.2021.
//

#ifndef MY_CLIB_DICTIONARY_H
#define MY_CLIB_DICTIONARY_H

#include "KV_tree.h"


/**
 * This structure denotes a tree-based dictionary allowing usage of arbitrary elements as keys and values.
 */
typedef struct Dict {
    KV_node* tree;
    size_t size;
    int (*compare_keys)(const void*, const void*);
    void (*print_key)(const void*);
    void (*print_value)(const void*);
    void (*delete_key)(void*);
    void (*delete_data)(void*);
} Dict;


Dict* new_empty_dict(
        int (*compare_keys)(const void*, const void*),
        void (*print_key)(const void*),
        void (*print_value)(const void*),
        void (*delete_key)(void*),
        void (*delete_data)(void*)
    );


/**
 * Frees the memory occupied by the given dictionary and destroys all its keys and data.
 */
void delete_dict(Dict* dict);


int is_dict_empty(const Dict* dict);


/**
 * Adds the given key-value pair to the given dictionary. If the given key already exists, rewrites the data.
 */
void add_to_dict(Dict* dict, void* key, void* value);


/**
 * @return the value corresponding to the given key. If it is not present in the dictionary, returns NULL
 */
void* get_from_dict(const Dict* dict, const void* key);


/**
 * Displays all the key-value pairs sorted in ascending order wrt the keys.
 */
void print_dict(const Dict* dict);


/**
 * Removes the item corresponding to the given key from the dictionary. The copy of the data and the key stored in the
 * dictionary will be destroyed.
 *
 * @param dict
 * @param key
 * @return 0 if there was no such element, 1 if removed successfully and -1 if an error occurred
 */
int remove_from_dict(Dict* dict, const void* key);


#endif //MY_CLIB_DICTIONARY_H
