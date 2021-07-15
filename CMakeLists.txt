cmake_minimum_required(VERSION 3.19)
project(my_clib C)

set(CMAKE_C_STANDARD 99)

add_library(my_clib my_clib.c my_clib.h tree/BS_tree.c tree/BS_tree.h)

add_executable(main main.c)
target_link_libraries(main my_clib)

add_executable(test test.c tests/test_bs_tree.h)
target_link_libraries(test my_clib)