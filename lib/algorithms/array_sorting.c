//
// Created by Mikhail Tsaritsyn on 22.10.2021.
//

#include "algorithms/array_sorting.h"


void ascending_sort_array_int(array_int_ptr arr, unsigned long left, unsigned long right) {
    if (left > arr->length || right > arr->length || left > right) {
        printf("Incorrect borders provided: %lu and %lu\n", left, right);
        return;
    }

    if (left + 1 >= right)
        return;

    int reference_value = arr->elements[left];
    unsigned long border_position = left;
    unsigned long i;
    for (i = left + 1; i < right; i++) {
        if (arr->compare_elements(arr->elements[i], reference_value) < 0) {
            SWAP(int, arr->elements[i], arr->elements[border_position])
            border_position++;
        }
    }

    if (border_position == left)
        border_position++;

    ascending_sort_array_int(arr, left, border_position);
    ascending_sort_array_int(arr, border_position, right);
}


void sort_datalist_ascending(DataList *dataList, size_t left, size_t right) {
    if (left > dataList->length || right > dataList->length || left > right) {
        printf("Incorrect borders provided: %lu and %lu\n", left, right);
        return;
    }

    if (left + 1 >= right)
        return;

    void* reference_value = dataList->elements[left];
    unsigned long border_position = left;
    unsigned long i;
    for (i = left + 1; i < right; i++) {
        if (dataList->compare_elements(dataList->elements[i], reference_value) < 0) {
            SWAP(void*, dataList->elements[i], dataList->elements[border_position])
            border_position++;
        }
    }

    if (border_position == left)
        border_position++;

    sort_datalist_ascending(dataList, left, border_position);
    sort_datalist_ascending(dataList, border_position, right);
}
