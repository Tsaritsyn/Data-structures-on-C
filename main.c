//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#include <stdio.h>

#include "my_clib.h"


int main() {

    LongNum* lnum1 = new_long_num_from_string("0000000000000000000000000000000000000000000000001");
    LongNum* lnum2 = new_long_num_from_string("0000000000000000001");

    print(compare_long_num(lnum1, lnum2), "\n");

    delete_long_num(lnum1);
    delete_long_num(lnum2);

    return 0;
}

