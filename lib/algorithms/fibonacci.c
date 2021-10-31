//
// Created by Mikhail Tsaritsyn on 31.10.2021.
//

#include "algorithms/fibonacci.h"


DataList* get_all_fibonacci(size_t n) {
    DataList *result = new_empty_datalist(n, &print_long_num, &delete_long_num, &compare_long_num);
    if (n == 0) return result;

    append_to_datalist(result, new_long_num(1));
    if (n == 1) return result;

    append_to_datalist(result, new_long_num(1));
    if (n == 2) return result;

    size_t i;
    for (i = 2; i < n; i++)
        append_to_datalist(result, add_long_num(result->elements[i-1], result->elements[i-2]));

    return result;
}
