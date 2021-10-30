cmake_minimum_required(VERSION 3.19)
project(my_clib C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_library(my_clib my_clib.c my_clib.h lib/data_structures/BS_tree.c include/data_structures/BS_tree.h lib/data_structures/set_long.c include/data_structures/set_long.h include/common.h lib/data_structures/my_string.c lib/data_structures/array.c lib/algorithms/array_sorting.c include/algorithms/array_sorting.h lib/data_structures/matrix.c include/data_structures/matrix.h lib/data_structures/queue.c include/data_structures/queue.h lib/data_structures/graph.c include/data_structures/graph.h lib/data_structures/dictionary.c include/data_structures/dictionary.h lib/data_structures/KV_tree.c include/data_structures/KV_tree.h lib/data_structures/pair.c include/data_structures/pair.h lib/data_structures/long_number.c include/data_structures/long_number.h lib/algorithms/long_arithmetics.c include/algorithms/long_arithmetics.h lib/data_structures/decimal.c include/data_structures/decimal.h)

add_executable(main main.c include/data_structures/my_string.h include/data_structures.h include/algorithms.h include/algorithms/fast_substring_search.h lib/algorithms/fast_substring_search.c include/algorithms/levenstein_distance.h lib/algorithms/levenstein_distance.c include/data_structures/array.h lib/common.c lib/algorithms/greatest_common_subsequence.c include/algorithms/greatest_common_subsequence.h lib/data_structures/array.c lib/algorithms/array_sorting.c include/algorithms/array_sorting.h lib/data_structures/matrix.c include/data_structures/matrix.h lib/data_structures/linked_list.c include/data_structures/linked_list.h lib/data_structures/queue.c include/data_structures/queue.h lib/data_structures/graph.c include/data_structures/graph.h lib/data_structures/dictionary.c include/data_structures/dictionary.h lib/data_structures/KV_tree.c include/data_structures/KV_tree.h lib/data_structures/pair.c include/data_structures/pair.h lib/data_structures/long_number.c include/data_structures/long_number.h lib/algorithms/long_arithmetics.c include/algorithms/long_arithmetics.h lib/data_structures/decimal.c include/data_structures/decimal.h)
target_link_libraries(main my_clib)

add_executable(test test.c tests/data_structures/test_bs_tree.h lib/data_structures/set_long.c
        include/data_structures/set_long.h include/common.h tests/data_structures/test_set_long.h
        tests/algorithms/test_substring_search.c tests/algorithms/test_substring_search.h tests/data_structures_tests.h
        tests/algorithms_tests.h include/data_structures/my_string.h include/data_structures.h include/algorithms.h
        include/algorithms/fast_substring_search.h lib/algorithms/fast_substring_search.c
        include/algorithms/levenstein_distance.h lib/algorithms/levenstein_distance.c include/data_structures/array.h
        lib/common.c lib/algorithms/greatest_common_subsequence.c include/algorithms/greatest_common_subsequence.h
        lib/data_structures/array.c tests/test_helpers.c tests/test_helpers.h
        tests/algorithms/test_levenstein_distance.c tests/algorithms/test_levenstein_distance.h
        tests/algorithms/test_subsequence_search.c tests/algorithms/test_subsequence_search.h
        lib/algorithms/array_sorting.c include/algorithms/array_sorting.h tests/algorithms/test_array_sorting.c
        tests/algorithms/test_array_sorting.h lib/data_structures/matrix.c include/data_structures/matrix.h
        lib/data_structures/queue.c include/data_structures/queue.h lib/data_structures/graph.c
        include/data_structures/graph.h lib/data_structures/dictionary.c include/data_structures/dictionary.h
        lib/data_structures/KV_tree.c include/data_structures/KV_tree.h lib/data_structures/pair.c
        include/data_structures/pair.h include/data_structures/linked_list.h lib/data_structures/linked_list.c
        include/data_structures/queue.h lib/data_structures/queue.c lib/data_structures/long_number.c include/data_structures/long_number.h tests/data_structures/test_long_arithmetic.c tests/data_structures/test_long_arithmetic.h lib/algorithms/long_arithmetics.c include/algorithms/long_arithmetics.h lib/data_structures/decimal.c include/data_structures/decimal.h)
target_link_libraries(test my_clib)