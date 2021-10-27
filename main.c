//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#include <stdio.h>

#include "my_clib.h"


int main() {

    array_int* arr = new_constant_array(10, 1);
    array_float* arr1 = new_constant_array(10, 1.5f);
    array_double* arr2 = new_constant_array(10, 1.5);
    print_array(arr, " ", "\n");
    print_array(arr1, " ", "\n");
    print_array(arr2, " ", "\n");

    append_array(arr, 10);
    print_array(arr, " ", "\n");

    append_array(arr, 3.14);
    print_array(arr, " ", "\n");

    revert_array(arr);
    print_array(arr, " ", "\n");

    fill_array(arr, 200);
    print_array(arr, " ", "\n");

    array_float* arr3 = new_constant_array(11, 1.5f);
    print(are_arrays_equal(arr1, arr3), "\n");
    print(compare_array(arr1, arr3), "\n");

    array_double* arr4 = new_range(-1.5, 10.2, 1.7);
    print_array(arr4, " ", "\n");

    delete_array(arr);
    delete_array(arr1);
    delete_array(arr2);
    delete_array(arr3);
    delete_array(arr4);

    return 0;
}

