cmake_minimum_required(VERSION 3.6)
project(Concurrency)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES common/fifo_queue.h common/fifo_queue.c common/time.h common/time.c threads/thread_pool/task_queue.h threads/thread_pool/task_queue.c threads/generic_runner.h threads/generic_runner.c threads/thread_pool/thread_pool.h threads/thread_pool/thread_pool.c threads/generic_thread.h threads/generic_thread.c threads/generic_threads_manager.h threads/generic_threads_manager.c)
set(TEST_SOURCE_FILES test/test_fifo_queue.h test/test_fifo_queue.c test/test_task_queue.h test/test_task_queue.c test/test_thread_pool.h test/test_thread_pool.c test/test_threads_manager.h test/test_threads_manager.c)

# libraries paths
set(COMMON_FUNCTIONS_PATH /Users/michzio/Developer/MyProjects/BachelorDegree/c/common)
set(COLLECTIONS_PATH /Users/michzio/Developer/MyProjects/BachelorDegree/c/collections)
set(COMPARERS_PATH /Users/michzio/Developer/MyProjects/BachelorDegree/c/comparers)
set(UNIT_TESTS_PATH /Users/michzio/Developer/MyProjects/BachelorDegree/c/unit_tests)

add_library(Concurrency_Lib SHARED ${SOURCE_FILES})
set_target_properties(Concurrency_Lib PROPERTIES OUTPUT_NAME concurrency_shared)
target_link_libraries(Concurrency_Lib ${COMMON_FUNCTIONS_PATH}/libcommon_functions.a)
target_link_libraries(Concurrency_Lib ${COLLECTIONS_PATH}/libcollections.a)
target_link_libraries(Concurrency_Lib ${COMPARERS_PATH}/libcomparers.a)

add_library(Concurrency_Lib_Static ${SOURCE_FILES})
set_target_properties(Concurrency_Lib_Static PROPERTIES OUTPUT_NAME concurrency)
target_link_libraries(Concurrency_Lib_Static ${COMMON_FUNCTIONS_PATH}/libcommon_functions.a)
target_link_libraries(Concurrency_Lib_Static ${COLLECTIONS_PATH}/libcollections.a)
target_link_libraries(Concurrency_Lib_Static ${COMPARERS_PATH}/libcomparers.a)

add_executable(Concurrency main.c ${TEST_SOURCE_FILES})
target_link_libraries(Concurrency Concurrency_Lib_Static)
target_link_libraries(Concurrency ${UNIT_TESTS_PATH}/libunit_tests.a)