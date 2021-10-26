//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#include "data_structures/BS_tree.h"
#include "limits.h"


Tree_ptr new_node(long value) {
    Tree_ptr node = malloc(sizeof(Tree));
    node->left = NULL;
    node->right = NULL;
    node->value = value;
    return node;
}


// the second argument has type "long" because va_start operates with 16-bit chunks
Tree_ptr find_node(Tree_ptr_c root, long value, long get_parent, ...) {
    Tree_ptr node = (Tree_ptr)root;

//    if we do not need to keep the parent
    if (!get_parent) {
        if (root == NULL)
            return NULL;

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

        if (root == NULL) {
            va_end(ap);
            return NULL;
        }

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


int tree_insert_value(Tree_ptr root, long value) {
    Tree_ptr parent = NULL, node = NULL;
    node = find_node(root, value, 1, &parent);

//    the value is already present in the tree
    if (node != NULL)
        return 0;

    if (parent == NULL) {
        printf("Error in tree_insert_value: could not find neither node containing this value nor its parent.\n");
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
    size_t i;
    for (i = 1; i < size; i++)
        tree_insert_value(root, array[i]);
    return root;
}


void print_tree(Tree_ptr_c root) {
    if (root == NULL)
        return;

    print_tree(root->left);
    printf("%ld ", root->value);
    print_tree(root->right);
}


static void draw_subtree(Tree_ptr_c root, unsigned int depth) {
    size_t i;
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
    if (root == NULL) {
        printf("NULL\n");
        return;
    }

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

    extract_values(root->left, array);
    *((*array)++) = root->value;
    extract_values(root->right, array);
}


long* tree_to_array(Tree_ptr_c root) {
    if (root == NULL)
        return NULL;

    long *array = (long*) malloc(sizeof(long) * tree_size(root));
    long *buf = array;

    extract_values(root, &buf);

    return array;
}


Tree_ptr copy_tree(Tree_ptr_c src) {
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

//    the tree is not valid if minimal value of the right subtree is less than the node value
    Tree_ptr min_right = min_node_general(root->right);
    if (min_right != NULL && min_right->value <= root->value)
        return 0;

//    the same if maximal value of the left subtree exceeds the node value
    Tree_ptr max_left = max_node_general(root->left);
    if (max_left != NULL && max_left->value >= root->value)
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

    Tree_ptr max_left = max_node_general(root->left), max_right = max_node_general(root->right);
    Tree_ptr res = (Tree_ptr) root;
    if (max_left != NULL && max_left->value > res->value)
        res = max_left;
    if (max_right != NULL && max_right->value > res->value)
        res = max_right;

    return res;
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


static void replace_with(Tree_ptr node1, Tree_ptr node2) {
    if (node1 == NULL || node2 == NULL) {
        printf("Error in replace_with: one of the nodes is NULL.\n");
        return;
    }

    node1->value = node2->value;
    node1->left = node2->left;
    node1->right = node2->right;

    node2->right = NULL;
    node2->left = NULL;
    delete_tree(node2);
}


int remove_value(Tree_ptr root, long value) {
    if (root == NULL)
        return 0;

    Tree_ptr parent = NULL;
    Tree_ptr node = find_node(root, value, 1, &parent);

//    if there is no such value, do nothing
    if (node == NULL)
        return 0;

//    if the node has no children, just remove it
    if (node->left == NULL && node->right == NULL) {
//        if there is no parent, then the node is a root, and since it has no children, the tree set_contains of it only,
//        so we cannot delete it
        if (parent == NULL)
            return 0;

//        otherwise, it's simply a leaf
        delete_tree(node);
        if (value < parent->value)
            parent->left = NULL;
        else
            parent->right = NULL;
    }
//        if both children are present, replace the node with the minimal node of its right subtree
    else if (node->left != NULL && node->right != NULL) {
        Tree_ptr min_right = min_node_general(node->right);
//            transfer right subtree of the min successor to the current node
        node->right = min_right->right;
        min_right->right = NULL;
//            copy the value and the counter
        node->value = min_right->value;

//            delete the former minimum successor
        min_right->right = NULL;
        delete_tree(min_right);
    }
//        if the node has only one child, replace the node with it
    else {
        if (node->left != NULL)
            replace_with(node, node->left);
        else
            replace_with(node, node->right);
    }

    return 1;
}


char trees_equivalent(Tree_ptr_c root1, Tree_ptr_c root2) {
    if (root1 == NULL && root2 == NULL)
        return 1;

    if (tree_depth(root1) != tree_depth(root2))
        return 0;

//    now that we know that at least one is not NULL, start real check
    size_t size1 = tree_size(root1), size2 = tree_size(root2);
    if (size1 != size2)
        return 0;

//    now we know that both trees have the same size, so we can check their values
    long *values = tree_to_array(root1);
    size_t i;
    char res = 1;
    for (i = 0; i < size1; i++)
        if (find_node(root2, values[i], 0) == NULL) {
            res = 0;
            break;
        }

    free(values);
    return res;
}


/// swaps the node with its right neighbour
static Tree_ptr turn_left(Tree_ptr node) {
    if (node->right == NULL) {
        printf("Error in turn_left: the right node is NULL.\n");
        return node;
    }

    Tree_ptr new_node = node->right;
    node->right = new_node->left;
    new_node->left = node;
    return new_node;
}


/// swaps the node with its left neighbour
static Tree_ptr turn_right(Tree_ptr node) {
    if (node->left == NULL) {
        printf("Error in turn_right: the left node is NULL.\n");
        return node;
    }

    Tree_ptr new_node = node->left;
    node->left = new_node->right;
    new_node->right = node;
    return new_node;
}


Tree_ptr balance_tree(Tree_ptr root) {
    if (root == NULL)
        return NULL;

    unsigned int ld = tree_depth(root->left);
    unsigned int rd = tree_depth(root->right);

//    it's a leaf or its children are leaves, there is nothing to balance
    if (ld <= 1 && rd <= 1)
        return root;

//    rotate the tree until its depths become almost equal
    if (ld >= rd + 1)
        while (ld >= rd + 1) {
            root = turn_right(root);
            ld--;
            rd++;
        }
    else
        while (rd >= ld + 1) {
            root = turn_left(root);
            rd--;
            ld++;
        }

    root->left = balance_tree(root->left);
    root->right = balance_tree(root->right);

    return root;
}


long max_tree_value(Tree_ptr_c root) {
    Tree_ptr max_node = max_node_valid(root);
    if (max_node == NULL)
        return LONG_MIN;

    return max_node->value;
}


long min_tree_value(Tree_ptr_c root) {
    Tree_ptr min_node = min_node_valid(root);
    if (min_node == NULL)
        return LONG_MAX;

    return min_node->value;
}


/**
 * Merges two given arrays into a new one. If the arrays are sorted in the ascending order, the new one will be sorted,
 * too. The size of the resulting array is the sum of input sizes, because repeated values are preserved.
 *
 * @param a1 pointer to the first array
 * @param size1 size of the first array
 * @param a2 pointer to the second array
 * @param size2 size of the second array
 * @return pointer to the resulting array
 */
static long* merge_sorted_arrays(const long *a1, size_t size1, const long *a2, size_t size2) {
    size_t i = 0, j = 0, k = 0;

    long *res = malloc(sizeof(long) * (size1 + size2));
//    the algo is the following: each step we choose from the current values of two arrays the smallest one, write it
//    into the resulting one and then move to the next value in the array from where we took it
    while (i < size1 || j < size2) {
        if (i < size1 && j < size2) {
            if (a1[i] < a2[j])
                res[k++] = a1[i++];
            else
                res[k++] = a2[j++];
        }
//        once we reach the end of one of the arrays, we don't have to choose anymore
        else if (i == size1)
            res[k++] = a2[j++];
        else
            res[k++] = a1[i++];
    }

    return res;
}


Tree_ptr new_balanced_tree(const long *values, size_t size) {
    if (values == NULL || size == 0)
        return NULL;

    Tree_ptr root = new_node(values[size / 2]);
    if (size == 1)
        return root;

//    we ensure that the value we've put in the root will never be taken again
//    TODO: implement it via binary search
    size_t left_end = size / 2;
    while (left_end > 0 && (values[left_end] == root->value))
        left_end--;

    size_t right_begin = size / 2 + 1;
    while (right_begin < size && values[right_begin] == root->value) {
        right_begin++;
    }

    root->left = new_balanced_tree(values, left_end + 1);
    root->right = new_balanced_tree(values + right_begin, size - right_begin);
    return root;
}


Tree_ptr merge_balanced_trees(Tree_ptr_c root1, Tree_ptr_c root2) {
    if (root1 == NULL && root2 == NULL)
        return NULL;

    if (root1 == NULL)
        return copy_tree(root2);

    if (root2 == NULL)
        return copy_tree(root1);

    size_t size1 = tree_size(root1), size2 = tree_size(root2);
    long *values1 = tree_to_array(root1);
    long *values2 = tree_to_array(root2);
    long *values_common = merge_sorted_arrays(values1, size1, values2, size2);
    Tree_ptr res = new_balanced_tree(values_common, size1 + size2);

    free(values1);
    free(values2);
    free(values_common);
    return res;
}
