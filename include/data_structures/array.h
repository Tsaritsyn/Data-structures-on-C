//
// Created by Mikhail Tsaritsyn on 18.10.2021.
//

#ifndef MY_CLIB_ARRAY_H
#define MY_CLIB_ARRAY_H

#include <math.h>

#include "common.h"
#include "my_string.h"


#define declare_array(type) \
                            \
typedef struct array_##type { \
    unsigned long length, allocated_size; \
    type *elements;                  \
    int (*compare_elements)(const type, const type); \
} array_##type;             \
typedef array_##type* array_##type##_ptr; \
                            \
                            \
array_##type##_ptr new_empty_array_##type(unsigned long size); \
                            \
                            \
array_##type##_ptr new_constant_array_##type(unsigned long size, type value);\
                            \
                            \
array_##type##_ptr new_array_##type(const type c_arr[], unsigned long size);          \
                           \
                           \
void print_array_##type(const array_##type* arr, const char* sep);      \
                           \
                           \
void resize_array_##type(array_##type##_ptr arr, unsigned long new_size); \
                           \
                           \
void array_##type##_append(array_##type##_ptr arr, type value);           \
                           \
                           \
void fill_array_##type##_with(array_##type##_ptr arr, type value);        \
                            \
                            \
void revert_array_##type(array_##type##_ptr);          \
                            \
                            \
int are_arrays_##type##_equal(const array_##type* arr1, const array_##type* arr2);    \
                            \
                            \
int compare_array_##type(const array_##type* arr1, const array_##type* arr2);\
\
\
array_##type##_ptr new_range_##type(type start, type end, type step);        \
                            \
                            \
array_##type##_ptr copy_array_##type(const array_##type* arr);\


declare_array(int)
declare_array(short)
declare_array(char)
declare_array(long)
declare_array(l_long)
declare_array(float)
declare_array(double)
declare_array(l_double)
declare_array(u_int)
declare_array(u_short)
declare_array(u_char)
declare_array(u_long)
declare_array(ul_long)
declare_array(size_t)


void delete_array(void*);


/**
 * Generic array print. The values inside the array will be separated by sep, and _end will be printed in the end.
 */
#define print_array(array_ptr, sep, _end) _Generic(array_ptr, \
array_short*: print_array_short,                        \
array_int*: print_array_int,                         \
array_long*: print_array_long,                         \
array_l_long*: print_array_l_long,                         \
array_u_short*: print_array_u_short,                         \
array_u_int*: print_array_u_int,                         \
array_u_long*: print_array_u_long,                         \
array_ul_long*: print_array_ul_long,                         \
array_char*: print_array_char,                         \
array_float*: print_array_float,                         \
array_double*: print_array_double,                         \
array_l_double*: print_array_l_double,                         \
array_size_t*: print_array_size_t\
)(array_ptr, sep);                                            \
printf("%s", _end)


/**
 * Creates a new array of a given size filled with a given constant.
 */
#define new_constant_array(size, value) _Generic(value, \
short: new_constant_array_short,                        \
int: new_constant_array_int,                         \
long: new_constant_array_long,                         \
long long: new_constant_array_l_long,                         \
unsigned short: new_constant_array_u_short,                         \
unsigned int: new_constant_array_u_int,                         \
unsigned long: new_constant_array_u_long,                         \
unsigned long long: new_constant_array_ul_long,                         \
char: new_constant_array_char,                         \
float: new_constant_array_float,                         \
double: new_constant_array_double,                         \
long double: new_constant_array_l_double                         \
)(size, value)


/**
 * Reallocates the memory of the array to the new size. If new size is less then the former length, then the length
 * will be reduced and the tailing values will be lost. Otherwise, all values remain intact.
 */
#define resize_array(arr, new_size) _Generic(arr, \
array_short*: resize_array_short,                        \
array_int*: resize_array_int,                         \
array_long*: resize_array_long,                         \
array_l_long*: resize_array_l_long,                         \
array_u_short*: resize_array_u_short,                         \
array_u_int*: resize_array_u_int,                         \
array_u_long*: resize_array_u_long,                         \
array_ul_long*: resize_array_ul_long,                         \
array_char*: resize_array_char,                         \
array_float*: resize_array_float,                         \
array_double*: resize_array_double,                         \
array_l_double*: resize_array_l_double,                         \
array_size_t*: resize_array_size_t\
)(arr, new_size)


/**
 * Puts the given value to the end of the given array, increasing its length. If necessary, the memory will be
 * reallocated. If the value type is not the same as the type of the array elements, the value will be casted to the
 * necessary type.
 */
#define append_to_array(arr, value) _Generic(arr,\
array_short*: array_short_append,                        \
array_int*: array_int_append,                         \
array_long*: array_long_append,                         \
array_l_long*: array_l_long_append,                         \
array_u_short*: array_u_short_append,                         \
array_u_int*: array_u_int_append,                         \
array_u_long*: array_u_long_append,                         \
array_ul_long*: array_ul_long_append,                         \
array_char*: array_char_append,                         \
array_float*: array_char_append,                         \
array_double*: array_double_append,                         \
array_l_double*: array_l_double_append,                         \
array_size_t*: array_size_t_append\
)(arr, value)


/**
 * Makes all the elements of the array to be equal to the given value. Does not change its length.
 */
#define fill_array(arr, value) _Generic(arr, \
array_short*: fill_array_short_with,                        \
array_int*: fill_array_int_with,                         \
array_long*: fill_array_long_with,                         \
array_l_long*: fill_array_l_long_with,                         \
array_u_short*: fill_array_u_short_with,                         \
array_u_int*: fill_array_u_int_with,                         \
array_u_long*: fill_array_u_long_with,                         \
array_ul_long*: fill_array_ul_long_with,                         \
array_char*: fill_array_char_with,                         \
array_float*: fill_array_float_with,                         \
array_double*: fill_array_double_with,                         \
array_l_double*: fill_array_l_double_with,                         \
array_size_t*: fill_array_size_t_with\
)(arr, value)


/**
 * Flips the element of the given array in-place. No new arrays are created, the current array is not reallocated.
 */
#define revert_array(arr) _Generic(arr, \
array_short*: revert_array_short,                        \
array_int*: revert_array_int,                         \
array_long*: revert_array_long,                         \
array_l_long*: revert_array_l_long,                         \
array_u_short*: revert_array_u_short,                         \
array_u_int*: revert_array_u_int,                         \
array_u_long*: revert_array_u_long,                         \
array_ul_long*: revert_array_ul_long,                         \
array_char*: revert_array_char,                         \
array_float*: revert_array_float,                         \
array_double*: revert_array_double,                         \
array_l_double*: revert_array_l_double,                         \
array_size_t*: revert_array_size_t\
)(arr)


#define are_arrays_equal(arr1, arr2) _Generic(arr1, \
array_short*: are_arrays_short_equal,                        \
array_int*: are_arrays_int_equal,                         \
array_long*: are_arrays_long_equal,                         \
array_l_long*: are_arrays_l_long_equal,                         \
array_u_short*: are_arrays_u_short_equal,                         \
array_u_int*: are_arrays_u_int_equal,                         \
array_u_long*: are_arrays_u_long_equal,                         \
array_ul_long*: are_arrays_ul_long_equal,                         \
array_char*: are_arrays_char_equal,                         \
array_float*: are_arrays_float_equal,                         \
array_double*: are_arrays_double_equal,                         \
array_l_double*: are_arrays_l_double_equal,                         \
array_size_t*: are_arrays_size_t_equal\
)(arr1, arr2)


#define compare_array(arr1, arr2) _Generic(arr1, \
array_short*: compare_array_short,                        \
array_int*: compare_array_int,                         \
array_long*: compare_array_long,                         \
array_l_long*: compare_array_l_long,                         \
array_u_short*: compare_array_u_short,                         \
array_u_int*: compare_array_u_int,                         \
array_u_long*: compare_array_u_long,                         \
array_ul_long*: compare_array_ul_long,                         \
array_char*: compare_array_char,                         \
array_float*: compare_array_float,                         \
array_double*: compare_array_double,                         \
array_l_double*: compare_array_l_double,                         \
array_size_t*: compare_array_size_t\
)(arr1, arr2)


#define new_range(start, end, step) _Generic(start, \
short: new_range_short,                        \
int: new_range_int,                         \
long: new_range_long,                         \
l_long: new_range_l_long,                         \
u_short: new_range_u_short,                         \
u_int: new_range_u_int,                         \
u_long: new_range_u_long,                         \
ul_long: new_range_ul_long,                         \
char: new_range_char,                         \
float: new_range_float,                         \
double: new_range_double,                         \
l_double: new_range_l_double                         \
)(start, end, step)


#define copy_array(arr) _Generic(arr,\
array_short*: copy_array_short,                        \
array_int*: copy_array_int,                         \
array_long*: copy_array_long,                         \
array_l_long*: copy_array_l_long,                         \
array_u_short*: copy_array_u_short,                         \
array_u_int*: copy_array_u_int,                         \
array_u_long*: copy_array_u_long,                         \
array_ul_long*: copy_array_ul_long,                         \
array_char*: copy_array_char,                         \
array_float*: copy_array_float,                         \
array_double*: copy_array_double,                         \
array_l_double*: copy_array_l_double,                         \
array_size_t*: copy_array_size_t\
)(arr)


typedef struct DataList {
    size_t length, allocated_size;
    void** elements;
    void (*delete_element)(void*);
} DataList;


DataList *new_empty_datalist(size_t size, void (*delete_element)(void *));


void delete_datalist(DataList *datalist);


void print_datalist(const DataList *dataList, void (*print_element)(const void *));


void resize_datalist(DataList *dataList, size_t new_size);


void append_to_datalist(DataList *dataList, void* structure);


#endif //MY_CLIB_ARRAY_H
