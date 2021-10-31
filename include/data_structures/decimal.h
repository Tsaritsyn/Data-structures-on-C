//
// Created by Mikhail Tsaritsyn on 30.10.2021.
//

#ifndef MY_CLIB_DECIMAL_H
#define MY_CLIB_DECIMAL_H

#include "long_number.h"
#include "algorithms/long_arithmetics.h"
#include "string.h"
#include "algorithms/fast_substring_search.h"


typedef struct Decimal {
    LongNum *nom, *denom;
} Decimal;


Decimal* new_decimal(LongNum* nom, LongNum* denom);


/**
 * Will store the copies of the given long numbers.
 */
Decimal* new_decimal_from_copies(const LongNum *nom, const LongNum *denom);


Decimal* new_decimal_from_strings(const char* nom_literal, const char* denom_literal);


Decimal* copy_decimal(const Decimal *decimal);


void delete_decimal(Decimal* decimal);


void print_decimal(const Decimal* decimal);


Decimal* new_decimal_inf(int sign);


Decimal* new_decimal_zero(void);


Decimal* new_decimal_nan(void);


int is_decimal_inf(const Decimal *decimal);


int is_decimal_zero(const Decimal *decimal);


int is_decimal_nan(const Decimal *decimal);


int compare_decimal(const Decimal *decimal1, const Decimal *decimal2);


Decimal* add_decimal(const Decimal *decimal1, const Decimal *decimal2);


Decimal* sub_decimal(const Decimal *decimal1, const Decimal *decimal2);


Decimal* mul_decimal(const Decimal *decimal1, const Decimal *decimal2);


Decimal* div_decimal(const Decimal *nom, const Decimal *denom);


/**
 * Print decimal number in floating point notation. If the decimal fraction is periodic, the print will stop as soon as
 * the period is detected and "..." will be printed at the end of it.
 *
 * The last digit of the number is not rounded, but printed without taking the next one into account
 *
 * @param max_precision if the length of the part after the dot exceeds this limit, the print will stop
 */
void print_decimal_as_float(const Decimal *decimal, size_t max_precision);


#endif //MY_CLIB_DECIMAL_H
