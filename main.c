//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#include <stdio.h>

#include "my_clib.h"


int main() {

    print(10, "\n");
    print(1.5, "\n");

    array_int* arr_int = new_constant_array_int(10, 1);
    array_float* arr_f = new_constant_array_float(5, 2.5f);

    print_array(arr_int, "\n");
    print_array(arr_f, "\n");

    delete_array(arr_int);
    delete_array(arr_f);


    return 0;
}

