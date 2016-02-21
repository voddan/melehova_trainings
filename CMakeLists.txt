cmake_minimum_required(VERSION 3.3)
project(melehova_trainings)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

#-------------------

add_executable(task_1-BizzBuss task_1-BizzBuss/bizz_buss.c)