//
// Created by Mikhail Tsaritsyn on 23.10.2021.
//

#ifndef MY_CLIB_MATRIX_H
#define MY_CLIB_MATRIX_H

#include <assert.h>

#include "array.h"

typedef struct matrix_int {
    size_t height, width;
    size_t allocated_height, allocated_width;
    array_int** rows;
} matrix_int;
typedef matrix_int* matrix_int_ptr;


/**
 * Allocates memory for a matrix of a given size. Does not fill the matrix with any values.
 * Its height and width will be zeros.
 *
 * @param height number of rows to be allocated
 * @param width length of each row to be allocated
 * @return pointer to the resulting matrix
 */
matrix_int_ptr new_empty_matrix_int(size_t height);


/**
 * Creates a matrix of a given size and fills it with the given value.
 * The allocated memory chunk will be exactly equal to the given dimensions.
 *
 * @return pointer to the resulting matrix
 */
matrix_int_ptr new_constant_matrix_int(size_t height, size_t width, int value);


/**
 * Reallocates memory for a given matrix. If a desired dimension is larger than the current one, all values will be preserved
 * and no new values will be added. If less, then all extra values will be lost and the dimension size (height/width) will be reduced.
 *
 * WARNING: the height and width values are changed only if the matrix dimension has been reduced!
 *
 * WARNING: though this operation might add pointer to new rows, they will be NULL, so you will need to create new rows manually, if needed
 */
void resize_matrix_int(matrix_int_ptr M, size_t new_height, size_t new_width);


/**
 * Puts the given array as the last row of the given matrix. The length of the row must be equal to the width of the matrix.
 *
 * WARNING: the values from the given array are not copied into the matrix, but instead the pointer to the array is stored.
 * So, if you delete the array, the correspondent row of the matrix will be lost, too.
 *
 * @return 1 if successful, 0 otherwise
 */
int matrix_int_append_row(matrix_int_ptr M, array_int_ptr row);


/**
 * Puts the given array as the last column of the given matrix. The length of the row must be equal to the height of the matrix.
 *
 * WARNING: the values of the given array are copied into the matrix, so firstly, it is done mush slower than append_row,
 * and secondly, you should use delete_array() when you want to deallocate the memory occupied by this array.
 * The matrix will not be touched by it.
 *
 * @return 1 if successful, 0 otherwise
 */
int matrix_int_append_column(matrix_int_ptr M, array_int_ptr column);


/**
 * Deallocates the memory.
 */
void delete_matrix(void*);


/**
 * Prints the values of the NxM matrix as following:
 * [[a11, a12, ... a1M],
 * [a21, a22, ... a2M],
 * ...
 * [aN1, aN2, ... aNM]]
 */
void print_matrix_int(const matrix_int*);


/**
 * Does in-place transposition of a square matrix. If it is not square, does nothing.
 *
 * We cannot transpose non-square matrix in-place, because of the memory problems. For example, take NxM matrix with
 * N >> M. To transpose it in-place, we will need to resize it transforming to NxN matrix,
 * transpose it as a square one, and reduce it to MxN. This intermediate step may require allocation of huge amount
 * of memory, though most of it will not ever be initialized and used.
 *
 * @return 1 if the matrix has been transposed successfully and 0 otherwise
 */
int transpose_square_matrix_int(matrix_int_ptr);


/**
 * @return the transposed version of the given matrix
 */
matrix_int_ptr get_transposed_matrix_int(const matrix_int*);


/**
 * Here goes the template matrix definition for different numerical types. It must be kept the same as for integer.
 */
#define declare_matrix(type) \
typedef struct matrix_##type {\
    size_t height, width;\
    size_t allocated_height, allocated_width;\
    array_##type** rows;\
} matrix_##type;\
typedef matrix_##type* matrix_##type##_ptr;  \
\
matrix_##type##_ptr new_empty_matrix_##type(size_t height);\
\
\
matrix_##type##_ptr new_constant_matrix_##type(size_t height, size_t width, type value);\
\
\
void resize_matrix_##type(matrix_##type##_ptr M, size_t new_height, size_t new_width);\
\
\
int matrix_##type##_append_row(matrix_##type##_ptr M, array_##type##_ptr row);\
\
\
int matrix_##type##_append_column(matrix_##type##_ptr M, array_##type##_ptr column);\
\
\
void print_matrix_##type(const matrix_##type*);\
\
\
int transpose_square_matrix_##type(matrix_##type##_ptr);\
\
\
matrix_##type##_ptr get_transposed_matrix_##type(const matrix_##type*);                    \

declare_matrix(short)
declare_matrix(char)
declare_matrix(long)
declare_matrix(float)
declare_matrix(double)
declare_matrix(u_int)
declare_matrix(u_short)
declare_matrix(u_char)
declare_matrix(u_long)

#endif //MY_CLIB_MATRIX_H
