//
// Created by Mikhail Tsaritsyn on 30.10.2021.
//

#include "algorithms/long_arithmetics.h"
#include "algorithms/addition_chain.h"


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

    add_to_long_num(copy1, copy2);
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

    LongNum *result = new_long_num(1);

    size_t i;
    for (i = 1; i <= n; i++)
        mul_long_num_by_positive_int(result, i);
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
    for (i = max + 1; i <= n; i++) mul_long_num_by_positive_int(result, i);

    LongNum *denom = long_factorial(min);
    reset_long_num(&result, div_long_num(result, denom));
    delete_long_num(denom);
    return result;
}


LongNum* fast_exponent(const LongNum* longNum, size_t power) {
    if (longNum == NULL) return NULL;

    if (power == 0) return new_long_num(1);
    else if (power == 1) return copy_long_num(longNum);

    if (is_long_zero(longNum)) return new_long_zero();

//    if the power is too high, it consumes extremely much memory for chain search, so we use the square root approach instead
//    since memory consumption is sublinear, this division will be more efficient
    if (power > 200) {
        LongNum *result_sqrt = fast_exponent(longNum, power / 2);
        LongNum *result = mul_long_num(result_sqrt, result_sqrt);

//        if the power is odd, we need to multiply with the given number one more time
        if (power % 2 != 0) mul_long_num_by(result, longNum); //reset_long_num(&result, mul_long_num(result, longNum));
        delete_long_num(result_sqrt);
        return result;
    }

    array_size_t *intermediate_powers = addition_chain(power);
//    print_array(intermediate_powers, ", ", "\n");
    assert(intermediate_powers->elements[0] == 1);
    assert(intermediate_powers->elements[intermediate_powers->length - 1] == power);

    DataList *intermediate_results = new_empty_datalist(
            intermediate_powers->length, &delete_long_num);
//    th first power is always equal to the number itself
    append_to_datalist(intermediate_results, copy_long_num(longNum));

    size_t i;
    for (i = 1; i < intermediate_powers->length; i++) {
//        determine which power to use to get the current intermediate result from the previous one
        size_t diff = intermediate_powers->elements[i] - intermediate_powers->elements[i-1];
//        the intermediate_powers is constructed in such way that diff is always present somewhere earlier in the
//        array, and therefore the result for it is already computed
        size_t prev_ind;
        for (prev_ind = 0; prev_ind < intermediate_powers->length && intermediate_powers->elements[prev_ind] != diff; prev_ind++);

        append_to_datalist(
                intermediate_results, mul_long_num(intermediate_results->elements[i-1], intermediate_results->elements[prev_ind])
                );
    }

    LongNum *result = copy_long_num(intermediate_results->elements[intermediate_results->length - 1]);
    delete_array(intermediate_powers);
    delete_datalist(intermediate_results);
    return result;
}



