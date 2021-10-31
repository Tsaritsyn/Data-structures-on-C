//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#include <stdio.h>

#include "my_clib.h"


int main() {

    Decimal *decimal = new_decimal_from_strings("9", "12");

    print_decimal_as_float(decimal, 200);
    printf("\n");

    delete_decimal(decimal);


//    decimal = new_decimal_from_strings("987654321987654321", "-12345");
//
//    print_decimal_as_float(decimal);
//    printf("\n");
//
//    delete_decimal(decimal);

    return 0;
}

