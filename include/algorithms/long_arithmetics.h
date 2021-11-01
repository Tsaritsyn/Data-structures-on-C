//
// Created by Mikhail Tsaritsyn on 30.10.2021.
//

#ifndef MY_CLIB_LONG_ARITHMETICS_H
#define MY_CLIB_LONG_ARITHMETICS_H


#include "data_structures/long_number.h"
#include "data_structures/queue.h"
#include "algorithms/addition_chain.h"


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


/**
 * Computes the intermediate powers needed to compute the given one.
 *
 * @example
 *  Suppose we need to compute x^15. We can do it in three ways.
 *  1. Just multiply the current result by x in a loop starting from 1
 *  2. Use binary decomposition of the power to reduce the number of multiplications:
 *      x^15 = x^14 * x;
 *      x^14 = x^12 * x^2;
 *      x^12 = x^8 * x^4;
 *      x^8 = x^4 * x^4;
 *      x^4 = x^2 * x^2;
 *      x^2 = x * x.
 *  It allows us to reduce the number of multiplications from 15 for a loop to only 6! However, we will have to store 5
 *  intermediate powers or recompute them every time.
 *  3. Use another decomposition:
 *      x^15 = x^10 * x^5;
 *      x^10 = x^5 * x^5;
 *      x^5 = x^3 * x^2;
 *      x^3 = x^2 * x;
 *      x^2 = x * x.
 *  It allows us to reduce the number of multiplications even further: to only 5, while storing the same 5 intermediate
 *  powers!
 *
 *  This function gives the intermediate powers needed for the third method. In our example it will return an array
 *  [1, 2, 3, 5, 10, 15] for an input 15. Note, that the solution is not unique, and [1, 2, 3, 6, 12, 15] is an
 *  equivalent one.
 *
 * @cite See https://www.youtube.com/watch?v=BfNlzdFa_a4 for more details.
 *
 */
LongNum* fast_exponent(const LongNum* longNum, size_t power);


#endif //MY_CLIB_LONG_ARITHMETICS_H
