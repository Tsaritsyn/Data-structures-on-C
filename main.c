//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#include "my_clib.h"
#include "stdio.h"


int main() {
    matrix_int_ptr M = new_empty_matrix_int(10);
    print_matrix_int(M);

    size_t i;
    for (i = 0; i < 10; i++)
        matrix_int_append_row(M, new_range_int(0, 10, 1));
    print_matrix_int(M);

    transpose_square_matrix_int(M);
    print_matrix_int(M);

    matrix_int_ptr transposed = get_transposed_matrix_int(M);
    print_matrix_int(transposed);
    printf("%lu, %lu\n", M->allocated_height, M->allocated_width);
    printf("%lu, %lu\n", transposed->allocated_height, transposed->allocated_width);

    delete_matrix(M);
    delete_matrix(transposed);


    matrix_float_ptr Mf = new_empty_matrix_float(10);
    print_matrix_float(Mf);

    for (i = 0; i < 10; i++)
        matrix_float_append_row(Mf, new_range_float(0, 10, 1));
    print_matrix_float(Mf);

    transpose_square_matrix_float(Mf);
    print_matrix_float(Mf);

    matrix_float_ptr transposed_f = get_transposed_matrix_float(Mf);
    print_matrix_float(transposed_f);
    printf("%lu, %lu\n", Mf->allocated_height, Mf->allocated_width);
    printf("%lu, %lu\n", transposed_f->allocated_height, transposed_f->allocated_width);

    delete_matrix(Mf);
    delete_matrix(transposed_f);

    return 0;
}

