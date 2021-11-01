//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#include <stdio.h>

#include "my_clib.h"


int main() {

    LongNum *longNum = new_long_num_from_string("111111111111111111111111111111111");

    LongNum *pow = fast_exponent(longNum, 100);
    print_long_num(pow);
    printf("\n");

    delete_long_num(longNum);
    delete_long_num(pow);

    return 0;
}

