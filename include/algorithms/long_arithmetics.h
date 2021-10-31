//
// Created by Mikhail Tsaritsyn on 30.10.2021.
//

#ifndef MY_CLIB_LONG_ARITHMETICS_H
#define MY_CLIB_LONG_ARITHMETICS_H


#include "data_structures/long_number.h"


/**
 * @return the greatest common divider of two long numbers
 */
LongNum* gcd_long_num(const LongNum* lnum1, const LongNum* lnum2);


/**
 * @return the least common multiple of two long numbers
 */
LongNum* lcm_long_num(const LongNum* lnum1, const LongNum* lnum2);


/**
 * @return pair of pointer to GCD in the first, to LCM in the second
 */
Pair* gcd_lcm_long_num(const LongNum* lnum1, const LongNum* lnum2);


LongNum* long_factorial(size_t n);


/**
 * Computes the number of combinations of k elements out of n.
 *
 * @return n! / k! / (n-k)! if k <= n, otherwise 0
 */
LongNum* newton_binome(size_t n, size_t k);


#endif //MY_CLIB_LONG_ARITHMETICS_H
