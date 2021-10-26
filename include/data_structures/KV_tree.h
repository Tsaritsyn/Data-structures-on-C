//
// Created by Mikhail Tsaritsyn on 25.10.2021.
//

#ifndef MY_CLIB_KV_TREE_H
#define MY_CLIB_KV_TREE_H

#include <glob.h>
#include <stdlib.h>

#include "common.h"
#include "array.h"
#include "pair.h"


typedef struct KV_node KV_node;

/**
 * This structure represents a more complex version of Binary Search tree. Here the nodes are compared using the keys
 * only, and the data is just stored.
 *
 * This structure contains pointers to structures considered key and values. Keys must be comparable in the sense that
 * not only comparison function must be defined for them, but (key1 < key2) || (key1 == key2) || (key1 > key2) must be
 * always True.
 */
struct KV_node {
    KV_node *left, *right;
    void *key, *data;
};


/**
 * @param key pointer structure that will act as a kew
 * @param data pointer to structure that will act as the stored data
 * @return pointer to a new node containing key and data
 */
KV_node* new_kv_node(void* key, void* data);


/**
 * Frees the memory allocated for the given node. The key and data structures will also be destroyed.
 *
 * @param delete_key the function that will delete the key structure given a pointer to it
 * @param delete_data the function that will delete the data structure given a pointer to it
 */
void delete_kv_node(KV_node* node, void (*delete_key)(void*), void (*delete_data)(void*));


/**
 * Copies all the content from one node to another. The source node and all its data structures will remain intact.
 *
 * @param src node from where to copy the data
 * @return pointer to the copy of the given node
 */
KV_node* copy_kv_node(const KV_node* src);


/**
 * Replaces all the content of the destination node with that of the source node. The old content will be deleted
 * properly.
 *
 * WARNING: the subtrees of the destination node will be assigned to the source values, but the old ones will not be
 * deleted.
 */
void replace_kv_node(KV_node* dst, const KV_node *src, void (*delete_key)(void*), void (*delete_data)(void*));


/**
 * Deletes the whole tree, with all its nodes;
 *
 * @param tree pointer to the tree root
 * @param delete_key the function that will delete the key structure given a pointer to it
 * @param delete_data the function that will delete the data structure given a pointer to it
 */
void delete_kv_tree(KV_node* tree, void (*delete_key)(void*), void (*delete_data)(void*));


/**
 * Inserts the key-data pair into the tree wrt the key value. If the given key already exists, its data will be
 * rewritten.
 *
 * @param tree pointer to a tree to insert into
 * @param key pointer to the key structure
 * @param data pointer to the data structure
 * @param compare_keys function that will compare the key structures to put the pair into the right place
 * @return if the given key existed, returns the pointer to the data it stored, otherwise NULL
 */
void* insert_to_kv_tree(KV_node* tree, void* key, void* data, int (*compare_keys)(const void*, const void*));


size_t kv_tree_depth(const KV_node* tree);


size_t kv_tree_size(const KV_node* tree);


/**
 * Balances the tree.
 *
 * @param compare_keys function that will compare the key structures given pointers to them
 * @return new root of the tree
 */
KV_node *balance_kv_tree(KV_node *tree);


/**
 * @return array of pointers to the tree nodes sorted by their key values
 */
array_size_t_ptr linearize_kv_tree(const KV_node* tree);


/**
 * @param tree pointer to the tree from where to take the values
 * @param key pointer to the desired key structure
 * @param compare_keys function that will compare the key structures given pointers to them
 * @return a pair containing first a pointer to the node with given key (if NULL, then this key does not exist) and
 * second pointer to its parent (if NULL, it's the root)
 */
Pair* find_in_kv_tree(const KV_node* tree, const void *key, int (*compare_keys)(const void*, const void*));


/**
 * Removes the node with the given key from the tree. Deletes the node, the key and data structure.
 *
 * WARNING: If the tree consists of a single element, it will not be deleted.
 *
 * @param tree tree to delete from
 * @param key key to delete
 * @return 1 if deleted successfully, 0 if the given key was not present in the tree, and -1 if an error happened
 */
int remove_from_kv_tree(KV_node *tree, const void *key,
                        int (*compare_keys)(const void *, const void *),
                        void (*delete_key)(void *),
                        void (*delete_data)(void *));


#endif //MY_CLIB_KV_TREE_H
