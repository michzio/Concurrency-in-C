//
// Created by Michal Ziobro on 28/07/2016.
//

#ifndef CONCURRENCY_THREADS_TASK_QUEUE_H
#define CONCURRENCY_THREADS_TASK_QUEUE_H

#include "common/allocator.h"
#include "../generic_runner.h"

// TASK QUEUE
struct task_queue;
typedef struct task_queue task_queue_t;

// TASK
struct task;
typedef struct task task_t;

// task queue operations
void task_queue_init(task_queue_t **task_queue);
void enqueue_task(task_queue_t *task_queue, task_t *task);
task_t *dequeue_task(task_queue_t *task_queue);
task_t *dequeue_task_timed(task_queue_t *task_queue, int ms_timeout);
int task_queue_count(task_queue_t *task_queue);
void task_queue_free(task_queue_t *task_queue);

// task operations
void task_init(task_t **task);
void task_fill(task_t *task, runner_t runner, runner_attr_t runner_attr, runner_res_handler_t runner_res_handler);
void task_run(task_t *task);
void task_free(task_t *task);

#endif //CONCURRENCY_THREADS_TASK_QUEUE_H
