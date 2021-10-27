//
// Created by Mikhail Tsaritsyn on 19.10.2021.
//

#include "algorithms/greatest_common_subsequence.h"

//aliases for transition directions
#define LEFT 0
#define UP 1
#define UP_LEFT 2


array_int_ptr greatest_common_int_subsequence(const array_int* arr1, const array_int* arr2) {
//    we remember which of the given arrays is the shortest
    const array_int* short_array = (arr1->length < arr2->length) ? arr1 : arr2;
    const array_int* long_array = (arr1->length < arr2->length) ? arr2 : arr1;

//    we create two auxiliary arrays to store the intermediate gcs lengths
//    they must have the size of one of the given arrays, so we use the shortest one
    array_u_long_ptr previous_results = new_constant_array(short_array->length + 1, 0UL);
    array_u_long_ptr current_results = new_constant_array(short_array->length + 1, 0UL);

//    auxiliary transition matrix that will help us to restore the subsequences themselves by keeping the link
//    to the previous item
    matrix_char_ptr trans = new_empty_matrix_char(long_array->length + 1);
    matrix_char_append_row(trans, new_constant_array_char(short_array->length + 1, -1));

//    the main loop
    unsigned long i, j;
    for (i = 1; i <= long_array->length; i++) {
        array_char_ptr cur_trans = new_empty_array_char(short_array->length + 1);
        append_to_array(cur_trans, -1);
        for (j = 1; j <= short_array->length; j++)
//            if the current elements of the given arrays are equal, we will include them in the gcs
//            in this case, the gcs consists of this value plus the gcs of the subarrays up to these elements
            if (long_array->elements[i - 1] == short_array->elements[j - 1]) {
                current_results->elements[j] = 1 + previous_results->elements[j - 1];
                append_to_array(cur_trans, UP_LEFT);
//            otherwise, the current gcs is the longest of two: if we remove the last element from the first array or
//            from the second one
            } else if (previous_results->elements[j] >= current_results->elements[j - 1]) {
                current_results->elements[j] = previous_results->elements[j];
                append_to_array(cur_trans, UP);
            } else {
                current_results->elements[j] = current_results->elements[j - 1];
                append_to_array(cur_trans, LEFT);
            }
        matrix_char_append_row(trans, cur_trans);
        SWAP(array_u_long_ptr, previous_results, current_results)
    }

//    get the length of the resulting gcs
    unsigned long resulting_length = previous_results->elements[previous_results->length - 1];
    delete_array(previous_results);
    delete_array(current_results);

//    restore the gcs from the transition matrix
    array_int_ptr result = new_empty_array_int(resulting_length);                                        \
    i = long_array->length;
    j = short_array->length;
    while(i > 0 && j > 0) {
        switch (trans->rows[i]->elements[j]) {
//            this is the case when we had two equal elements, and now we add this value to the gcs
            case UP_LEFT:
                assert(long_array->elements[i-1] == short_array->elements[j-1]);
                append_to_array(result, long_array->elements[i - 1]);
                i--; j--;
                break;
//            otherwise, we just follow the links until we meet the next equal-element situation or a matrix border
            case UP:
                i--;
                break;
            case LEFT:
                j--;
                break;
            default:
                break;
        }
    }

    delete_matrix(trans);

//    now the gsc is written in the reversed order, so we revert it
    revert_array(result);
    return result;
}


// the copy of the function above defined for an arbitrary datatype
#define implement_gcs_search(type) \
array_##type##_ptr greatest_common_##type##_subsequence(const array_##type* arr1, const array_##type* arr2) { \
    const array_##type* short_array = (arr1->length < arr2->length) ? arr1 : arr2;                       \
    const array_##type* long_array = (arr1->length < arr2->length) ? arr2 : arr1;                        \
                                   \
    array_u_long_ptr previous_results = new_constant_array(short_array->length + 1, 0UL);\
    array_u_long_ptr current_results = new_constant_array(short_array->length + 1, 0UL);               \
                                   \
    matrix_char_ptr trans = new_empty_matrix_char(long_array->length + 1);\
    matrix_char_append_row(trans, new_constant_array_char(short_array->length + 1, -1));                      \
    \
    unsigned long i, j;             \
    for (i = 1; i <= long_array->length; i++) {\
        array_char_ptr cur_trans = new_empty_array_char(short_array->length + 1);\
        append_to_array(cur_trans, -1);\
        for (j = 1; j <= short_array->length; j++) {\
            if (long_array->elements[i - 1] == short_array->elements[j - 1]) {\
                current_results->elements[j] = 1 + previous_results->elements[j - 1];\
                append_to_array(cur_trans, UP_LEFT);\
            } else if (previous_results->elements[j] >= current_results->elements[j - 1]) {\
                current_results->elements[j] = previous_results->elements[j];\
                append_to_array(cur_trans, UP);\
            } else {\
                current_results->elements[j] = current_results->elements[j - 1];\
                append_to_array(cur_trans, LEFT);\
            }                      \
        }                       \
        matrix_char_append_row(trans, cur_trans);\
        SWAP(array_u_long_ptr, previous_results, current_results)\
    }\
                                   \
    unsigned long resulting_length = previous_results->elements[previous_results->length - 1];           \
    delete_array(previous_results);                                                                  \
    delete_array(current_results);                                                                   \
                                   \
    array_##type##_ptr result = new_empty_array_##type(resulting_length);                                        \
    i = long_array->length;        \
    j = short_array->length;       \
    while(i > 0 && j > 0) {        \
        switch (trans->rows[i]->elements[j]) {     \
            case UP_LEFT:          \
                assert(long_array->elements[i-1] == short_array->elements[j-1]);                         \
                append_to_array(result, long_array->elements[i-1]);                                     \
                i--; j--;          \
                break;             \
            case UP:               \
                i--;               \
                break;             \
            case LEFT:             \
                j--;               \
                break;             \
            default:               \
                break;             \
        }                          \
    }                              \
    delete_matrix(trans);                 \
                                   \
    revert_array(result);      \
    return result;                 \
}

implement_gcs_search(short)
implement_gcs_search(char)
implement_gcs_search(long)
implement_gcs_search(float)
implement_gcs_search(double)
implement_gcs_search(u_int)
implement_gcs_search(u_short)
implement_gcs_search(u_long)




