//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#include <stdio.h>

#include "my_clib.h"


int main() {

    Decimal* decimal = new_decimal_inf(-1);

    print_decimal(decimal);

    delete_decimal(decimal);

    return 0;
}

