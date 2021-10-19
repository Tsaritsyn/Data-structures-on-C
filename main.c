//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#include "my_clib.h"
#include "stdio.h"


void test_substrings() {
    string_ptr s = new_string("abacabadabacabafabacabadabacabagabacabadabacabafabacabadabacaba");
    unsigned long i;

    string_ptr substr = new_string("cabafabacabad");
    unsigned long* positions = NULL;
    unsigned long num_of_occurrences = find_substrings(s, substr, &positions);
    printf("%lu occurrences found:\n", num_of_occurrences);
    for (i = 0; i < num_of_occurrences; i++)
        printf("%lu ", positions[i]);
    printf("\n");

    delete_string(s);
    delete_string(substr);
    free(positions);
}


void test_str_distance() {
    string_ptr s1 = new_string("moloko");
    string_ptr s2 = new_string("kolokol");
    printf("%lu\n", get_levenstein_distance(s1, s2));

    delete_string(s1);
    delete_string(s2);
}


void test_arrays(){
    array_int_ptr arr = new_empty_array_int(10);
    fill_array_int_with(arr, -1);
    print_array_int(arr);

    int i;
    for (i = 0; i < 20; i++)
        array_int_append(arr, i);
    print_array_int(arr);

    revert_array_int(arr);
    print_array_int(arr);

    fill_array_int_with(arr, 5);
    print_array_int(arr);

    delete_array_int(arr);

    int a[] = {0, 1, 5, 9, 11, 7, -2, 0};
    arr = new_array_int(a, sizeof(a) / sizeof(int));
    print_array_int(arr);
    delete_array_int(arr);
}


int main() {

    int a[] = {0, 1, 5, 9, 11, 7, -2, 0, 4};
    array_int_ptr arr1 = new_array_int(a, sizeof(a) / sizeof(a[0]));

    int b[] = {2, 0, -3, 10, 5, 9, 8, 7, 6, 10, 0, -2, 1};
    array_int_ptr arr2 = new_array_int(b, sizeof(b) / sizeof(b[0]));

    array_int_ptr gcs = greatest_common_subsequence(arr1, arr2);

    print_array_int(arr1);
    print_array_int(arr2);
    print_array_int(gcs);

    delete_array_int(arr1);
    delete_array_int(arr2);
    delete_array_int(gcs);

    return 0;
}

