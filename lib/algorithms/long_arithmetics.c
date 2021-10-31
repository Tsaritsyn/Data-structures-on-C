//
// Created by Mikhail Tsaritsyn on 30.10.2021.
//

#include "algorithms/long_arithmetics.h"


LongNum* gcd_long_num(const LongNum* lnum1, const LongNum* lnum2) {
    if (lnum1 == NULL || lnum2 == NULL) return NULL;

    if (is_long_zero(lnum1) || is_long_zero(lnum2)) return new_long_zero();

    if (is_long_one(lnum1) || is_long_one(lnum2)) return new_long_num(1);

    LongNum* copy1 = copy_long_num(lnum1);
    copy1->sign = PLUS;
    LongNum* copy2 = copy_long_num(lnum2);
    copy2->sign = PLUS;


    while (!is_long_zero(copy1) && !is_long_zero(copy2)) {
        int relation = compare_long_num(copy1, copy2);
        if (relation > 0) reset_long_num(&copy1, mod_long_num(copy1, copy2));
        else reset_long_num(&copy2, mod_long_num(copy2, copy1));
    }

    add_to_long_num(&copy1, copy2);
    delete_long_num(copy2);
    return copy1;
}


LongNum* lcm_long_num(const LongNum* lnum1, const LongNum* lnum2) {
    const LongNum *greater = (compare_long_num(lnum1, lnum2) > 0) ? lnum1 : lnum2;
    const LongNum *smaller = (compare_long_num(lnum1, lnum2) > 0) ? lnum2 : lnum1;

    LongNum *gcd = gcd_long_num(lnum1, lnum2);
//    we divide the smaller number, because if it the gcd, we will get 1 here and the following multiplication will
//    become really simple
    LongNum *temp = div_long_num(smaller, gcd);
    delete_long_num(gcd);

    LongNum *lcm = mul_long_num(greater, temp);
    delete_long_num(temp);
    return lcm;
}


Pair* gcd_lcm_long_num(const LongNum* lnum1, const LongNum* lnum2) {
    const LongNum *greater = (compare_long_num(lnum1, lnum2) > 0) ? lnum1 : lnum2;
    const LongNum *smaller = (compare_long_num(lnum1, lnum2) > 0) ? lnum2 : lnum1;

    LongNum *gcd = gcd_long_num(lnum1, lnum2);
//    we divide the smaller number, because if it the gcd, we will get 1 here and the following multiplication will
//    become really simple
    LongNum *temp = div_long_num(smaller, gcd);

    LongNum *lcm = mul_long_num(greater, temp);
    delete_long_num(temp);
    return new_pair(gcd, lcm);
}


LongNum* long_factorial(size_t n) {
    if (n <= 1) return new_long_num(1);

    LongNum *previous = new_long_num(1);
    LongNum *result = NULL;

    size_t i;
    for (i = 1; i <= n; i++) {
        reset_long_num(&result, mul_long_num_and_positive_int(previous, i));
        reset_long_num(&previous, copy_long_num(result));
    }

    delete_long_num(previous);
    return result;
}


LongNum* newton_binome(size_t n, size_t k) {
    if (k > n) return new_long_zero();

    if (k == 0 || k == n) return new_long_num(1);

    size_t i;
    LongNum *result = new_long_num(1);
    size_t max = MAX(k, n-k);
    size_t min = MIN(k, n - k);
//    compute n! / max(k, n-k)!
    for (i = max + 1; i <= n; i++) reset_long_num(&result, mul_long_num_and_positive_int(result, i));
    LongNum *denom = long_factorial(min);
    reset_long_num(&result, div_long_num(result, denom));
    delete_long_num(denom);
    return result;
}
