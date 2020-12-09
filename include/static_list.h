/*
 *  静态链表，数据结构定义
 * */

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "project_config.h"

#define STATIC_LIST_INIT_SIZE  100         // 线性表存储空间-初始分配量
#define LIST_INCREMENT      10          // 线性表存储空间-分配增量

typedef int ElemType;                   // 线性表-存储元素类型

/*  单列表, 数据项比较函数。 返回值 0, 表示比较成功  */
typedef bool (*compare_func)(ElemType a, ElemType b);

/*  单列表, 数据项迭代函数  */
typedef void (*visit_func)(ElemType e);

typedef struct
{
    ElemType *elem;                     // 存储空间, 基地址
    int length;                         // 当前长度
    int list_size;                      // 线性表-存储总长度
   
}StaticList;


/*
 *  单列表初始化
 * */
void StaticList_init(StaticList *list);

/*
 *  单列表销毁
 * */
void StaticList_destroy_list(StaticList *list);

/*
 *  清空单列表
 * */
void StaticList_clear(StaticList *list);

/*
 *  判断单列表是否为空
 * */
bool StaticList_Empty(const StaticList *list);

/*
 *  查询单列表长度
 * */
int StaticList_length(const StaticList *list);

/*
 * 查询单列表第 idx 个数据元素对象, idx 从1开始计数 
 * */
bool StaticList_get_elem(const StaticList *list, int idx, ElemType *e);

/*
 *  查询单列表，数据元素e, 所在的下标。（下标从1开始计数）
 * */
int StaticList_locate_elem(const StaticList *list, ElemType e, compare_func compare); 

/*
 *  查询单列表，数据元素 cur_e的前驱元素
 * */
bool StaticList_prior_elem(const StaticList *list, ElemType cur_e, ElemType *pre_e);

/*
 *  查询单列表，数据元素 cur_e的后继元素
 * */
bool StaticList_next_elem(const StaticList *list, ElemType cur_e, ElemType *next_e);

/*
 *  单列表, 在第idx 位置插入元素, idx 从1开始计数
 * */
bool StaticList_insert(StaticList *list, int idx, ElemType e);

/*
 *  单列表，删除第 idx 位置的元素, idx 从1开始计数 
 * */
bool StaticList_delete(StaticList *list, int idx, ElemType *e);

/*
 *  单列表，使用 visit 函数, 访问每一个元素
 * */
void StaticList_traverse(const StaticList *list, visit_func visit);


#if defined ENABLE_UNITTEST

/*
 *  测试, 单列表的基本功能
 * */
void StaticList_test_01(void);

/*
 *  测试, 单列表长度超出长度的基本功能
 * */
void StaticList_test_02(void);

/*
 *  测试, 单列表性能测试
 * */
void StaticList_test_03(void);
#endif          /*  ENABLE_UNITTEST */

#endif          

