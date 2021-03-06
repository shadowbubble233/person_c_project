/*
 *  双向循环链表, 数据结构定义
 * */
#ifndef CYCLE_DLINK_LIST_H
#define CYCLE_DLINK_LIST_H

#include "project_config.h"


typedef bool (*compare_func)(ElemType a, ElemType b);

typedef void (*visit_func)(ElemType e);

typedef struct _cycle_dlink_node
{
    ElemType elem;                                  // 数据域
    struct _cycle_dlink_node *next;                 // 后继元素指针域
    struct _cycle_dlink_node *prev;                 // 前驱元素指针域
}CycleDLinkNode;


typedef struct
{
    CycleDLinkNode *data;                           // 头指针
    int length;                                     // 元素长度
}CycleDLinkList;

/*
** 循环双向列表初始化
***/
void CycleDLinkList_init(CycleDLinkList *list);

/*
** 循环双向列表销毁
***/
void CycleDLinkList_destroy_list(CycleDLinkList *list);

/*
** 清空循环双向列表
***/
void CycleDLinkList_clear(CycleDLinkList *list);

/*
** 判断循环双向列表是否为空
***/
bool CycleDLinkList_empty(const CycleDLinkList *list);

/*
** 查询循环双向列表长度
***/
int CycleDLinkList_length(const CycleDLinkList *list);

/*
** 查询循环双向列表第 idx 个数据元素对象, idx 从1开始计数 
***/
bool CycleDLinkList_get_elem(const CycleDLinkList *list, int idx, ElemType *e);

/*
** 查询循环双向列表，数据元素e, 所在的下标。（下标从1开始计数）
***/
int CycleDLinkList_locate_elem(const CycleDLinkList *list, ElemType e, compare_func compare);

/*
** 查询循环双向列表，数据元素 cur_e的前驱元素
***/
bool CycleDLinkList_prior_elem(const CycleDLinkList *list, ElemType cur_e, ElemType *pre_e);

/*
** 查询循环双向列表，数据元素 cur_e的后继元素
***/
bool CycleDLinkList_next_elem(const CycleDLinkList *list, ElemType cur_e, ElemType *next_e);

/*
** 循环双向列表, 在第idx 位置插入元素, idx 从1开始计数
***/
bool CycleDLinkList_insert(CycleDLinkList *list, int idx, ElemType e);

/*
** 循环双向列表，删除第 idx 位置的元素, idx 从1开始计数 
***/
bool CycleDLinkList_delete(CycleDLinkList *list, int idx, ElemType *e);

/*
** 循环双向列表，使用 visit 函数, 访问每一个元素
***/
void CycleDLinkList_traverse(const CycleDLinkList *list, visit_func visit);


#if defined ENABLE_UNITTEST

/*
** 测试, 循环双向列表的基本功能
***/
void CycleDLinkList_test_01(void);

#endif          /*  ENABLE_UNITTEST */

#endif

