//
// Created by Michal Ziobro on 30/07/2016.
//

#ifndef CONCURRENCY_TEST_TASK_QUEUE_H
#define CONCURRENCY_TEST_TASK_QUEUE_H

typedef struct {
    void (*run_tests)(void);
} test_task_queue_t;

extern test_task_queue_t test_task_queue;

#endif //CONCURRENCY_TEST_TASK_QUEUE_H
