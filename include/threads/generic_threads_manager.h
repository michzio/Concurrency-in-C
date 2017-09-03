//
// Created by Michal Ziobro on 08/08/2016.
//

#ifndef CONCURRENCY_THREADS_GENERIC_THREADS_MANAGER_H
#define CONCURRENCY_THREADS_GENERIC_THREADS_MANAGER_H

#include <stdio.h>
#include "types.h"
#include "generic_runner.h"

struct threads_manager;
typedef struct threads_manager threads_manager_t;

// threads manager operations
result_t threads_manager_init(threads_manager_t **threads_manager, size_t max_limit);
void threads_manager_set_max_limit(threads_manager_t *threads_manager, size_t max_limit);
size_t threads_manager_max_limit(threads_manager_t *threads_manager);
size_t threads_manager_count(threads_manager_t *threads_manager);
pthread_t *threads_manager_threads(threads_manager_t *threads_manager);
result_t wait_for_thread(threads_manager_t *threads_manager, runner_t runner, runner_attr_t runner_attr);
result_t timed_wait_for_thread(threads_manager_t *threads_manager, const int ms_timeout, runner_t runner, runner_attr_t runner_attr);
void threads_manager_free(threads_manager_t *threads_manager);

#endif //CONCURRENCY_THREADS_GENERIC_THREADS_MANAGER_H
