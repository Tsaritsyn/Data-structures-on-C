//
// Created by Mikhail Tsaritsyn on 25.10.2021.
//

#include "data_structures/queue.h"


Queue* new_empty_queue(void) {
    Queue* queue = malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = queue->head;
    return queue;
}


int is_queue_empty(const Queue* queue) {
    return queue->head == NULL;
}


void queue_push(Queue* queue, size_t data) {
    if (is_queue_empty(queue)) {
        queue->head = new_list_node(data);
        queue->tail = queue->head;
    }
    else {
        attach_list_node(queue->tail, new_list_node(data));
        queue->tail = queue->tail->next;
    }
}


size_t queue_pop(Queue* queue) {
    if (is_queue_empty(queue))
        return 0;

    size_t data = queue->head->data;
    list_node* new_head = queue->head->next;
//    we do not use delete_node() here, because we want to preserve the data stored
    free(queue->head);
    queue->head = new_head;
    return data;
}


void delete_queue(Queue* queue, void (*delete_data)(size_t)) {
    while (!is_queue_empty(queue)) {
        size_t data = queue_pop(queue);
        delete_data(data);
    }
    free(queue);
}


void print_queue(const Queue* queue, void (*print_data)(void*)) {
    list_node* node = queue->head;
    printf("queue(");
    while (node != NULL) {
        print_data((void *) node->data);
        printf("%s", (node->next == NULL) ? "" : ", ");
        node = node->next;
    }
    printf(")\n");
}
