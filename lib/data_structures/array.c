//
// Created by Mikhail Tsaritsyn on 19.10.2021.
//

#include "data_structures/array.h"


#define implement_array(type) \
                              \
array_##type##_ptr new_empty_array_##type(unsigned long size) { \
    array_##type##_ptr arr = malloc(sizeof(array_##type)); \
    arr->elements = malloc(sizeof(type) * size); \
    arr->length = 0; \
    arr->allocated_size = size; \
    arr->compare_elements = &compare_##type; \
    return arr; \
}                             \
                              \
                              \
array_##type##_ptr new_constant_array_##type(unsigned long size, type value) { \
    array_##type##_ptr arr = new_empty_array_##type(size);      \
    arr->length = size;       \
    unsigned long i;          \
    for (i = 0; i < arr->length; i++)                           \
        arr->elements[i] = value;                               \
    return arr;               \
}                             \
                           \
                           \
void delete_array_##type(array_##type##_ptr arr) {   \
    free(arr->elements);   \
    free(arr);             \
}                          \
                           \
                           \
void print_array_##type(const array_##type* arr) {           \
    unsigned long i;        \
    printf("[");           \
    for (i = 0; i < arr->length; i++) {   \
        print_##type(arr->elements[i]);      \
        printf("%s", (i + 1 < arr->length) ? ", " : "");  \
    }                      \
    printf("]\n");         \
}                          \
                           \
                           \
void resize_array_##type(array_##type##_ptr arr, unsigned long new_size) { \
    arr->elements = realloc(arr->elements, new_size);  \
    arr->allocated_size = new_size;       \
    arr->length = MIN(arr->length, arr->allocated_size);  \
}                          \
                           \
                           \
void array_##type##_append(array_##type##_ptr arr, type value) { \
    if (arr->length + 1 > arr->allocated_size) {       \
        resize_array_##type(arr, MAX(MAX_APPEND_LENGTH, arr->allocated_size * 2)); \
    }                      \
    arr->elements[arr->length++] = value; \
}                          \
                           \
                           \
void fill_array_##type##_with(array_##type##_ptr arr, type value) {        \
    unsigned long i;       \
    for (i = 0; i < arr->length; i++)     \
        arr->elements[i] = value;         \
}                             \
                              \
                              \
void revert_array_##type(array_##type##_ptr arr) {        \
    unsigned int i;           \
    for (i = 0; i < arr->length / 2; i++) {               \
        type temp = arr->elements[i];                      \
        arr->elements[i] = arr->elements[arr->length - 1 - i];             \
        arr->elements[arr->length - 1 - i] = temp;        \
    }                         \
}                             \
                              \
                              \
array_##type##_ptr new_array_##type(type c_arr[], unsigned long size) {  \
    unsigned long i;           \
    array_##type##_ptr result = new_empty_array_##type(size);           \
    for (i = 0; i < size; i++)\
        array_##type##_append(result, c_arr[i]);                     \
    return result;            \
}                             \
                              \
                              \
int are_arrays_##type##_equal(const array_##type* arr1, const array_##type* arr2) {   \
    if (arr1->length != arr2->length)                           \
        return 0;             \
                              \
    unsigned long i;          \
    for (i = 0; i < arr1->length; i++)                          \
        if (arr1->elements[i] != arr2->elements[i])             \
            return 0;         \
    return 1;                 \
}                             \


implement_array(int)
implement_array(short)
implement_array(char)
implement_array(long)
implement_array(float)
implement_array(double)
implement_array(u_int)
implement_array(u_short)
implement_array(u_char)
implement_array(u_long)



