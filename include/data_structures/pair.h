//
// Created by Mikhail Tsaritsyn on 26.10.2021.
//

#ifndef MY_CLIB_PAIR_H
#define MY_CLIB_PAIR_H

#include <stdlib.h>


/**
 * This structure keeps a pair of pointers.
 */
typedef struct {
    void *first, *second;
} Pair;


/**
 * Creates a new pair that will store the given pointers.
 */
Pair* new_pair(void* first, void* second);


#endif //MY_CLIB_PAIR_H
