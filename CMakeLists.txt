cmake_minimum_required(VERSION 3.19)
project(my_clib C)

set(CMAKE_C_STANDARD 99)

add_library(my_clib my_clib.c my_clib.h lib/BS_tree.c data_structures/BS_tree.h lib/set_long.c data_structures/set_long.h common.h)

add_executable(main main.c)
target_link_libraries(main my_clib)

add_executable(test test.c tests/test_bs_tree.h lib/set_long.c data_structures/set_long.h common.h tests/test_set_long.h)
target_link_libraries(test my_clib)