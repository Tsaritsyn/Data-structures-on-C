//
// Created by Mikhail Tsaritsyn on 18.10.2021.
//

#include "data_structures/my_string.h"


string_ptr new_empty_string(unsigned long size) {
    string_ptr result = malloc(sizeof(string));
    result->c_string = malloc(size + 1);
    result->c_string[0] = '\0';
    result->length = 0;
    result->allocated_size = size;
    return result;
}


string_ptr new_string(const char* value) {
    string_ptr result = new_empty_string(strlen(value));
    unsigned long i;
    for (i = 0; (result->c_string[i] = value[i]) != '\0'; i++);
    result->c_string[i] = '\0';
    result->length = result->allocated_size;
    return result;
}


string_ptr copy_string(const_string_ptr src) {
    string_ptr result = malloc(sizeof(string));
    result->c_string = malloc(src->allocated_size + 1);
    strcpy(result->c_string, src->c_string);
    result->length = src->length;
    result->allocated_size = src->allocated_size;
    return result;
}


void delete_string(string_ptr s) {
    free(s->c_string);
    free(s);
}


void print_string(const_string_ptr s) {
    printf("%s", s->c_string);
}


void resize_string(string_ptr s, unsigned long new_size) {
    if (new_size == s->allocated_size)
        return;

    s->c_string = realloc(s->c_string, new_size + 1);
    if (new_size < s->allocated_size) {
        s->c_string[new_size] = '\0';
        s->length = new_size;
    }
    s->allocated_size = new_size;
}


string_ptr string_concat(const_string_ptr s1, const_string_ptr s2) {
    string_ptr dst = new_empty_string(s1->length + s2->length);
    string_concat_to(dst, s1);
    string_concat_to(dst, s2);
    return dst;
}


void string_concat_to(string_ptr dst, const_string_ptr src) {
    if (src->length == 0)
        return;

    if (dst->length + src->length > dst->allocated_size)
        resize_string(dst, MAX(dst->length + src->length, dst->length + MIN(dst->length, MAX_APPEND_LENGTH) + 1));
    strcpy(dst->c_string + dst->length, src->c_string);
    dst->length += src->length;
}


void string_append(string_ptr s, char c) {
    if (s->length + 1 > s->allocated_size)
        resize_string(s, s->length + MIN(s->length, MAX_APPEND_LENGTH) + 1);
    s->c_string[s->length] = c;
    s->length++;
    s->c_string[s->length] = '\0';
}


int compare_string(const string *s1, const string *s2) {
    return strcmp(s1->c_string, s2->c_string);
}


