/*
    排序算法
*/
#ifndef SORT_H
#define SORT_H

#include "project_config.h"


/*  比较函数 */
typedef int (*sort_compare_func)(const void *a, const void *b);

/*  迭代访问每一个数据元素  */
bool sort_traverse(const void *base, size_t len, size_t size, bool(*visit_func)(void *elem));

/*  冒泡排序    */
void bubble_sort(void *base, size_t len, size_t size, sort_compare_func compare_func);

/*  快速排序    */
void quick_sort(void *base, size_t len, size_t size, sort_compare_func compare_func);

/*  选择排序    */
void select_sort(void *base, size_t len, size_t size, sort_compare_func compare_func);

/*  插入排序    */
void insert_sort(void *base, size_t len, size_t size, sort_compare_func compare_func);

/*  希尔排序    */
void xier_sort(void *base, size_t len, size_t size, sort_compare_func compare_func);

/*  归并排序    */
void merger_sort(void *base, size_t len, size_t size, sort_compare_func compare_func);

/*  堆排序    */
void heap_sort(void *base, size_t len, size_t size, sort_compare_func compare_func);

/*  tim sort 排序*/
void tim_sort(void *base, size_t len, size_t size, sort_compare_func compare_func);


#if defined ENABLE_UNITTEST

void Sort_test_01(void);

#endif

#endif

