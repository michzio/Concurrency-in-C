//
// Created by Michal Ziobro on 29/07/2016.
//

#ifndef CONCURRENCY_TEST_FIFO_QUEUE_H
#define CONCURRENCY_TEST_FIFO_QUEUE_H

typedef struct {
    void (*run_tests)(void);
} test_fifo_queue_t;

extern test_fifo_queue_t test_fifo_queue;

#endif //CONCURRENCY_TEST_FIFO_QUEUE_H
