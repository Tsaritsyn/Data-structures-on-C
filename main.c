//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#include <stdio.h>

#include "my_clib.h"


int main() {

//    LongNum *fact = long_factorial(1000);
//    print_long_num(fact);
//    printf("\n");
//    delete_long_num(fact);

    LongNum* cnk = newton_binome(100, 50);
    print_long_num(cnk);
    printf("\n");
    delete_long_num(cnk);

    return 0;
}

