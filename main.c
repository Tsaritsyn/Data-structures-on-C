//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#include <stdio.h>

#include "my_clib.h"


int main() {

    LongNum* lnum1 = new_long_num_from_string("123456789123456789");
    LongNum* lnum2 = new_long_num_from_string("987654321");

    LongNum* gcd = gcd_long_num(lnum1, lnum2);
    printf("gcd = ");
    print_long_num(gcd);
    printf("\n");
    LongNum* lcm = lcm_long_num(lnum1, lnum2);
    printf("lcm = ");
    print_long_num(lcm);
    printf("\n");

    delete_long_num(lnum1);
    delete_long_num(lnum2);
    delete_long_num(gcd);

    return 0;
}

