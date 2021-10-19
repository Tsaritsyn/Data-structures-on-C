cmake_minimum_required(VERSION 3.19)
project(my_clib C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_library(my_clib my_clib.c my_clib.h lib/data_structures/BS_tree.c include/data_structures/BS_tree.h lib/data_structures/set_long.c include/data_structures/set_long.h include/common.h lib/data_structures/my_string.c lib/data_structures/array.c)

add_executable(main main.c include/data_structures/my_string.h include/data_structures.h include/algorithms.h include/algorithms/fast_substring_search.h lib/algorithms/fast_substring_search.c include/algorithms/levenstein_distance.h lib/algorithms/levenstein_distance.c include/data_structures/array.h lib/common.c lib/algorithms/greatest_common_subsequence.c include/algorithms/greatest_common_subsequence.h lib/data_structures/array.c)
target_link_libraries(main my_clib)

add_executable(test test.c tests/data_structures/test_bs_tree.h lib/data_structures/set_long.c include/data_structures/set_long.h include/common.h tests/data_structures/test_set_long.h)
target_link_libraries(test my_clib)