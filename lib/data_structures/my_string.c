//
// Created by Mikhail Tsaritsyn on 18.10.2021.
//

#include "data_structures/my_string.h"

/// maximum extra number of bytes to be appended during concatenation
const unsigned long MAX_APPEND_CHUNK = 1024;

string new_empty_string(unsigned long size) {
    string result = malloc(sizeof(string_object));
    result->c_string = malloc(size + 1);
    result->c_string[0] = '\0';
    result->length = 0;
    result->allocated_size = size;
    return result;
}


string new_string(const char* value) {
    string result = new_empty_string(strlen(value));
    unsigned long i;
    for (i = 0; (result->c_string[i] = value[i]) != '\0'; i++);
    result->c_string[i] = '\0';
    result->length = result->allocated_size;
    return result;
}


string copy_string(const_string src) {
    string result = malloc(sizeof(string_object));
    result->c_string = malloc(src->allocated_size + 1);
    strcpy(result->c_string, src->c_string);
    result->length = src->length;
    result->allocated_size = src->allocated_size;
    return result;
}


void delete_string(string s) {
    free(s->c_string);
    free(s);
}


void print_string(const_string s) {
    printf("%s\n", s->c_string);
}


void resize_string(string s, unsigned long new_size) {
    if (new_size == s->allocated_size)
        return;

    char* new_c_str = realloc(s->c_string, new_size + 1);
    if (new_size < s->allocated_size) {
        new_c_str[new_size] = '\0';
        s->length = new_size;
    }
    s->c_string = new_c_str;
    s->allocated_size = new_size;
}


string string_concat(const_string s1, const_string s2) {
    string dst = new_empty_string(s1->length + s2->length);
    string_concat_to(dst, s1);
    string_concat_to(dst, s2);
    return dst;
}


void string_concat_to(string dst, const_string src) {
    if (dst->length + src->length > dst->allocated_size)
        resize_string(dst, MAX(dst->length + src->length, MIN(dst->length * 2, MAX_APPEND_CHUNK)));
    strcpy(dst->c_string + dst->length, src->c_string);
    dst->length += src->length;
}


void string_append(string s, char c) {
    if (s->length + 1 > s->allocated_size)
        resize_string(s, MAX(s->length + 1, MIN(s->length * 2, MAX_APPEND_CHUNK)));
    s->c_string[s->length] = c;
    s->length++;
    s->c_string[s->length] = '\0';
}


int string_cmp(const_string s1, const_string s2) {
    return strcmp(s1->c_string, s2->c_string);
}


