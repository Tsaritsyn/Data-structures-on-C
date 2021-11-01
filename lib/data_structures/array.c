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
void print_array_##type(const array_##type* arr, const char* sep) {           \
    unsigned long i;        \
    printf("[");           \
    for (i = 0; i < arr->length; i++) {   \
        print(arr->elements[i], (i + 1 < arr->length) ? sep : "");      \
    }                      \
    printf("]");         \
}                          \
                           \
                           \
void resize_array_##type(array_##type##_ptr arr, unsigned long new_size) {     \
    arr->elements = realloc(arr->elements, sizeof(type) * new_size);           \
    arr->allocated_size = new_size;       \
    arr->length = MIN(arr->length, arr->allocated_size);  \
}                          \
                           \
                           \
void array_##type##_append(array_##type##_ptr arr, type value) { \
    if (arr->length + 1 > arr->allocated_size) {                \
        resize_array_##type(arr, MIN(arr->length + MAX_APPEND_LENGTH, arr->length * 2) + 1); \
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
array_##type##_ptr new_array_##type(const type c_arr[], unsigned long size) {  \
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
        if (arr1->compare_elements(arr1->elements[i], arr2->elements[i]) != 0)             \
            return 0;         \
    return 1;                 \
}                             \
                              \
                              \
int compare_array_##type(const array_##type* arr1, const array_##type* arr2) {          \
    unsigned int i;           \
    int element_relation;     \
    for (i = 0; i < MIN(arr1->length, arr2->length); i++) {     \
        element_relation = arr1->compare_elements(arr1->elements[i], arr2->elements[i]);   \
        if (element_relation != 0)                              \
            return element_relation;                            \
    }                         \
                              \
    if (arr1->length < arr2->length)                            \
        return -1;            \
    else if (arr1->length > arr2->length)                       \
        return 1;             \
    else                      \
        return 0;             \
}\
\
\
array_##type##_ptr new_range_##type(type start, type _end, type step) {\
    if (step == 0) {\
        printf("Cannot create a range with step 0\n");\
        return new_empty_array_##type(0);\
    }\
    \
    array_##type##_ptr result = new_empty_array_##type(0);\
    type value = start;\
    if (step > 0) {\
        if (_end < start) {\
            printf("Cannot create a range from ");\
            print_##type(start);\
            printf(" to ");\
            print_##type(_end);\
            printf(" with step ");\
            print_##type(step);\
            printf("\n");\
            return result;\
        }\
\
        while (value < _end) {\
            array_##type##_append(result, value);               \
            value += step;                          \
        }                          \
    }\
    else {\
        if (_end > start) {\
            printf("Cannot create a range from ");              \
            print(start, " to ");                               \
            print(_end, " with step ");                         \
            print(step, "\n");                  \
            return result;\
        }\
\
        while (value > _end) {\
            array_##type##_append(result, value);               \
            value += step;                          \
        }                     \
    }                         \
    return result;\
}\
\
\
array_##type##_ptr copy_array_##type(const array_##type* arr) {           \
    array_##type##_ptr copy = new_empty_array_##type(arr->length);             \
    size_t i;                 \
    for (i = 0; i < arr->length; i++)                           \
        array_##type##_append(copy, arr->elements[i]);          \
    return copy;\
}\

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
implement_array(size_t)


void delete_array(void* arr) {
//    it actually does not matter to array of which type to cast, because all of them have fields in the same order
//    and of the same size
    free(((array_int*)arr)->elements);
    free(arr);
}


//******************************//
// DataList methods description //
//******************************//


DataList *new_empty_datalist(size_t size, void (*delete_element)(void *)) {
    DataList *dataList = malloc(sizeof(DataList));
    dataList->allocated_size = size;
    dataList->elements = malloc(sizeof(void*) * size);
    dataList->length = 0;
    dataList->delete_element = delete_element;
    return dataList;
}


void delete_datalist(DataList *datalist) {
    size_t i;
    for (i = 0; i < datalist->length; i++)
        datalist->delete_element(datalist->elements[i]);
    free(datalist->elements);
    free(datalist);
}


void print_datalist(const DataList *dataList, void (*print_element)(const void *)) {
    printf("[");
    size_t i;
    for (i = 0; i < dataList->length; i++) {
        print_element(dataList->elements[i]);
        printf("%s", (i < dataList->length - 1) ? ", " : "");
    }
    printf("]");
}


void resize_datalist(DataList *dataList, size_t new_size) {
    if (new_size < dataList->length) {
        size_t i;
        for (i = new_size; i < dataList->length; i++)
            dataList->delete_element(dataList->elements[i]);
    }

    dataList->elements = realloc(dataList->elements, sizeof(void*) * new_size);
    dataList->allocated_size = new_size;
    dataList->length = MIN(dataList->length, dataList->allocated_size);
}


void append_to_datalist(DataList *dataList, void* structure) {
    if (dataList->length + 1 > dataList->allocated_size) {                \
        resize_datalist(dataList, MIN(dataList->length + MAX_APPEND_LENGTH, dataList->length * 2) + 1); \
    }                      \
    dataList->elements[dataList->length++] = structure;
}
