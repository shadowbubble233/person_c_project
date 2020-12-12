/*
 *  静态链表，数据结构定义
 * */

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "project_config.h"

/*
    -1 作为尾结点标志符
  idx   | elem | cur | 
    0     elem   -1
 
 * */


#define STATIC_LIST_INIT_SIZE   100     // 线性表存储空间-初始分配量
#define STATIC_LIST_INCREMENT   10      // 线性表存储空间-分配增量

typedef struct
{
    ElemType elem;                      // 元素内容
    int next;                           // 下一个元素的下标
}StaticNode;


typedef struct
{
    StaticNode *data;                   // 存储空间, 基地址
    int length;                         // 当前长度
    int free_cur;                       // 空闲链表, 头索引
    int list_size;                      // 静态链表-存储总长度
}StaticList;



/*
 *  静态链表初始化
 * */
void StaticList_init(StaticList *list);

/*
 *  静态链表销毁
 * */
void StaticList_destroy_list(StaticList *list);

/*
 *  清空静态链表
 * */
void StaticList_clear(StaticList *list);

/*
 *  判断静态链表是否为空
 * */
bool StaticList_empty(const StaticList *list);

/*
 *  查询静态链表长度
 * */
int StaticList_length(const StaticList *list);

/*
 * 查询静态链表第 idx 个数据元素对象, idx 从1开始计数 
 * */
bool StaticList_get_elem(const StaticList *list, int idx, ElemType *e);

/*
 *  查询静态链表，数据元素e, 所在的下标。（下标从1开始计数）
 * */
int StaticList_locate_elem(const StaticList *list, ElemType e, bool (*compare_func)(ElemType a, ElemType b)); 

/*
 *  查询静态链表，数据元素 cur_e的前驱元素
 * */
bool StaticList_prior_elem(const StaticList *list, ElemType cur_e, ElemType *pre_e);

/*
 *  查询静态链表，数据元素 cur_e的后继元素
 * */
bool StaticList_next_elem(const StaticList *list, ElemType cur_e, ElemType *next_e);

/*
 *  静态链表, 在第idx 位置插入元素, idx 从1开始计数
 * */
bool StaticList_insert(StaticList *list, int idx, ElemType e);

/*
 *  静态链表，删除第 idx 位置的元素, idx 从1开始计数 
 * */
bool StaticList_delete(StaticList *list, int idx, ElemType *e);

/*
 *  静态链表，使用 visit 函数, 访问每一个元素
 * */
void StaticList_traverse(const StaticList *list, void (*visit_func)(ElemType e));

/*
 *  静态链表, dump 数据结构
 * */
void StaticList_print(const StaticList *list);

#if defined ENABLE_UNITTEST

/*
 *  测试, 静态链表的基本功能
 * */
void StaticList_test_01(void);

#endif          /*  ENABLE_UNITTEST */

#endif          

