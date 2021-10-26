//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#include "my_clib.h"
#include "stdio.h"


void delete_long(size_t x) {}


int main() {

    Dict* dict_str_long = new_empty_dict((int (*)(const void *, const void *)) &compare_string,
                                         (void (*)(const void *)) &print_string,
                                         (void (*)(const void *)) &print_long,
                                         (void (*)(void *)) &delete_string,
                                         (void (*)(void *)) &delete_long);

    string* key = new_string("Alex");
    add_to_dict(dict_str_long, new_string("Mikhail"), 23);
    add_to_dict(dict_str_long, copy_string(key), 24);
    add_to_dict(dict_str_long, new_string("Mattia"), 35);
    print_dict(dict_str_long);
    printf("\n");
    printf("%lu\n", get_from_dict(dict_str_long, key));

    remove_from_dict(dict_str_long, key);
    print_dict(dict_str_long);
    printf("\n");

    delete_string(key);
    delete_dict(dict_str_long);

    return 0;
}

