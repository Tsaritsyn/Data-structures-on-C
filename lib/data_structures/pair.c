//
// Created by Mikhail Tsaritsyn on 26.10.2021.
//

#include "data_structures/pair.h"


Pair* new_pair(void* first, void* second) {
    Pair* pair = malloc(sizeof(Pair));
    pair->first = first;
    pair->second = second;
    return pair;
}


void delete_pair(Pair* pair, void (*delete_first)(void*), void (*delete_second)(void*)) {
    delete_first(pair->first);
    delete_second(pair->second);
    free(pair);
}
