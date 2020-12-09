/*
 *  线性表，数据结构定义
 * */

#ifndef SEQ_LIST_H
#define SEQ_LIST_H

#include "project_config.h"

#define SEQ_LIST_INIT_SIZE  100         // 线性表存储空间-初始分配量
#define LIST_INCREMENT      10          // 线性表存储空间-分配增量

/*  线性表, 数据项比较函数。 返回值 0, 表示比较成功  */
typedef bool (*compare_func)(ElemType a, ElemType b);

/*  线性表, 数据项迭代函数  */
typedef void (*visit_func)(ElemType e);

typedef struct
{
    ElemType *elem;                     // 存储空间, 基地址
    int length;                         // 当前长度
    int list_size;                      // 线性表-存储总长度
   
}SeqList;


/*
 *  线性表初始化
 * */
void SeqList_init(SeqList *list);

/*
 *  线性表销毁
 * */
void SeqList_destroy_list(SeqList *list);

/*
 *  清空线性表
 * */
void SeqList_clear(SeqList *list);

/*
 *  判断线性表是否为空
 * */
bool SeqList_empty(const SeqList *list);

/*
 *  查询线性表长度
 * */
int SeqList_length(const SeqList *list);

/*
 * 查询线性表第 idx 个数据元素对象, idx 从1开始计数 
 * */
bool SeqList_get_elem(const SeqList *list, int idx, ElemType *e);

/*
 *  查询线性表，数据元素e, 所在的下标。（下标从1开始计数）
 * */
int SeqList_locate_elem(const SeqList *list, ElemType e, compare_func compare); 

/*
 *  查询线性表，数据元素 cur_e的前驱元素
 * */
bool SeqList_prior_elem(const SeqList *list, ElemType cur_e, ElemType *pre_e);

/*
 *  查询线性表，数据元素 cur_e的后继元素
 * */
bool SeqList_next_elem(const SeqList *list, ElemType cur_e, ElemType *next_e);

/*
 *  线性表, 在第idx 位置插入元素, idx 从1开始计数
 * */
bool SeqList_insert(SeqList *list, int idx, ElemType e);

/*
 *  线性表，删除第 idx 位置的元素, idx 从1开始计数 
 * */
bool SeqList_delete(SeqList *list, int idx, ElemType *e);

/*
 *  线性表，使用 visit 函数, 访问每一个元素
 * */
void SeqList_traverse(const SeqList *list, visit_func visit);


#if defined ENABLE_UNITTEST

/*
 *  测试, 线性表的基本功能
 * */
void SeqList_test_01(void);

/*
 *  测试, 线性表长度超出长度的基本功能
 * */
void SeqList_test_02(void);

/*
 *  测试, 线性表性能测试
 * */
void SeqList_test_03(void);
#endif          /*  ENABLE_UNITTEST */

#endif          

