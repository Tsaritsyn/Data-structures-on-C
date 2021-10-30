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
} string;
typedef string* string_ptr;
#define const_string_ptr const string*


/**
 * Allocates the memory for a new string of given size. The resulting string remains empty, however
 */
string_ptr new_empty_string(unsigned long);


/**
 * Allocates the memory for a new string and puts the given value into it. The allocation is just enough to fit the
 * value.
 */
string_ptr new_string(const char*);


string_ptr copy_string(const_string_ptr);


/**
 * Deallocates the memory chunk of the given string.
 */
void delete_string(string_ptr);


void print_string(const_string_ptr);


/**
 * Reallocate the memory for the given string_ptr to
 */
void resize_string(string_ptr, unsigned long);


/**
 * @return a new string with the value equal to given strings concatenated
 */
string_ptr string_concat(const_string_ptr, const_string_ptr);


/**
 * Concatenates the second string to the first one.
 */
void string_concat_to(string_ptr, const_string_ptr);


/**
 * Append the given given string with the given symbol.
 */
void string_append(string_ptr, char);


/**
 * @return negative number if the first one is less than the second one, positive number if the first one is bigger
 *  and 0 if they are equal
 */
int compare_string(const string *s1, const string *s2);


void revert_string(string* s);


#endif //MY_CLIB_MY_STRING_H
