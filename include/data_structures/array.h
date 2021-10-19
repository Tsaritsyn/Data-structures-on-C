//
// Created by Mikhail Tsaritsyn on 18.10.2021.
//

#ifndef MY_CLIB_ARRAY_H
#define MY_CLIB_ARRAY_H

#include "common.h"
#include "my_string.h"


#define declare_array(type) \
typedef struct { \
    unsigned long length, allocated_size; \
    type *elements;                  \
    int (*compare_elements)(const type*, const type*); \
} array_##type;             \
typedef array_##type* array_##type##_ptr; \
                            \
array_##type##_ptr new_empty_array_##type(unsigned long size); \
                            \
                            \
array_##type##_ptr new_array_##type(type c_arr[], unsigned long size);          \
                            \
                            \
void delete_array_##type(array_##type##_ptr arr);      \
                           \
                           \
void print_array_##type(const array_##type* arr);      \
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



declare_array(int)
declare_array(short)
declare_array(char)
declare_array(long)
declare_array(float)
declare_array(double)
declare_array(u_int)
declare_array(u_short)
declare_array(u_char)
declare_array(u_long)



#endif //MY_CLIB_ARRAY_H
