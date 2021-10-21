//
// Created by Mikhail Tsaritsyn on 19.10.2021.
//

#include "algorithms/greatest_common_subsequence.h"

//aliases for transition directions
#define LEFT 0
#define UP 1
#define UP_LEFT 2


//    TODO: replace trans with 2d array
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
        array_##type##_ptr temp = previous_results;                                                           \
        previous_results = current_results;                                                              \
        current_results = temp;    \
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
    free(trans);                   \
                                   \
    revert_array_##type(result);      \
    return result;                 \
}

implement_gcs_search(int)
implement_gcs_search(short)
implement_gcs_search(char)
implement_gcs_search(long)
implement_gcs_search(float)
implement_gcs_search(double)
implement_gcs_search(u_int)
implement_gcs_search(u_short)
implement_gcs_search(u_char)
implement_gcs_search(u_long)
