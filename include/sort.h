/*
    排序算法
*/
#ifndef SORT_H
#define SORT_H


/*  比较函数 */
typedef int (*sort_compare_func)(const void *a, cosnt void *b);

/*  冒泡排序    */
void bubble_sort(void *base, sort_compare_func func);

/*  快速排序    */
void quick_sort(void *base, sort_compare_func func);

/*  选择排序    */
void select_sort(void *base, sort_compare_func func);

/*  插入排序    */
void insert_sort(void *base, sort_compare_func func);

/*  希尔排序    */
void xier_sort(void *base, sort_compare_func func);

/*  归并排序    */
void merge_sort(void *base, sort_compare_func func);

/*  堆排序    */
void heap_sort(void *base, sort_compare_func func);

/*  tim sort 排序*/
void tim_sort(void *base, sort_compare_func func);


#endif

