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
