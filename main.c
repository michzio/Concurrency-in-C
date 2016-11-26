#include <stdio.h>
#include "test/test_fifo_queue.h"
#include "test/test_task_queue.h"
#include "test/test_thread_pool.h"
#include "test/test_threads_manager.h"

int main() {

    printf("Concurrency Library\n");

    test_fifo_queue.run_tests();
    test_task_queue.run_tests();
    test_thread_pool.run_tests();
    test_threads_manager.run_tests();

    return 0;
}