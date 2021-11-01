//
// Created by Mikhail Tsaritsyn on 01.11.2021.
//

#include "algorithms/addition_chain.h"


array_size_t* addition_chain(size_t n) {
    array_size_t *initial_chain = new_empty_array_size_t(10);
    array_size_t_append(initial_chain, 1);

    Queue *intermediate_chains = new_empty_queue(&print_array_size_t, &delete_array);
    queue_push(intermediate_chains, initial_chain);

    size_t i;
    array_size_t *result = NULL;
    int result_found = 0;
    while (1) {
        array_size_t *cur_chain = queue_pop(intermediate_chains);
        for (i = 0; i < cur_chain->length; i++) {
            size_t new_end = cur_chain->elements[i] + cur_chain->elements[cur_chain->length - 1];
            if (new_end > n) continue;

            array_size_t *new_chain = copy_array(cur_chain);
            append_to_array(new_chain, new_end);

            if (new_end == n){
                result_found = 1;
                result = new_chain;
                break;
            }
            else queue_push(intermediate_chains, new_chain);
        }
        if (result_found) break;
    }

    delete_queue(intermediate_chains);
    return result;
}