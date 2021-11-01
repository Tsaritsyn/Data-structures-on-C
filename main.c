//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#include <stdio.h>

#include "my_clib.h"


int main() {

    LongNum *longNum = long_factorial(100);

    print_long_num(longNum);
    printf("\n");

    reset_long_num(&longNum, newton_binome(100, 50));
    print_long_num(longNum);
    printf("\n");

    delete_long_num(longNum);

    return 0;
}

