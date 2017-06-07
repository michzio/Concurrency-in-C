cmake_minimum_required(VERSION 3.6)
project(Concurrency)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES common/fifo_queue.h common/fifo_queue.c common/time.h common/time.c threads/thread_pool/task_queue.h threads/thread_pool/task_queue.c threads/generic_runner.h threads/generic_runner.c threads/thread_pool/thread_pool.h threads/thread_pool/thread_pool.c threads/generic_thread.h threads/generic_thread.c threads/generic_threads_manager.h threads/generic_threads_manager.c)
set(TEST_SOURCE_FILES test/test_fifo_queue.h test/test_fifo_queue.c test/test_task_queue.h test/test_task_queue.c test/test_thread_pool.h test/test_thread_pool.c test/test_threads_manager.h test/test_threads_manager.c)

if(CYGWIN)
    # windows cygwin
    message("building for Cygwin")
else()
    # unix
    message("building for Unix")
endif()

# libraries paths
set(COMMON_FUNCTIONS_PATH ${CMAKE_SOURCE_DIR}/../common)
set(COLLECTIONS_PATH ${CMAKE_SOURCE_DIR}/../collections)
set(COMPARERS_PATH ${CMAKE_SOURCE_DIR}/../comparers)
set(UNIT_TESTS_PATH ${CMAKE_SOURCE_DIR}/../unit_tests)
if(CYGWIN)
    # windows cygwin
    set(COMMON_FUNCTIONS_LIB_PATH ${COMMON_FUNCTIONS_PATH}/output/windows/lib/static/libcommon_functions.a)
    set(COLLECTIONS_LIB_PATH ${COLLECTIONS_PATH}/output/windows/lib/static/libcollections.a)
    set(COMPARERS_LIB_PATH ${COMPARERS_PATH}/output/windows/lib/static/libcomparers.a)
    set(UNIT_TESTS_LIB_PATH ${UNIT_TESTS_PATH}/output/windows/lib/static/libunit_tests.a)
else()
    # unix
    set(COMMON_FUNCTIONS_LIB_PATH ${COMMON_FUNCTIONS_PATH}/output/unix/lib/static/libcommon_functions.a)
    set(COLLECTIONS_LIB_PATH ${COLLECTIONS_PATH}/output/unix/lib/static/libcollections.a)
    set(COMPARERS_LIB_PATH ${COMPARERS_PATH}/output/unix/lib/static/libcomparers.a)
    set(UNIT_TESTS_LIB_PATH ${UNIT_TESTS_PATH}/output/unix/lib/static/libunit_tests.a)
endif()

add_library(Concurrency_Lib SHARED ${SOURCE_FILES})
set_target_properties(Concurrency_Lib PROPERTIES OUTPUT_NAME concurrency)
target_link_libraries(Concurrency_Lib ${COMMON_FUNCTIONS_LIB_PATH})
target_link_libraries(Concurrency_Lib ${COLLECTIONS_LIB_PATH})
target_link_libraries(Concurrency_Lib ${COMPARERS_LIB_PATH})

add_library(Concurrency_Lib_Static ${SOURCE_FILES})
set_target_properties(Concurrency_Lib_Static PROPERTIES OUTPUT_NAME concurrency)
target_link_libraries(Concurrency_Lib_Static ${COMMON_FUNCTIONS_LIB_PATH})
target_link_libraries(Concurrency_Lib_Static ${COLLECTIONS_LIB_PATH})
target_link_libraries(Concurrency_Lib_Static ${COMPARERS_LIB_PATH})

add_executable(Concurrency main.c ${TEST_SOURCE_FILES})
set_target_properties(Concurrency PROPERTIES OUTPUT_NAME concurrency)
target_link_libraries(Concurrency Concurrency_Lib_Static)
target_link_libraries(Concurrency ${UNIT_TESTS_LIB_PATH})

# install targets (executables, shared libraries, static libraries) in current project source directory
add_custom_target(Install_${PROJECT_NAME}
                  $(MAKE) install
                  DEPENDS ${PROJECT_NAME}
                  COMMENT "Installing ${PROJECT_NAME}")

if(CYGWIN)
    # windows cygwin
    set(RUNTIME_DEST_DIR ${CMAKE_SOURCE_DIR}/output/windows/bin)
    set(LIBRARY_DEST_DIR ${CMAKE_SOURCE_DIR}/output/windows/lib)
    set(ARCHIVE_DEST_DIR ${CMAKE_SOURCE_DIR}/output/windows/lib/static)
else()
    # unix
    set(RUNTIME_DEST_DIR ${CMAKE_SOURCE_DIR}/output/unix/bin)
    set(LIBRARY_DEST_DIR ${CMAKE_SOURCE_DIR}/output/unix/lib)
    set(ARCHIVE_DEST_DIR ${CMAKE_SOURCE_DIR}/output/unix/lib/static)
endif()

install(TARGETS Concurrency Concurrency_Lib Concurrency_Lib_Static
        RUNTIME DESTINATION ${RUNTIME_DEST_DIR}
        LIBRARY DESTINATION ${LIBRARY_DEST_DIR}
        ARCHIVE DESTINATION ${ARCHIVE_DEST_DIR})