//
// Created by Mikhail Tsaritsyn on 16.07.2021.
//

#ifndef MY_CLIB_COMMON_H
#define MY_CLIB_COMMON_H

#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

#define MIN3(a, b, c) (a < MIN(b, c) ? a : MIN(b, c))
#define MAX3(a, b, c) (a > MAX(b, c) ? a : MAX(b, c))


/// maximum extra number of elements to be appended during concatenation
extern const unsigned long MAX_APPEND_LENGTH;


/// template function for numeric value comparison
#define declare_comparison_finction(type) int compare_##type(const type*, const type*);

declare_comparison_finction(int)
declare_comparison_finction(short)
declare_comparison_finction(char)
declare_comparison_finction(long)
declare_comparison_finction(float)
declare_comparison_finction(double)
declare_comparison_finction(u_int)
declare_comparison_finction(u_short)
declare_comparison_finction(u_char)
declare_comparison_finction(u_long)


/// formatting strings for all numeric values
#define format_int "%d"
#define format_u_int "%u"
#define format_char "%c"
#define format_u_char "%c"
#define format_short "%hd"
#define format_u_short "%hu"
#define format_long "%ld"
#define format_u_long "%lu"
#define format_float "%f"
#define format_double "%lf"


/// template function for printing numeric values
#define declare_print_value(type) void print_##type(type);

declare_print_value(int)
declare_print_value(short)
declare_print_value(char)
declare_print_value(long)
declare_print_value(float)
declare_print_value(double)
declare_print_value(u_int)
declare_print_value(u_short)
declare_print_value(u_char)
declare_print_value(u_long)


char* strupr(const char*);

#endif //MY_CLIB_COMMON_H
