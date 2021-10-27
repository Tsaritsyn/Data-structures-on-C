//
// Created by Mikhail Tsaritsyn on 19.10.2021.
//

#ifndef MY_CLIB_GREATEST_COMMON_SUBSEQUENCE_H
#define MY_CLIB_GREATEST_COMMON_SUBSEQUENCE_H


#include <assert.h>

#include "data_structures/array.h"
#include "data_structures/matrix.h"


/**
 * @return the longest common subsequence of two given arrays
 */
#define declare_gcs_search(type) \
array_##type##_ptr greatest_common_##type##_subsequence(const array_##type *arr1, const array_##type *arr2);

declare_gcs_search(int)
declare_gcs_search(short)
declare_gcs_search(char)
declare_gcs_search(long)
declare_gcs_search(float)
declare_gcs_search(double)
declare_gcs_search(u_int)
declare_gcs_search(u_short)
declare_gcs_search(u_long)

#endif //MY_CLIB_GREATEST_COMMON_SUBSEQUENCE_H
