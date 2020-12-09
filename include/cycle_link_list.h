/*
 *  循环链式线性表, 数据结构定义
 * */
#ifndef CYCLE_LINK_LIST_H
#define CYCLE_LINK_LIST_H

#include "project_config.h"


typedef int ElemType;                   // 线性链表-存储元素类型

/*  线性链表, 数据项比较函数。 返回值 0, 比较成功 */
typedef bool (*compare_func)(ElemType a, ElemType b);

/*  线性链表, 数据项迭代函数 */
typedef void (*visit_func)(ElemType e);

typedef struct _cycle_node
{
    ElemType elem;                      // 数据域
    struct _cycle_node *next;           // 指针域
}CycleLinkNode;


typedef struct
{
    CycleLinkNode *data;                     // 头结点
    int length;                         // 元素长度
}CycleLinkList;

/*
** 单列表初始化
***/
void CycleLinkList_init(CycleLinkList *list);

/*
** 单列表销毁
***/
void CycleLinkList_destroy_list(CycleLinkList *list);

/*
** 清空单列表
***/
void CycleLinkList_clear(CycleLinkList *list);

/*
** 判断单列表是否为空
***/
bool CycleLinkList_Empty(const CycleLinkList *list);

/*
** 查询单列表长度
***/
int CycleLinkList_length(const CycleLinkList *list);

/*
** 查询单列表第 idx 个数据元素对象, idx 从1开始计数 
***/
bool CycleLinkList_get_elem(const CycleLinkList *list, int idx, ElemType *e);

/*
** 查询单列表，数据元素e, 所在的下标。（下标从1开始计数）
***/
int CycleLinkList_locate_elem(const CycleLinkList *list, ElemType e, compare_func compare);

/*
** 查询单列表，数据元素 cur_e的前驱元素
***/
bool CycleLinkList_prior_elem(const CycleLinkList *list, ElemType cur_e, ElemType *pre_e);

/*
** 查询单列表，数据元素 cur_e的后继元素
***/
bool CycleLinkList_next_elem(const CycleLinkList *list, ElemType cur_e, ElemType *next_e);

/*
** 单列表, 在第idx 位置插入元素, idx 从1开始计数
***/
bool CycleLinkList_insert(CycleLinkList *list, int idx, ElemType e);

/*
** 单列表，删除第 idx 位置的元素, idx 从1开始计数 
***/
bool CycleLinkList_delete(CycleLinkList *list, int idx, ElemType *e);

/*
** 单列表，使用 visit 函数, 访问每一个元素
***/
void CycleLinkList_traverse(const CycleLinkList *list, visit_func visit);


#if defined ENABLE_UNITTEST

/*
** 测试, 单列表的基本功能
***/
void CycleLinkList_test_01(void);

/*
** 测试, 单列表长度超出长度的基本功能
***/
void CycleLinkList_test_02(void);

/*
** 测试, 单列表性能测试
***/
void CycleLinkList_test_03(void);
#endif          /*  ENABLE_UNITTEST */

#endif

