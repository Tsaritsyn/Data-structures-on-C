//
// Created by Mikhail Tsaritsyn on 31.10.2021.
//

#ifndef MY_CLIB_FIBONACCI_H
#define MY_CLIB_FIBONACCI_H

#include "data_structures/long_number.h"
#include "data_structures/array.h"


/**
 * @return array of LongNum* containing n first Fibonacci numbers
 */
DataList* get_all_fibonacci(size_t n);


#endif //MY_CLIB_FIBONACCI_H
