//
// Created by Michal Ziobro on 09/08/2016.
//

#ifndef CONCURRENCY_THREADS_GENERIC_RUNNER_H
#define CONCURRENCY_THREADS_GENERIC_RUNNER_H

#include "types.h"

// runner type definition
typedef void * runner_attr_t;
typedef void * runner_res_t;
typedef runner_res_t (*runner_t)(runner_attr_t);
typedef void (*runner_res_handler_t) (runner_res_t);

// managed thread runner ( runner_t and runner_attr_t wrapper to enable usage with threads managed by threads manager)
struct managed_thread_runner_attr;
typedef struct managed_thread_runner_attr managed_thread_runner_attr_t;
runner_res_t managed_thread_runner(managed_thread_runner_attr_t *attr);

result_t managed_thread_runner_attr_init(managed_thread_runner_attr_t **managed_thread_runner_attr);
void managed_thread_runner_attr_fill(managed_thread_runner_attr_t *managed_thread_runner_attr, runner_t runner, runner_attr_t runner_attr, callback_t callback, callback_attr_t callback_attr);
void managed_thread_runner_attr_free(managed_thread_runner_attr_t *managed_thread_runner_attr);

#endif //CONCURRENCY_THREADS_RUNNER_H
