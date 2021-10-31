//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#include <stdio.h>

#include "my_clib.h"


int main() {

    DataList *fib = get_all_fibonacci(1000);

    print_datalist(fib);
    printf("\n");

    delete_datalist(fib);

    return 0;
}

