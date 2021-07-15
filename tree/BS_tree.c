//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#include "BS_tree.h"


#define MAX(a, b) ((a > b) ? a : b)


Tree_ptr new_node(long value) {
    Tree_ptr node = malloc(sizeof(Tree));
    node->left = NULL;
    node->right = NULL;
    node->value = value;
}


// the second argument has type "long" because va_start operates with 16-bit chunks
Tree_ptr find_node(Tree_ptr_c root, long value, long get_parent, ...) {
    Tree_ptr node = (Tree_ptr)root;

//    if we do not need to keep the parent
    if (!get_parent) {
//        search for the node until we reach the leaves of the tree
        while (node->value != value) {
            if (value < node->value) {
//                we've reached the left leaf and have not found the value
                if (node->left == NULL)
                    return NULL;
                else
                    node = node->left;
            }
            else {
                if (node->right == NULL)
                    return NULL;
                else
                    node = node->right;
            }
        }
        return node;
    }
    else {
        va_list ap;
        va_start(ap, get_parent);
//        treat the last argument as the pointer to the pointer to the parent node to be returned
        Tree_ptr *parent_ptr = (Tree_ptr*)va_arg(ap, unsigned long);
//        initialize it with null pointer
        *parent_ptr = NULL;

//        search for the node until we reach the leaves of the tree
        while (node->value != value) {
            *parent_ptr = node;
            if (value < node->value) {
//                we've reached the left leaf and have not found the value
                if (node->left == NULL) {
                    va_end(ap);
                    return NULL;
                }
                else
                    node = node->left;
            }
            else {
                if (node->right == NULL) {
                    va_end(ap);
                    return NULL;
                }
                else
                    node = node->right;
            }
        }

        va_end(ap);
        return node;
    }
}


int put_value(Tree_ptr root, long value) {
    Tree_ptr parent = NULL, node = NULL;
    node = find_node(root, value, 1, &parent);

//    the value is already present in the tree
    if (node != NULL)
        return 0;

    if (parent == NULL) {
        printf("Error in put_value: could not find neither node nor its parent.");
        return -1;
    }

    if (value < parent->value)
        parent->left = new_node(value);
    else
        parent->right = new_node(value);
    return 1;
}


void delete_tree(Tree_ptr root) {
    if (root == NULL)
        return;

    delete_tree(root->left);
    delete_tree(root->right);

    free((void *) root);
    root = NULL;
}


Tree_ptr new_tree(const long *array, size_t size) {
    Tree_ptr root = new_node(array[0]);
    int i;
    for (i = 1; i < size; i++)
        put_value(root, array[i]);
    return root;
}


void print_tree(Tree_ptr_c root) {
    if (root == NULL)
        return;

    print_tree(root->left);
    printf("%ld ", root->value);
    print_tree(root->right);
}


static void draw_subtree(const Tree_ptr root, unsigned int depth) {
    int i;
    for (i = 0; i < depth; i++) {
        printf("  ");
    }

    if (root == NULL) {
        printf("NULL\n");
        return;
    }

    printf("%ld\n", root->value);

//    will terminate if it's a leaf
    if (root->left == NULL && root->right == NULL)
        return;

    printf("l: ");
    draw_subtree(root->left, depth + 1);

    printf("r: ");
    draw_subtree(root->right, depth + 1);
}


void draw_tree(Tree_ptr_c root) {
    printf("root: %ld\n", root->value);

    printf("l: ");
    draw_subtree(root->left, 1);

    printf("r: ");
    draw_subtree(root->right, 1);
}


size_t tree_depth(Tree_ptr_c root) {
    if (root == NULL)
        return 0;

    return MAX(tree_depth(root->left), tree_depth(root->right)) + 1;
}


size_t tree_size(Tree_ptr_c root) {
    if (root == NULL)
        return 0;

    return tree_size(root->left) + tree_size(root->right) + 1;
}


static void extract_values(Tree_ptr_c root, long ** array) {
    if (root == NULL)
        return;

//    printf("All right\n");
//    printf("%lu %lu\n", *array, *array+1);
//    printf("%ld %ld\n", **array, *(*array+1));

    extract_values(root->left, array);
    *((*array)++) = root->value;
    extract_values(root->right, array);
}


long* tree_to_array(Tree_ptr_c root) {
    long *array = (long*) malloc(sizeof(long) * tree_size(root));
    long *buf = array;

    extract_values(root, &buf);

    return array;
}


Tree_ptr copy_tree(Tree_ptr src) {
    if (src == NULL)
        return NULL;

    Tree_ptr dst = (Tree_ptr) malloc(sizeof(Tree));
    dst->value = src->value;
    dst->left = copy_tree(src->left);
    dst->right = copy_tree(src->right);

    return dst;
}


char trees_equal(Tree_ptr_c root1, Tree_ptr_c root2) {
    if (root1 == NULL && root2 == NULL)
        return 1;

    if (root1 == NULL && root2 != NULL || root1 != NULL && root2 == NULL)
        return 0;

//    now that we know both trees are not NULL, compare their values
    if (root1->value != root2->value)
        return 0;

//    if the values are equal, go to their children
    return (char)(trees_equal(root1->left, root2->left) && trees_equal(root1->right, root2->right));
}


char tree_valid(Tree_ptr_c root) {
    if (root == NULL)
        return 1;

    if (root->left != NULL && root->left->value > root->value)
        return 0;

    if (root->right != NULL && root->right->value < root->value)
        return 0;

    return (char)(tree_valid(root->left) && tree_valid(root->right));
}


Tree_ptr max_node_valid(Tree_ptr_c root) {
    if (root == NULL)
        return NULL;

    Tree_ptr p = (Tree_ptr)root;
    while (p->right != NULL)
        p = p->right;
    return p;
}


Tree_ptr min_node_valid(Tree_ptr_c root) {
    if (root == NULL)
        return NULL;

    Tree_ptr p = (Tree_ptr)root;
    while (p->left != NULL)
        p = p->left;
    return p;
}


Tree_ptr max_node_general(Tree_ptr_c root) {
    if (root == NULL)
        return NULL;

    if (root->left == NULL && root->right == NULL) {
        return (Tree_ptr)root;
    }

    Tree_ptr max_left = max_node_general(root->left), max_right = max_node_general(root->right);
    if (max_left != NULL && max_right == NULL) {
        return (max_left->value > root->value) ? max_left : (Tree_ptr)root;
    }

    if (max_left == NULL && max_right != NULL) {
        return (max_right->value > root->value) ? max_right : (Tree_ptr)root;
    }

    if (max_left->value > max_right->value && max_left->value > root->value)
        return max_left;

    if (max_right->value > max_left->value && max_right->value > root->value)
        return max_right;

    if (root->value > max_right->value && root->value > max_left->value)
        return (Tree_ptr)root;
}


Tree_ptr min_node_general(Tree_ptr_c root) {
    if (root == NULL)
        return NULL;

    Tree_ptr min_left = min_node_general(root->left), min_right = min_node_general(root->right);
    Tree_ptr res = (Tree_ptr) root;
    if (min_left != NULL && min_left->value < res->value)
        res = min_left;
    if (min_right != NULL && min_right->value < res->value)
        res = min_right;

    return res;
}
