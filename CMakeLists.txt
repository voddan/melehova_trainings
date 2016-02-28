cmake_minimum_required(VERSION 3.3)
project(melehova_trainings)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

#-------------------

add_executable(task_1-BizzBuss task_1-BizzBuss/bizz_buss.c)

#-------------------

add_executable(task_2-BadHashTable task_2-BadHashTable/hashtable.c
        task_2-BadHashTable/HASH/hashfunction.c
        task_2-BadHashTable/HASH/hashfunction.h
        task_2-BadHashTable/HASH/hashfunction_bfm.c
        task_2-BadHashTable/HASH/hashfunction_bfm.h
        task_2-BadHashTable/BFM/brain_fuck_machine.c
        task_2-BadHashTable/BFM/brain_fuck_machine.h)

add_executable(task_2-BadHashTable-test-BFM task_2-BadHashTable/HASH/test_bfm.c
        task_2-BadHashTable/HASH/hashfunction_bfm.c
        task_2-BadHashTable/BFM/brain_fuck_machine.c)

add_executable(task_2-BadHashTable-test-hashes task_2-BadHashTable/HASH/test_hashes.c
        task_2-BadHashTable/HASH/hashfunction.c
        task_2-BadHashTable/HASH/hashfunction_bfm.c
        task_2-BadHashTable/BFM/brain_fuck_machine.c
        )