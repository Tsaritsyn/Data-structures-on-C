//
// Created by Mikhail Tsaritsyn on 18.10.2021.
//

#include "common.h"


const unsigned long MAX_APPEND_LENGTH = 1024;


/// template function for numeric value comparison
#define numeric_comparison_function(type) \
int compare_##type(const type a, const type b) { \
    if (a > b) return 1; \
    else if (a < b) return -1; \
    else return 0; \
}

numeric_comparison_function(int)
numeric_comparison_function(short)
numeric_comparison_function(char)
numeric_comparison_function(long)
numeric_comparison_function(float)
numeric_comparison_function(double)
numeric_comparison_function(u_int)
numeric_comparison_function(u_short)
numeric_comparison_function(u_char)
numeric_comparison_function(u_long)
numeric_comparison_function(size_t)


/// template function for printing numeric values
#define print_value(type) \
void print_##type(type value) {      \
    printf(format_##type, value);    \
}

print_value(int)
print_value(short)
print_value(char)
print_value(long)
print_value(float)
print_value(double)
print_value(u_int)
print_value(u_short)
print_value(u_char)
print_value(u_long)
print_value(size_t)


char* strupr(const char* s) {
    unsigned long len_s = strlen(s);
    char* res = malloc(len_s + 1);
    unsigned long i;
    for (i = 0; i < len_s; i++)
        res[i] = toupper(s[i]);
    res[i] = '\0';
    return res;
}