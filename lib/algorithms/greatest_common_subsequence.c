//
// Created by Mikhail Tsaritsyn on 19.10.2021.
//

#include "algorithms/greatest_common_subsequence.h"

//aliases for transition directions
#define LEFT 0
#define UP 1
#define UP_LEFT 2


//    TODO: replace trans with 2d array
array_int_ptr greatest_common_int_subsequence(const array_int* arr1, const array_int* arr2) {
//    we remember which of the given arrays is the shortest
    const array_int* short_array = (arr1->length < arr2->length) ? arr1 : arr2;
    const array_int* long_array = (arr1->length < arr2->length) ? arr2 : arr1;

//    we create two auxiliary arrays to store the intermediate gcs lengths
//    they must have the size of one of the given arrays, so we use the shortest one
    array_int_ptr previous_results = new_constant_array_int(short_array->length + 1, 0);
    array_int_ptr current_results = new_constant_array_int(short_array->length + 1, 0);

//    auxiliary transition matrix that will help us to restore the subsequences themselves by keeping the link
//    to the previous item
    char **trans = malloc(sizeof(char*) * (long_array->length + 1));
    unsigned long i, j;
    for (i = 0; i <= long_array->length; i++)
        trans[i] = malloc(sizeof(char) * (short_array->length + 1));

//    the main loop
    for (i = 1; i <= long_array->length; i++) {
        for (j = 1; j <= short_array->length; j++)
//            if the current elements of the given arrays are equal, we will include them in the gcs
//            in this case, the gcs consists of this value plus the gcs of the subarrays up to these elements
            if (long_array->elements[i - 1] == short_array->elements[j - 1]) {
                current_results->elements[j] = 1 + previous_results->elements[j - 1];
                trans[i][j] = UP_LEFT;
//            otherwise, the current gcs is the longest of two: if we remove the last element from the first array or
//            from the second one
            } else if (previous_results->elements[j] >= current_results->elements[j - 1]) {
                current_results->elements[j] = previous_results->elements[j];
                trans[i][j] = UP;
            } else {
                current_results->elements[j] = current_results->elements[j - 1];
                trans[i][j] = LEFT;
            }
        SWAP(array_int_ptr, previous_results, current_results)                                                 \
    }

//    restore the gcs from the transition matrix
    unsigned long resulting_length = previous_results->elements[previous_results->length - 1];
    delete_array_int(previous_results);
    delete_array_int(current_results);
    array_int_ptr result = new_empty_array_int(resulting_length);                                        \
    i = long_array->length;
    j = short_array->length;
    while(i > 0 && j > 0) {
        switch (trans[i][j]) {
//            this is the case when we had two equal elements, and now we add this value to the gcs
            case UP_LEFT:
                assert(long_array->elements[i-1] == short_array->elements[j-1]);
                array_int_append(result, long_array->elements[i-1]);
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

    for (i = 0; i <= long_array->length; i++)
        free(trans[i]);
    free(trans);

//    now the gsc is written in the reversed order, so we revert it
    revert_array_int(result);
    return result;
}


// the copy of the function above defined for an arbitrary datatype
#define implement_gcs_search(type) \
array_##type##_ptr greatest_common_##type##_subsequence(const array_##type* arr1, const array_##type* arr2) { \
    const array_##type* short_array = (arr1->length < arr2->length) ? arr1 : arr2;                       \
    const array_##type* long_array = (arr1->length < arr2->length) ? arr2 : arr1;                        \
                                   \
    array_##type##_ptr previous_results = new_constant_array_##type(short_array->length + 1, 0);              \
    array_##type##_ptr current_results = new_constant_array_##type(short_array->length + 1, 0);               \
                                   \
    char **trans = malloc(sizeof(char*) * (long_array->length + 1));                                   \
    unsigned long i, j;             \
    for (i = 0; i <= long_array->length; i++)                                                            \
        trans[i] = malloc(sizeof(char) * (short_array->length + 1));                                    \
                                   \
    for (i = 1; i <= long_array->length; i++) {                                                          \
        for (j = 1; j <= short_array->length; j++)                                                       \
            if (long_array->elements[i - 1] == short_array->elements[j - 1]) {                           \
                current_results->elements[j] = 1 + previous_results->elements[j - 1];                    \
                trans[i][j] = UP_LEFT;                                                                   \
            } else if (previous_results->elements[j] >= current_results->elements[j - 1]) {              \
                current_results->elements[j] = previous_results->elements[j];                            \
                trans[i][j] = UP;  \
            } else {               \
                current_results->elements[j] = current_results->elements[j - 1];                         \
                trans[i][j] = LEFT;\
            }                      \
                                   \
        SWAP(array_##type##_ptr, previous_results, current_results)                                                 \
    }                              \
                                   \
    unsigned long resulting_length = previous_results->elements[previous_results->length - 1];           \
    delete_array_##type(previous_results);                                                                  \
    delete_array_##type(current_results);                                                                   \
                                   \
    array_##type##_ptr result = new_empty_array_##type(resulting_length);                                        \
    i = long_array->length;        \
    j = short_array->length;       \
    while(i > 0 && j > 0) {        \
        switch (trans[i][j]) {     \
            case UP_LEFT:          \
                assert(long_array->elements[i-1] == short_array->elements[j-1]);                         \
                array_##type##_append(result, long_array->elements[i-1]);                                     \
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
    for (i = 0; i <= long_array->length; i++)                                                                 \
        free(trans[i]);            \
    free(trans);                   \
                                   \
    revert_array_##type(result);      \
    return result;                 \
}

implement_gcs_search(short)
implement_gcs_search(char)
implement_gcs_search(long)
implement_gcs_search(float)
implement_gcs_search(double)
implement_gcs_search(u_int)
implement_gcs_search(u_short)
implement_gcs_search(u_char)
implement_gcs_search(u_long)




