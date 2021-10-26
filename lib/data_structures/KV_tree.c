//
// Created by Mikhail Tsaritsyn on 25.10.2021.
//

#include "data_structures/KV_tree.h"


KV_node* new_kv_node(void* key, void* data) {
    KV_node* node = malloc(sizeof(KV_node));
    node->key = key;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}


void delete_kv_node(KV_node* node, void (*delete_key)(void*), void (*delete_data)(void*)) {
    if (node == NULL)
        return;

    delete_key(node->key);
    delete_data(node->data);
    free(node);
}


void delete_kv_tree(KV_node* tree, void (*delete_key)(void*), void (*delete_data)(void*)) {
    if (tree == NULL)
        return;

    delete_kv_tree(tree->left, delete_key, delete_data);
    delete_kv_tree(tree->right, delete_key, delete_data);
    delete_kv_node(tree, delete_key, delete_data);
}


void* insert_to_kv_tree(KV_node* tree, void* key, void* data, int (*compare_keys)(const void*, const void*)) {
    int key_relation = compare_keys(key, tree->key);

    if (key_relation > 0) {
        if (tree->right == NULL) {
            tree->right = new_kv_node(key, data);
            return NULL;
        }
        else
            return insert_to_kv_tree(tree->right, key, data, compare_keys);
    }
    else if (key_relation < 0) {
        if (tree->left == NULL) {
            tree->left = new_kv_node(key, data);
            return NULL;
        }
        else
            return insert_to_kv_tree(tree->left, key, data, compare_keys);
    }
    else {
        void* old_data = tree->data;
        tree->data = data;
        return old_data;
    }
}


KV_node* find_in_kv_tree(const KV_node* tree, const void *key, int (*compare_keys)(const void*, const void*)) {
    int key_relation = compare_keys(key, tree->key);

    if (key_relation > 0) {
        if (tree->right == NULL)
            return NULL;
        else
            return find_in_kv_tree(tree->right, key, compare_keys);
    }
    else if (key_relation < 0) {
        if (tree->left == NULL)
            return NULL;
        else
            return find_in_kv_tree(tree->left, key, compare_keys);
    }
    else
        return tree;
}


size_t kv_tree_depth(const KV_node* tree) {
    if (tree == NULL)
        return 0;
    else {
        size_t right_depth = kv_tree_depth(tree->right);
        size_t left_depth = kv_tree_depth(tree->left);
        return 1 + MAX(right_depth, left_depth);
    }
}


size_t kv_tree_size(const KV_node* tree) {
    if (tree == NULL)
        return 0;
    else
        return 1 + kv_tree_size(tree->right) + kv_tree_size(tree->left);
}


/// swaps the node with its right neighbour
static KV_node* turn_left(KV_node* node) {
    if (node->right == NULL) {
        printf("Error in turn_left: the right node is NULL.\n");
        return node;
    }

    KV_node* new_node = node->right;
    node->right = new_node->left;
    new_node->left = node;
    return new_node;
}


/// swaps the node with its left neighbour
static KV_node* turn_right(KV_node* node) {
    if (node->left == NULL) {
        printf("Error in turn_right: the left node is NULL.\n");
        return node;
    }

    KV_node* new_node = node->left;
    node->left = new_node->right;
    new_node->right = node;
    return new_node;
}


KV_node *balance_kv_tree(KV_node *tree) {
    if (tree == NULL)
        return NULL;

    size_t ld = kv_tree_depth(tree->left), rd = kv_tree_depth(tree->right);

    //    it's a leaf or its children are leaves, there is nothing to balance
    if (ld <= 1 && rd <= 1)
        return tree;

//    rotate the tree until its depths become almost equal
    if (ld >= rd + 1)
        while (ld >= rd + 1) {
            tree = turn_right(tree);
            ld--;
            rd++;
        }
    else
        while (rd >= ld + 1) {
            tree = turn_left(tree);
            rd--;
            ld++;
        }

    tree->left = balance_kv_tree(tree->left);
    tree->right = balance_kv_tree(tree->right);

    return tree;
}


static void extract_values(const KV_node* root, array_size_t_ptr array) {
    if (root == NULL)
        return;

    extract_values(root->left, array);
    array_size_t_append(array, (u_long) root);
    extract_values(root->right, array);
}


array_size_t_ptr linearize_kv_tree(const KV_node* tree) {
    array_size_t_ptr result = new_empty_array_size_t(kv_tree_size(tree));
    extract_values(tree, result);
    return result;
}



