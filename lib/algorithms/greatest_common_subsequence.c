//
// Created by Mikhail Tsaritsyn on 19.10.2021.
//

#include "algorithms/greatest_common_subsequence.h"

//aliases for transition directions
#define LEFT 0
#define UP 1
#define UP_LEFT 2


array_int_ptr greatest_common_subsequence(const array_int* arr1, const array_int* arr2) {
//    TODO: replace temp with two switching arrays
//    create a matrix for temporary results
    unsigned long **temp = malloc(sizeof(unsigned long*) * (arr1->length + 1));
    unsigned int i, j;
    for (i = 0; i <= arr1->length; i++)
        temp[i] = malloc(sizeof(unsigned long) * (arr2->length + 1));

//    initialize it with border values, given that if any of the arrays is empty, the common sequence is empty as well
    for (i = 0; i <= arr1->length; i++)
        temp[i][0] = 0;
    for (j = 0; j <= arr2->length; j++)
        temp[0][j] = 0;

//    creating a temporary matrix for transitions
//    we do not initialize its border values, because we will stop when reach them, so they do not matter
    short **trans = malloc(sizeof(short*) * (arr1->length + 1));
    for (i = 0; i <= arr1->length; i++)
        trans[i] = malloc(sizeof(short) * (arr2->length + 1));

//    start the algorithm
    for (i = 1; i <= arr1->length; i++)
        for (j = 1; j <= arr2->length; j++)
            if (arr1->elements[i - 1] == arr2->elements[j - 1]) {
                temp[i][j] = temp[i - 1][j - 1] + 1;
                trans[i][j] = UP_LEFT;
            } else if (temp[i - 1][j] >= temp[i][j - 1]) {
                temp[i][j] = temp[i - 1][j];
                trans[i][j] = UP;
            } else {
                temp[i][j] = temp[i][j - 1];
                trans[i][j] = LEFT;
            }

    i = arr1->length;
    j = arr2->length;
    unsigned long resulting_length = temp[i][j];
    array_int_ptr result = new_empty_array_int(resulting_length);
    while(i > 0 && j > 0) {
        switch (trans[i][j]) {
            case UP_LEFT:
                assert(arr1->elements[i-1] == arr2->elements[j-1]);
                array_int_append(result, arr1->elements[i-1]);
                i--; j--;
                break;
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

    revert_array_int(result);

    for (i = 0; i <= arr1->length; i++) {
        free(temp[i]);
        free(trans[i]);
    }
    free(temp);
    free(trans);

    return result;
}
