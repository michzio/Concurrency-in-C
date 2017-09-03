//
// Created by Michal Ziobro on 27/07/2016.
//

#ifndef CONCURRENCY_THREADS_GENERIC_THREAD_H
#define CONCURRENCY_THREADS_GENERIC_THREAD_H

#define _REENTRANT
#include <pthread.h>

#include "thread_pool/task_queue.h"

// create thread: generic thread
pthread_t thread_create(runner_t runner, runner_attr_t runner_attr);

#endif //CONCURRENCY_THREADS_GENERIC_THREAD_H
