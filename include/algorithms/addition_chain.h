//
// Created by Mikhail Tsaritsyn on 01.11.2021.
//

#ifndef MY_CLIB_ADDITION_CHAIN_H
#define MY_CLIB_ADDITION_CHAIN_H

#include "algorithms/long_arithmetics.h"
#include "algorithms/addition_chain.h"

/**
 * Computes a minimal addition chain from 1 to the given number. Addition chain is the sequence of numbers such that
 * the difference between any neighboring ones is already present in the chain.
 *
 * @example
 *  such chains as [1], [1, 2], [1, 2, 3], [1, 2, 4], [1, 2, 3, 5, 10, 15, 25, 50] are addition chains.
 *
 */
array_size_t* addition_chain(size_t n);


#endif //MY_CLIB_ADDITION_CHAIN_H
