cmake_minimum_required(VERSION 3.6)
project(Concurrency)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(SOURCE_FILES include/common/fifo_queue.h src/common/fifo_queue.c include/common/time.h src/common/time.c include/threads/thread_pool/task_queue.h src/threads/thread_pool/task_queue.c include/threads/generic_runner.h src/threads/generic_runner.c include/threads/thread_pool/thread_pool.h src/threads/thread_pool/thread_pool.c include/threads/generic_thread.h src/threads/generic_thread.c include/threads/generic_threads_manager.h src/threads/generic_threads_manager.c)
set(TEST_SOURCE_FILES test/test_fifo_queue.h test/test_fifo_queue.c test/test_task_queue.h test/test_task_queue.c test/test_thread_pool.h test/test_thread_pool.c test/test_threads_manager.h test/test_threads_manager.c)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs)
if(CYGWIN)
    # windows cygwin
    message("building for Cygwin")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/lib/cygwin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/lib/cygwin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/bin/cygwin)
elseif(APPLE)
    # apple
    message("building for Apple")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/lib/apple)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/lib/apple)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/bin/apple)
else()
    # unix
    message("building for Unix")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/lib/unix)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/lib/unix)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/outputs/bin/unix)
endif()

### MAKING LIBRARIES ###
# include current project headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# subprojects paths
if(NOT DEFINED COMMON_FUNCTIONS_SRC_DIR)
    set(COMMON_FUNCTIONS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../common)
    set(COMMON_FUNCTIONS_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../common/outputs)
endif()
set(COLLECTIONS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../collections)
set(COLLECTIONS_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../collections/outputs)

# add subprojects
if(NOT DEFINED COMMON_FUNCTIONS_SRC_DIR)
    add_subdirectory( # Specifies the directory of the CMakeLists.txt file.
                      ${COMMON_FUNCTIONS_SRC_DIR}
                      # Specifies the directory for the build outputs.
                      ${COMMON_FUNCTIONS_BUILD_DIR} )
endif()
add_subdirectory( # Specifies the directory of the CMakeLists.txt file.
                  ${COLLECTIONS_SRC_DIR}
                  # Specifies the directory for the build outputs.
                  ${COLLECTIONS_BUILD_DIR} )

# include header files of subproject
set(COMPARERS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../comparers)
include_directories(${COMMON_FUNCTIONS_SRC_DIR}/include)
include_directories(${COMMON_FUNCTIONS_SRC_DIR}/libraries)
include_directories(${COMPARERS_SRC_DIR}/include)
include_directories(${COLLECTIONS_SRC_DIR}/include)

# current project shared and static libraries creation
# SHARED
add_library(Concurrency_Lib SHARED ${SOURCE_FILES})
set_target_properties(Concurrency_Lib PROPERTIES OUTPUT_NAME concurrency)
target_link_libraries(Concurrency_Lib Common_Functions_Lib)
target_link_libraries(Concurrency_Lib Comparers_Lib)
target_link_libraries(Concurrency_Lib Collections_Lib)

# STATIC
add_library(Concurrency_Lib_Static ${SOURCE_FILES})
set_target_properties(Concurrency_Lib_Static PROPERTIES OUTPUT_NAME concurrency)
target_link_libraries(Concurrency_Lib_Static Common_Functions_Lib_Static)
target_link_libraries(Concurrency_Lib_Static Comparers_Lib_Static)
target_link_libraries(Concurrency_Lib_Static Collections_Lib_Static)

### MAKING EXECUTABLE ###
# executable's libraries paths
set(UNIT_TESTS_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../unit_tests)
if(CYGWIN)
    # windows cygwin
    set(UNIT_TESTS_LIB_PATH ${UNIT_TESTS_SRC_DIR}/outputs/lib/cygwin/libunit_tests.so)
elseif(APPLE)
    # apple
    set(UNIT_TESTS_LIB_PATH ${UNIT_TESTS_SRC_DIR}/outputs/lib/apple/libunit_tests.dylib)
else()
    # unix
    set(UNIT_TESTS_LIB_PATH ${UNIT_TESTS_SRC_DIR}/outputs/lib/unix/libunit_tests.so)
endif()

# executable's libraries import
add_library(Unit_Test_Lib SHARED IMPORTED)
set_target_properties( Unit_Test_Lib PROPERTIES IMPORTED_LOCATION ${UNIT_TESTS_LIB_PATH} )

# executable's libraries include headers
include_directories( ${UNIT_TESTS_SRC_DIR}/include )

# current project executable creation
add_executable(Concurrency src/main.c ${TEST_SOURCE_FILES})
set_target_properties(Concurrency PROPERTIES OUTPUT_NAME concurrency)
target_link_libraries(Concurrency Concurrency_Lib)
target_link_libraries(Concurrency Unit_Test_Lib)