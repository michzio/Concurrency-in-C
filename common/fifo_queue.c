//
// Created by Michal Ziobro on 29/07/2016.
//

#include <stdlib.h>
#include <stdio.h>
#include "../../collections/linked_list/doubly_linked_list.h"
#include "fifo_queue.h"

struct fifo_queue {
    doubly_linked_list_t *queue;
};

/**
 * function allocates memory for fifo queue
 * and its internal doubly linked list used
 * as the queue data structure. it takes as
 * second param allocator struct used by
 * doubly linked list. This allocator can be set to null
 * when list won't be the owner of data, responsible
 * for their allocation/deallocation.
 */
void fifo_init(fifo_queue_t **fifo, allocator_t *allocator) {

    *fifo = malloc(sizeof(fifo_queue_t));
    dl_list_init( &((*fifo)->queue), allocator );
}

void fifo_enqueue(fifo_queue_t *fifo, void *data, size_t data_size) {
    dl_list_push_front(fifo->queue, data, data_size);
}

void *fifo_dequeue(fifo_queue_t *fifo, size_t *data_size) {

    allocator_t *allocator;
    doubly_linked_node_t *node;
    size_t tmp_size;
    void *tmp_data;
    void *data;

    // get data and its size from the last node in the queue
    if((node = dl_list_back(fifo->queue)) == NULL) {
        fprintf(stderr, "back: queue is empty!\n");
        data_size = NULL;
        return NULL;
    };
    tmp_data = dl_unwrap_data(node, &tmp_size);

    // copy retrieved data
    if( (allocator = dl_list_allocator(fifo->queue)) != NULL ) {
        // if nodes allocate/deallocate data copy it properly using allocator struct
        allocate_handler_t allocate = allocator_allocate(allocator);
        allocate(&data, tmp_data, tmp_size);
    } else {
        // if nodes store pointers and client allocate/deallocate data copy just pointer
        data = tmp_data;
    }

    // remove the last node in the queue
    dl_list_pop_back(fifo->queue);

    if(data_size != NULL) *data_size = tmp_size; // return size of data through pointer argument
    return data;
}

void fifo_free(fifo_queue_t *fifo) {

    dl_list_free(fifo->queue);
    free(fifo);
    fifo = NULL;
}