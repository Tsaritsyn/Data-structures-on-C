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


extern const u_int64_t max_possible_value;
extern const char* max_short_literal;


#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define MIN3(a, b, c) (((a) < MIN(b, c)) ? (a) : MIN(b, c))
#define MAX3(a, b, c) (((a) > MAX(b, c)) ? (a) : MAX(b, c))

#define SWAP(type, a, b) {type temp = a; a = b; b = temp;}

typedef long long l_long;
typedef unsigned long long ul_long;
typedef long double l_double;


/// maximum extra number of elements to be appended during concatenation
extern const unsigned long MAX_APPEND_LENGTH;


/// template function for numeric value comparison
#define declare_comparison_function(type) int compare_##type(type, type);

declare_comparison_function(int)
declare_comparison_function(short)
declare_comparison_function(char)
declare_comparison_function(long)
declare_comparison_function(float)
declare_comparison_function(double)
declare_comparison_function(u_int)
declare_comparison_function(u_short)
declare_comparison_function(u_char)
declare_comparison_function(u_long)
declare_comparison_function(size_t)


/**
 * Comparison of any values for which the operators <, >, == are defined.
 *
 * @return 1 if a > b, -1 if a < b and 0 if a == b
 */
#define compare_numerical(a, b) (((a) > (b)) ? 1 : ((a) < (b) ? -1 : 0))


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
#define format_size_t "%lu"


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
declare_print_value(size_t)


/**
 * Prints the given value based on its type.
 *
 * @param _end will be put to the end of the print
 */
#define print(x, _end) printf(_Generic (x, \
short: "%hd",         \
int: "%d",         \
long: "%ld",       \
long long: "%lld", \
unsigned short: "%hu",\
unsigned int: "%u",   \
unsigned long: "%lu", \
unsigned long long: "%llu", \
char: "%c",      \
unsigned char: "%c",\
float: "%f",     \
double: "%lf",   \
long double: "%Lf",   \
char*: "%s",                               \
const char*: "%s"\
), x);\
printf("%s", _end)


char* strupr(const char*);


/**
 * @return 1 if the given string consists only of decimal digits with possible leading '+' or '-', 0 otherwise
 */
int is_int_literal(const char* literal);




#endif //MY_CLIB_COMMON_H
