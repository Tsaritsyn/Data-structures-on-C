//
// Created by Mikhail Tsaritsyn on 25.10.2021.
//

#include "data_structures/dictionary.h"


Dict* new_empty_dict(
        int (*compare_keys)(const void*, const void*),
        void (*print_key)(const void*),
        void (*print_value)(const void*),
        void (*delete_key)(void*),
        void (*delete_data)(void*)
) {
    Dict* dict = malloc(sizeof(Dict));
    dict->tree = NULL;
    dict->size = 0;
    dict->compare_keys = compare_keys;
    dict->print_key = print_key;
    dict->print_value = print_value;
    dict->delete_key = delete_key;
    dict->delete_data = delete_data;
    return dict;
}


void delete_dict(Dict* dict) {
    delete_kv_tree(dict->tree, dict->delete_key, dict->delete_data);
    free(dict);
}


int is_dict_empty(const Dict* dict) {
    return dict->size == 0;
}


void add_to_dict(Dict* dict, void* key, void* value) {
    if (dict->tree == NULL) {
        dict->tree = new_kv_node(key, value);
    }
    else {
        void* old_data = insert_to_kv_tree(dict->tree, key, value, dict->compare_keys);
        dict->tree = balance_kv_tree(dict->tree);

        if (old_data != NULL)
            dict->delete_data(old_data);
    }
    dict->size++;
}


void* get_from_dict(const Dict* dict, const void* key) {
//    KV_node *node = find_in_kv_tree(dict->tree, key, dict->compare_keys);
    Pair* pair = find_in_kv_tree(dict->tree, key, dict->compare_keys);

    void* data;
    if (pair->first == NULL)
        data = NULL;
    else
        data = ((KV_node*)pair->first)->data;
    free(pair);
    return data;
}


void print_dict(const Dict* dict) {
    array_size_t_ptr linearized = linearize_kv_tree(dict->tree);
    size_t i;
    printf("dict(\n");
    for (i = 0; i < linearized->length; i++) {
        printf("\t");
        dict->print_key(((KV_node*)linearized->elements[i])->key);
        printf(": ");
        dict->print_value(((KV_node*)linearized->elements[i])->data);
        printf("%s", (i == linearized->length - 1) ? "\n" : ",\n");
    }
    printf(")");
    delete_array(linearized);
}


int remove_from_dict(Dict* dict, const void* key) {
    if (dict->size == 0)
        return 0;

    if (dict->size == 1) {
        if (dict->compare_keys(dict->tree->key, key) == 0) {
            delete_kv_tree(dict->tree, dict->delete_key, dict->delete_data);
            dict->tree = NULL;
        }
        else
            return 0;
    }
    else {
        int result = remove_from_kv_tree(dict->tree, key, dict->compare_keys, dict->delete_key, dict->delete_data);
        if (result != 1)
            return result;

//        we need to re-balance the tree only if the item has been removed successfully
        balance_kv_tree(dict->tree);
    }
    dict->size--;
    return 1;
}


