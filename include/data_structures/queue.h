//
// Created by Mikhail Tsaritsyn on 25.10.2021.
//

#ifndef MY_CLIB_QUEUE_H
#define MY_CLIB_QUEUE_H

#include <stdio.h>

#include "linked_list.h"


typedef struct Queue {
    list_node *head, *tail;
    void (*print_data)(const void *);
    void (*delete_data)(size_t);
} Queue;


/**
 * @param print_data function that will print the structure pointed at by the data
 * @param delete_data function that will delete the structure pointed at by the data and free its memory
 * @return a pointer to an empty queue
 */
Queue* new_empty_queue(void (*print_data)(const void *), void (*delete_data)(size_t));


/**
 * @return positive if the given queue contains no data and 0 otherwise
 */
int is_queue_empty(const Queue* queue);


/**
 * Puts the given data to the end of the given queue.
 */
void queue_push(Queue* queue, size_t data);


/**
 * Removes the data from the beginning of the queue (memory pointed at by the data remains untouched).
 *
 * @return the data stored in the beginning of the queue
 */
size_t queue_pop(Queue* queue);


/**
 * Deletes the queue with all the data stored within.
 */
void delete_queue(Queue* queue);


/**
 * Displays the content of the given queue from the first element to the last one;
 */
void print_queue(const Queue* queue);


#endif //MY_CLIB_QUEUE_H
