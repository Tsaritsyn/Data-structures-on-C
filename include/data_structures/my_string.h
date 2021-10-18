//
// Created by Mikhail Tsaritsyn on 18.10.2021.
//

#ifndef MY_CLIB_MY_STRING_H
#define MY_CLIB_MY_STRING_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "common.h"

typedef struct {
    char* c_string;
    unsigned long length;
    /// the real size of the allocated memory will always be this value + 1 to account for the terminating symbol
    unsigned long allocated_size;
} string_object;
typedef string_object* string;
#define const_string const string_object*


/**
 * Allocates the memory for a new string_object of given size. The resulting string_object remains empty, however
 */
string new_empty_string(unsigned long);


/**
 * Allocates the memory for a new string_object and puts the given value into it. The allocation is just enough to fit the
 * value.
 */
string new_string(const char*);


string copy_string(const_string);


/**
 * Deallocates the memory chunk of the given string_object.
 */
void delete_string(string);


void print_string(const_string);


/**
 * Reallocate the memory for the given string to
 */
void resize_string(string, unsigned long);


/**
 * @return a new string_object with the value equal to given strings concatenated
 */
string string_concat(const_string, const_string);


/**
 * Concatenates the second string_object to the first one.
 */
void string_concat_to(string, const_string);


/**
 * Append the given given string_object with the given symbol.
 */
void string_append(string, char);


/**
 * @return negative number if the first one is less than the second one, positive number if the first one is bigger
 *  and 0 if they are equal
 */
int string_cmp(const_string, const_string);


#endif //MY_CLIB_MY_STRING_H
