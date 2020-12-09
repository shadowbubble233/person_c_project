/*
 *  线性表_ 链式结构, 数据结构定义
 * */
#ifndef LINK_LIST_H
#define LINK_LIST_H

#include "project_config.h"


typedef int ElemType;                   // 线性链表-存储元素类型

/*  线性链表, 数据项比较函数。 返回值 0, 比较成功 */
typedef bool (*compare_func)(ElemType a, ElemType b);

/*  线性链表, 数据项迭代函数 */
typedef void (*visit_func)(ElemType e);

typedef struct _node
{
    ElemType elem;                      // 数据域
    struct _node *next;                 // 指针域
}LinkNode;


typedef struct
{
    LinkNode *data;                     // 头结点
    int length;                         // 元素长度
}LinkList;

/*
** 单列表初始化
***/
void LinkList_init(LinkList *list);

/*
** 单列表销毁
***/
void LinkList_destroy_list(LinkList *list);

/*
** 清空单列表
***/
void LinkList_clear(LinkList *list);

/*
** 判断单列表是否为空
***/
bool LinkList_Empty(const LinkList *list);

/*
** 查询单列表长度
***/
int LinkList_length(const LinkList *list);

/*
** 查询单列表第 idx 个数据元素对象, idx 从1开始计数 
***/
bool LinkList_get_elem(const LinkList *list, int idx, ElemType *e);

/*
** 查询单列表，数据元素e, 所在的下标。（下标从1开始计数）
***/
int LinkList_locate_elem(const LinkList *list, ElemType e, compare_func compare);

/*
** 查询单列表，数据元素 cur_e的前驱元素
***/
bool LinkList_prior_elem(const LinkList *list, ElemType cur_e, ElemType *pre_e);

/*
** 查询单列表，数据元素 cur_e的后继元素
***/
bool LinkList_next_elem(const LinkList *list, ElemType cur_e, ElemType *next_e);

/*
** 单列表, 在第idx 位置插入元素, idx 从1开始计数
***/
bool LinkList_insert(LinkList *list, int idx, ElemType e);

/*
** 单列表，删除第 idx 位置的元素, idx 从1开始计数 
***/
bool LinkList_delete(LinkList *list, int idx, ElemType *e);

/*
** 单列表，使用 visit 函数, 访问每一个元素
***/
void LinkList_traverse(const LinkList *list, visit_func visit);


#if defined ENABLE_UNITTEST

/*
** 测试, 单列表的基本功能
***/
void LinkList_test_01(void);

/*
** 测试, 单列表长度超出长度的基本功能
***/
void LinkList_test_02(void);

/*
** 测试, 单列表性能测试
***/
void LinkList_test_03(void);
#endif          /*  ENABLE_UNITTEST */

#endif

