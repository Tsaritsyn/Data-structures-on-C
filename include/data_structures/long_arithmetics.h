//
// Created by Mikhail Tsaritsyn on 27.10.2021.
//

#ifndef MY_CLIB_LONG_ARITHMETICS_H
#define MY_CLIB_LONG_ARITHMETICS_H

#include <assert.h>

#include "array.h"
#include "pair.h"

#define BASE 1000000000
#define BASE_LENGTH 9
#define NUM_DIGITS_IN_LONG_LONG 3

enum {MINUS = -1, PLUS = 1, ZERO = 0};


/**
 * The digits are stored in BASE-ish system. The BASE is such that it is close to MAX_INT, and its square is less than
 * LLONG_MAX. So, we will always be able to store the result of multiplication of digits into a long long buffer and
 * catch overflows.
 *
 * Moreover, since the BASE is a multiple of 10, no special conversion to decimal system is required when printing a
 * long number.
 *
 * The digits are stored in a big-endian format, meaning that the first digit corresponds to 0th power of BASE.
 */
typedef struct LongNum {
    int sign;
    array_u_int* digits;
} LongNum;


/**
 * @return pointer to a new long number equals to zero
 */
LongNum* new_long_zero();


/**
 * @return pointer to a new long number equal to a given value
 */
LongNum* new_long_num(long long value);


LongNum* new_long_num_from_string(const char* literal);


void delete_long_num(LongNum* lnum);


/// Deletes the previous value of the dst and sets it to the given number. When the dst will be next deleted, the src
/// will be deleted, too.
void reset_long_num(LongNum **dst, LongNum *src);


LongNum* copy_long_num(const LongNum* lnum);


void print_long_num(const LongNum* lnum);


/**
 * @return sum of two long numbers
 */
LongNum* add_long_num(const LongNum* lnum1, const LongNum* lnum2);


/**
 * @return subtraction of two long numbers
 */
LongNum* sub_long_num(const LongNum* lnum1, const LongNum* lnum2);


/**
 * @return multiplication of two long numbers
 */
LongNum* mul_long_num(const LongNum* lnum1, const LongNum* lnum2);


LongNum* mul_long_num_and_positive_int(const LongNum* lnum, unsigned int digit);


/**
 * @return integer division of two long numbers
 */
LongNum* div_long_num(const LongNum* nom, const LongNum* denom);


/**
 * @return remainder of the integer division of two long numbers
 */
LongNum* mod_long_num(const LongNum* nom, const LongNum* denom);


/**
 * Computes the result of the integer division of the two given long numbers along with the modulo value.
 *
 * @return pair containing the pointer to the division result in the first field, and the pointer to the modulo in the
 *  second one
 */
Pair* divmod_long_num(const LongNum* nom, const LongNum* denom);


/**
 * In-place addition of two long numbers long integer. The result is written to the first one
 */
void add_to_long_num(LongNum **lnum1, const LongNum* lnum2);


void add_positive_int_to_long_num(LongNum** lnum, unsigned int num);


/**
 * In-place subtraction of the second long number from the first one. The result is written to the first one
 */
void sub_from_long_num(LongNum **lnum1, const LongNum* lnum2);


void sub_positive_int_from_long_num(LongNum** lnum, unsigned int num);


/**
 * Multiplies the given long number with BASE^shift.
 */
void long_shift_left(LongNum **lnum, size_t shift);


/**
 * @return -1 if the first long number is less, 1 if greater than the second and 0 if they are equal
 */
int compare_long_num(const LongNum* lnum1, const LongNum* lnum2);


/**
 * @return 1 if the given long number is a zero of a NULL, and 0 otherwise
 */
int is_long_zero(const LongNum* lnum);


/**
 * @return 1 if the given long number's absolute value is one, and 0 otherwise
 */
int is_long_one(const LongNum* lnum);


#endif //MY_CLIB_LONG_ARITHMETICS_H
