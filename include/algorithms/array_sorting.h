//
// Created by Mikhail Tsaritsyn on 22.10.2021.
//

#ifndef MY_CLIB_ARRAY_SORTING_H
#define MY_CLIB_ARRAY_SORTING_H

#include "data_structures/array.h"


void ascending_sort_array_int(array_int_ptr arr, unsigned long left, unsigned long right);


void sort_datalist_ascending(DataList *dataList, size_t left, size_t right,
                             int (*compare_elements)(const void *, const void *));


#endif //MY_CLIB_ARRAY_SORTING_H
