//
// Created by Michal Ziobro on 30/07/2016.
//

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "test_task_queue.h"
#include "threads/thread_pool/task_queue.h"
#include "numbers.h"
#include "test/assertion.h"
#include "common/terminal.h"

#define NUM_WORKERS 10

static task_queue_t *task_queue;
static pthread_t worker[NUM_WORKERS];

static pthread_mutex_t runner_mutex;

static runner_res_t runner(runner_attr_t attr) {
    // some task runner
    return (runner_res_t) attr;
}

static void runner_res_handler(runner_res_t res) {
    // some runner res handler

    pthread_mutex_lock(&runner_mutex);

    (*((int *)res))++;

    pthread_mutex_unlock(&runner_mutex);
}

static int runner_attr = 0;
static int dequeue_count = 0;
static int enqueue_count = 0;

static void test_create(void) {

    pthread_mutex_init(&runner_mutex, NULL);
    task_queue_init(&task_queue);
}

static void test_clean(void) {

    for(int i=0; i<NUM_WORKERS; i++)
        pthread_join(worker[i], NULL);

    printf("enqueue count: %d\n", enqueue_count);
    printf("dequeue count: %d\n", dequeue_count);
    printf("task queue count: %d\n", task_queue_count(task_queue));
    printf("runner execution count: %d\n", runner_attr);
    assert_equal_int(runner_attr, min(dequeue_count, enqueue_count), "test_task_queue - result: ");

    task_queue_free(task_queue);
    pthread_mutex_destroy(&runner_mutex);
}

static void *test_enqueue(void *arg) {

    printf("test_enqueue(): %p\n", pthread_self());

    task_t *task;
    task_init(&task);
    task_fill(task, runner, &runner_attr, runner_res_handler);

    enqueue_task(task_queue, task);

    return 0;
}

static void *test_dequeue(void *arg) {

    printf("test_dequeue(): %p\n", pthread_self());

    task_t *task = dequeue_task_timed(task_queue, 2000);
    if(task) task_run(task);
    task_free(task);

    return 0;
}

static void run_tests(void) {

    TITLE_HEADER("test_task_queue");

    test_create(); // create task_queue

    printf("test_task_queue:\n");
    // create random number of test threads that enqueue and dequeue tasks
    srand(time(NULL));
    for(int i=0; i<NUM_WORKERS; i++) {
        int n = rand() % 2;
        if (n) {
            dequeue_count++;
            pthread_create(&(worker[i]), NULL, test_dequeue, NULL); // run dequeueing thread
        } else {
            enqueue_count++;
            pthread_create(&(worker[i]), NULL, test_enqueue, NULL); // run enqueueing thread
        }
    }

    test_clean(); // destroy task_queue
}

test_task_queue_t test_task_queue = { .run_tests = run_tests };