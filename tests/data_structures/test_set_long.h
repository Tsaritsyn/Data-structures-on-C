//
// Created by Mikhail Tsaritsyn on 17.07.2021.
//

#ifndef MY_CLIB_TEST_SET_LONG_H
#define MY_CLIB_TEST_SET_LONG_H


#include "data_structures/set_long.h"


int test_set_creation(void) {

    printf("\nSet creation test started.\n");

    Set_long_ptr set = create_set();
    printf("Empty set created, its size %lu bytes.\n", sizeof(Set_long));

    unsigned int checks_passed = 0;
    unsigned int checks_total = 0;
    if (set->tree == NULL)
        checks_passed++;
    else
        printf("Check 1 failed: set->tree != NULL.\n");
    checks_total++;

    if (set->size == 0)
        checks_passed++;
    else
        printf("Check 2 failed: set->size != 0, but %lu.\n", set->size);
    checks_total++;

    if (checks_passed == checks_total) {
        printf("Test passed.\n");
        return 1;
    }
    else {
        printf("Test failed (%u/%u checks passed).", checks_passed, checks_total);
        return 0;
    }
}


#endif //MY_CLIB_TEST_SET_LONG_H
