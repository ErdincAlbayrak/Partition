cmake_minimum_required(VERSION 3.8)
project(Partition)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c PriorityQueue.c PriorityQueue.h Heap.c Heap.h)
add_executable(Partition ${SOURCE_FILES})