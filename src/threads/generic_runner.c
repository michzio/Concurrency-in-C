//
// Created by Michal Ziobro on 09/08/2016.
//
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "threads/generic_runner.h"

// managed thread runner
/**
 * wrapping runner_t and runner_attr_t into single structure to enable usage with
 * threads managed by threads manager
 */
struct managed_thread_runner_attr {
    runner_t runner;
    runner_attr_t runner_attr;
    callback_t callback;
    callback_attr_t callback_attr;
};
/**
 * managed thread runner function used to wrap invocation of generic runner
 * function with runner_attr as its only param to make possible usage
 * of runner_t and runner_attr_t with managed threads and threads manager object
 */
runner_res_t managed_thread_runner(managed_thread_runner_attr_t *attr) {

    runner_res_t runner_res = attr->runner(attr->runner_attr);
    if(attr->callback != NULL)
        attr->callback(attr->callback_attr, (void *) runner_res);
    managed_thread_runner_attr_free(attr);
    return NULL;
}

// managed thread runner attributes operations
result_t managed_thread_runner_attr_init(managed_thread_runner_attr_t **managed_thread_runner_attr) {

    if( ( *managed_thread_runner_attr = malloc(sizeof(managed_thread_runner_attr_t)) ) == NULL ) {
        fprintf(stderr, "malloc: failed to allocate managed_thread_runner_attr.\n");
        return FAILURE;
    }
    return SUCCESS;
}
void managed_thread_runner_attr_fill(managed_thread_runner_attr_t *managed_thread_runner_attr, runner_t runner, runner_attr_t runner_attr, callback_t callback, callback_attr_t callback_attr) {

    memset(managed_thread_runner_attr, 0, sizeof(*managed_thread_runner_attr));
    managed_thread_runner_attr->runner = runner;
    managed_thread_runner_attr->runner_attr = runner_attr;
    managed_thread_runner_attr->callback = callback;
    managed_thread_runner_attr->callback_attr = callback_attr;
}
void managed_thread_runner_attr_free(managed_thread_runner_attr_t *managed_thread_runner_attr) {

    free(managed_thread_runner_attr);
}