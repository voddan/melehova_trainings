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
        task_2-BadHashTable/BFM/brain_fuck_machine.c)

#-------------------

add_executable(task_3-FixBugs task_3-FixBugs/fix_bugs.cpp)

add_executable(task_3-dokhlopkov task_3-FixBugs/dokhlopkov_lesson3_fix_bugs_2.cpp)

add_executable(task_3-checked task_3-FixBugs/dokhlopkov_checked_dvodopian_fix_bugs.cpp)

#-------------------

add_executable(task_3-measure-getc-1 task_3-measure-getc/test_1.c)
add_executable(task_3-measure-getc-5 task_3-measure-getc/test_5.c)
add_executable(task_3-measure-getc-30 task_3-measure-getc/test_30.c)
add_executable(task_3-measure-getc-1000 task_3-measure-getc/test_1000.c)

add_executable(task_3-measure-getc-n task_3-measure-getc/test_n.c)

#-------------------

add_library(task_4-loglib task_4-loglib/loglib.c)

link_libraries(task_4-loglib)
add_executable(task_4-loglib-main task_4-loglib/main.c)
