//
// Created by Mikhail Tsaritsyn on 16.07.2021.
//

#ifndef MY_CLIB_COMMON_H
#define MY_CLIB_COMMON_H


#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

#define MIN3(a, b, c) (a < MIN(b, c) ? a : MIN(b, c))
#define MAX3(a, b, c) (a > MAX(b, c) ? a : MAX(b, c))


#endif //MY_CLIB_COMMON_H
