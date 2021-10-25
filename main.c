//
// Created by Mikhail Tsaritsyn on 14.07.2021.
//

#include "my_clib.h"
#include "stdio.h"


int main() {
    Queue* queue = new_empty_queue(&print_array_int, &delete_array);
    print_queue(queue);

    size_t i;
    for (i = 0; i < 10; i++)
        queue_push(queue, new_empty_array_int(10));
    print_queue(queue);

    delete_queue(queue);

    return 0;
}

