//
// Created by Michal Ziobro on 01/08/2016.
//

#ifndef CONCURRENCY_TEST_THREAD_POOL_H
#define CONCURRENCY_TEST_THREAD_POOL_H

typedef struct {
    void (*run_tests)(void);
} test_thread_pool_t;

extern test_thread_pool_t test_thread_pool;

#endif //CONCURRENCY_TEST_THREAD_POOL_H
