//
// Created by Mikhail Tsaritsyn on 23.10.2021.
//

#include "data_structures/matrix.h"


matrix_int_ptr new_empty_matrix_int(size_t height) {
    matrix_int_ptr result = malloc(sizeof(matrix_int));
    result->rows = malloc(sizeof(array_int_ptr) * height);
    result->height = 0;
    result->width = 0;
    result->allocated_width = 0;
    result->allocated_height = height;
    return result;
}


matrix_int_ptr new_constant_matrix_int(size_t height, size_t width, int value) {
    matrix_int_ptr result = new_empty_matrix_int(height);
    size_t i;
    for (i = 0; i < height; i++)
        matrix_int_append_row(result, new_constant_array_int(width, value));
    result->height = height;
    result->width = width;
    result->allocated_width = result->rows[0]->allocated_size;
    return result;
}


void resize_matrix_int(matrix_int_ptr M, size_t new_height, size_t new_width) {
    size_t i, j;
    if (new_width != M->allocated_width) {
        for (i = 0; i < M->height; i++)
            resize_array_int(M->rows[i], new_width);
        M->allocated_width = new_width;
        M->width = MIN(M->width, new_width);
    }

    if (new_height != M->height) {
        if (new_height < M->height)
            for (i = new_height; i < M->height; i++)
                delete_array(M->rows[i]);

        M->rows = realloc(M->rows, sizeof(array_int_ptr) * new_height);
        M->allocated_height = new_height;
        M->height = MIN(M->height, new_height);
    }
}


int matrix_int_append_row(matrix_int_ptr M, array_int_ptr row) {
    if (M->height == 0) {
        M->width = row->length;
        if (M->allocated_width == 0)
            M->allocated_width = row->length;
    }
    else if (row->length != M->width) {
        printf("Cannot append row of length %lu to the matrix of width %lu\n", row->length, M->width);
        return 0;
    }

    if (M->height + 1 > M->allocated_height)
        resize_matrix_int(M, M->height + MIN(M->height, MAX_APPEND_LENGTH) + 1, M->allocated_width);
    M->rows[M->height++] = row;
    return 1;
}


int matrix_int_append_column(matrix_int_ptr M, array_int_ptr column) {
//    it is the first column of the matrix, so we need to create all the rows first
    size_t i;
    if (M->width == 0)
        for (i = 0; i < column->length; i++)
            matrix_int_append_row(M, new_empty_array_int(1));

    if (column->length != M->height) {
        printf("Cannot append a column of size %lu to a matrix of height %lu\n", column->length, M->height);
        return 0;
    }

    for (i = 0; i < M->height; i++)
        array_int_append(M->rows[i], column->elements[i]);
    M->width++;
    M->allocated_width = M->rows[0]->allocated_size;
    return 1;
}


void delete_matrix(void* M) {
    size_t i;
//    it actually does not matter to matrix of which type to cast, because all of them have fields in the same order
//    and of the same size
    for (i = 0; i < ((matrix_int_ptr)M)->height; i++)
        delete_array(((matrix_int_ptr)M)->rows[i]);
    free(((matrix_int_ptr)M)->rows);
    free(M);
}


void print_matrix_int(const matrix_int* M) {
    size_t i;
    printf("[\n");
    for (i = 0; i < M->height; i++) {
        printf("\t");
        print_array_int(M->rows[i]);
        printf("%s", (i == M->height - 1) ? "\n" : ",\n");
    }
    printf("]");
}


int transpose_square_matrix_int(matrix_int_ptr M) {
    if (M->height != M->width) {
        printf("Matrix %lux%lu is not square\n", M->height, M->width);
        return 0;
    }

    size_t i, j;
    for (i = 0; i < M->height; i++)
        for (j = i + 1; j < M->width; j++)
            SWAP(int, M->rows[i]->elements[j], M->rows[j]->elements[i])
    return 1;
}


matrix_int_ptr get_transposed_matrix_int(const matrix_int* M) {
    matrix_int_ptr result = new_empty_matrix_int(M->width);
    size_t i;
    for (i = 0; i < M->height; i++)
        matrix_int_append_column(result, M->rows[i]);
    return result;
}


/**
 * Here comes the implementation of template matrix functions for other numerical types. It must be kept the same as
 * for int.
 */
#define implement_matrix(type)\
\
matrix_##type##_ptr new_empty_matrix_##type(size_t height) {\
    matrix_##type##_ptr result = malloc(sizeof(matrix_##type));\
    result->rows = malloc(sizeof(array_##type##_ptr) * height);\
    result->height = 0;\
    result->width = 0;\
    result->allocated_width = 0;\
    result->allocated_height = height;\
    return result;\
}\
\
\
matrix_##type##_ptr new_constant_matrix_##type(size_t height, size_t width, type value) {\
    matrix_##type##_ptr result = new_empty_matrix_##type(height);\
    size_t i;\
    for (i = 0; i < height; i++)\
        matrix_##type##_append_row(result, new_constant_array_##type(width, value));\
    result->height = height;\
    result->width = width;\
    result->allocated_width = result->rows[0]->allocated_size;\
    return result;\
}\
\
\
void resize_matrix_##type(matrix_##type##_ptr M, size_t new_height, size_t new_width) {\
    size_t i, j;\
    if (new_width != M->allocated_width) {\
        for (i = 0; i < M->height; i++)\
            resize_array_##type(M->rows[i], new_width);\
        M->allocated_width = new_width;\
        M->width = MIN(M->width, new_width);\
    }\
\
    if (new_height != M->height) {\
        if (new_height < M->height)\
            for (i = new_height; i < M->height; i++)\
                delete_array(M->rows[i]);\
\
        M->rows = realloc(M->rows, sizeof(array_##type##_ptr) * new_height);\
        M->allocated_height = new_height;\
        M->height = MIN(M->height, new_height);\
    }\
}\
\
\
int matrix_##type##_append_row(matrix_##type##_ptr M, array_##type##_ptr row) {\
    if (M->height == 0) {\
        M->width = row->length;\
        if (M->allocated_width == 0)\
            M->allocated_width = row->length;\
    }\
    else if (row->length != M->width) {\
        printf("Cannot append row of length %lu to the matrix of width %lu\n", row->length, M->width);\
        return 0;\
    }\
\
    if (M->height + 1 > M->allocated_height)\
        resize_matrix_##type(M, M->height + MIN(M->height, MAX_APPEND_LENGTH) + 1, M->allocated_width);\
    M->rows[M->height++] = row;\
    return 1;\
}\
\
\
int matrix_##type##_append_column(matrix_##type##_ptr M, array_##type##_ptr column) {\
    size_t i;\
    if (M->width == 0)\
        for (i = 0; i < column->length; i++)\
            matrix_##type##_append_row(M, new_empty_array_##type(1));\
\
    if (column->length != M->height) {\
        printf("Cannot append a column of size %lu to a matrix of height %lu\n", column->length, M->height);\
        return 0;\
    }\
\
    for (i = 0; i < M->height; i++)\
        array_##type##_append(M->rows[i], column->elements[i]);\
    M->width++;\
    M->allocated_width = M->rows[0]->allocated_size;\
    return 1;\
}\
\
\
void print_matrix_##type(const matrix_##type* M) {\
    size_t i;\
    printf("[\n");\
    for (i = 0; i < M->height; i++) {\
        printf("\t");\
        print_array_##type(M->rows[i]);                     \
        printf("%s", (i == M->height - 1) ? "\n" : ",\n");\
    }\
    printf("]");\
}\
\
\
int transpose_square_matrix_##type(matrix_##type##_ptr M) {\
    if (M->height != M->width) {\
        printf("Matrix %lux%lu is not square\n", M->height, M->width);\
        return 0;\
    }\
\
    size_t i, j;\
    for (i = 0; i < M->height; i++)\
        for (j = i + 1; j < M->width; j++)\
        SWAP(type, M->rows[i]->elements[j], M->rows[j]->elements[i])\
    return 1;\
}\
\
\
matrix_##type##_ptr get_transposed_matrix_##type(const matrix_##type* M) {\
    matrix_##type##_ptr result = new_empty_matrix_##type(M->width);\
    size_t i;\
    for (i = 0; i < M->height; i++)\
        matrix_##type##_append_column(result, M->rows[i]);\
    return result;\
}

implement_matrix(short)
implement_matrix(char)
implement_matrix(long)
implement_matrix(float)
implement_matrix(double)
implement_matrix(u_int)
implement_matrix(u_short)
implement_matrix(u_char)
implement_matrix(u_long)