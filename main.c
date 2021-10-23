//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#include "my_clib.h"
#include "stdio.h"


int main() {
    array_int_ptr a = new_range_int(0, -10, 1);
    array_int_ptr b = new_range_int(1, 4, 2);

    print_array_int(a);
    printf("%lu, %lu\n", a->length, a->allocated_size);
    print_array_int(b);

    printf("%d\n", compare_array_int(a, b));

    delete_array_int(a);
    delete_array_int(b);

    return 0;
}

