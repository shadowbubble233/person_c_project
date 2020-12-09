#include "link_list.h"

#include <stdlib.h>

/*
** 单列表初始化
***/
void LinkList_init(LinkList *list)
{
    assert(list != NULL);
   
    // 若该链表存在数据元素, 请清空 
    if(list->data)
    {
        free(list->data);
        list->data = NULL;
    }

    list->length = 0; 
}

/*
** 单列表销毁
***/
void LinkList_destroy_list(LinkList *list)
{
    LinkNode *item, *iter;
   
    assert(list != NULL);

    iter = list->data; 
    while(iter)
    {
        item = iter;
        iter = iter->next;
        free(item);
    }

    list->data = NULL;
    list->length = 0;
}


/*
** 清空单列表
***/
void LinkList_clear(LinkList *list)
{
    assert(list != NULL);
    LinkList_destroy_list(list);
}

/*
** 判断单列表是否为空
***/
bool LinkList_Empty(const LinkList *list)
{
    assert(list != NULL);
    return list->length == 0?true: false;
}

/*
** 查询单列表长度
***/
int LinkList_length(const LinkList *list)
{
    assert(list != NULL);
    return list->length;
}

/*
** 查询单列表第 idx 个数据元素对象, idx 从1开始计数 
***/
bool LinkList_get_elem(const LinkList *list, int idx, ElemType *e)
{
    int i=0;
    bool ret = false;
    LinkNode *iter;

    assert(list != NULL);

    if(idx<1 || idx>list->length)
        return ret;

    iter = list->data;
    while(iter)
    {
        if(i == idx-1)
        {
            *e = iter->elem;
            ret = true;
            break;
        } 
        iter=iter->next; 
        i++;
    }

    return ret;
}

/*
** 查询单列表，数据元素e, 所在的下标。（下标从1开始计数）
***/
int LinkList_locate_elem(const LinkList *list, ElemType e, compare_func compare)
{
    int i=0, ret=0;
    LinkNode *iter;    

    assert(list != NULL);
    if(!compare)
        return ret;

    iter = list->data;
    while(iter)
    {
        if(compare(e, iter->elem) == 0)
        {
            ret = i+1;
            break;
        } 

        iter=iter->next;
        ++i;
    }
    return ret; 
}

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
void LinkList_traverse(const LinkList *list, visit_func visit)
{
    LinkNode *iter;

    assert(list != NULL);

    iter = list->data;
    while(iter)
    {
        visit(iter->elem);
        iter = iter->next;
    }
}


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

