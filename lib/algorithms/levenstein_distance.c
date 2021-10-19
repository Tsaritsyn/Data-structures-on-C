//
// Created by Mikhail Tsaritsyn on 18.10.2021.
//

#include "algorithms/levenstein_distance.h"


unsigned long get_levenstein_distance(const_string_ptr s1, const_string_ptr s2) {
//    TODO: implement using arrays
//    TODO: implement via switching two arrays to save memory
//    allocate the matrix of intermediate results
    unsigned long **temp = malloc(sizeof(unsigned long*) * (s1->length + 1));
    unsigned long i;
    for (i = 0; i <= s1->length; i++)
        temp[i] = malloc(sizeof(unsigned long) * (s2->length + 1));

//    assign the distances to empty strings
    for (i = 0; i <= s1->length; i++)
        temp[i][0] = i;
    for (i = 0; i <= s2->length; i++)
        temp[0][i] = i;

    unsigned long j;
//    here we count i and j from 1, so when accessing the strings, we need to subtract 1
    for (i = 1; i <= s1->length; i++)
        for (j = 1; j <= s2->length; j++)
            if (s1->c_string[i-1] == s2->c_string[j-1])
                temp[i][j] = temp[i-1][j-1];
            else
                temp[i][j] = 1 + MIN3(temp[i-1][j], temp[i-1][j-1], temp[i][j-1]);

    for (i = 0; i <= s1->length; i++) {
        for (j = 0; j <= s2->length; j++)
            printf("%lu, ", temp[i][j]);
        printf("\n");
    }

    unsigned long result = temp[s1->length][s2->length];
    for (i = 0; i <= s1->length; i++)
        free(temp[i]);
    free(temp);
    return result;
}

