//
// Created by Michal Ziobro on 27/07/2016.
//

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include "threads/generic_thread.h"

// create thread: generic thread
pthread_t thread_create(runner_t runner, runner_attr_t runner_attr) {

    pthread_t thread;
    pthread_attr_t thread_attr;

    // fill pthread attributes
    pthread_attr_init(&thread_attr);

    if( pthread_create(&thread, &thread_attr, runner, runner_attr) != 0 )  {
        fprintf(stderr, "pthread_create: failed to create thread.\n");
        return NULL;
    }

    return thread;
}