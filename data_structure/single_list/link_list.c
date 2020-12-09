#include "link_list.h"

#include <stdlib.h>

/*
** 单链表初始化
***/
void LinkList_init(LinkList *list)
{
    assert(list != NULL);
   
    list->data = NULL;
    list->length = 0; 
}

/*
** 单链表销毁
***/
void LinkList_destroy_list(LinkList *list)
{
    LinkNode *item, *iter;
   
    assert(list != NULL);

    iter = list->data; 
    while(iter)
    {
        item = iter;
        free(item);
        iter = iter->next;
    }

    list->data = NULL;
    list->length = 0;
}


/*
** 清空单链表
***/
void LinkList_clear(LinkList *list)
{
    assert(list != NULL);
    LinkList_destroy_list(list);
}

/*
** 判断单链表是否为空
***/
bool LinkList_empty(const LinkList *list)
{
    assert(list != NULL);
    return list->length == 0? true: false;
}

/*
** 查询单链表长度
***/
int LinkList_length(const LinkList *list)
{
    assert(list != NULL);
    return list->length;
}

/*
** 查询单链表第 idx 个数据元素对象, idx 从1开始计数 
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
** 查询单链表，数据元素e, 所在的下标。（下标从1开始计数）
***/
int LinkList_locate_elem(const LinkList *list, ElemType e, compare_func compare)
{
    int i, ret=0;
    LinkNode *iter;    

    assert(list != NULL);
    if(!compare)
        return ret;

    i = 1;
    iter = list->data;
    while(iter)
    {
        if(compare(e, iter->elem) == 0)
        {
            ret = i;
            break;
        } 

        iter=iter->next;
        ++i;
    }
    return ret; 
}

/*
** 查询单链表，数据元素 cur_e的前驱元素
***/
bool LinkList_prior_elem(const LinkList *list, ElemType cur_e, ElemType *pre_e)
{
    bool ret = false;
    LinkNode *iter, *pre_node;
    
    assert(list != NULL);

    if(list->length <= 1)
    {
        return ret;
    }
   
    /*  第一个元素项没有前驱元素  */ 
    if(list->data->elem == cur_e)
    {
        return ret;
    }

    iter = list->data;
    pre_node = iter;
    iter = iter->next;
    while(iter)
    {
        if(iter->elem == cur_e)
        {
            *pre_e = pre_node->elem;
            ret = true;
            break;
        }
        pre_node = iter;
        iter = iter->next;    
    }
    
    return ret;
}

/*
** 查询单链表，数据元素 cur_e的后继元素
***/
bool LinkList_next_elem(const LinkList *list, ElemType cur_e, ElemType *next_e)
{
    LinkNode *iter;
    bool ret = false;

    assert(list != NULL);
   
    iter = list->data;

    while(iter)
    {
        if(iter->elem == cur_e)
        {
            if(iter->next)
            {
                *next_e = iter->next->elem;
                ret = true;
            }
            break;
        }
        iter = iter->next;
    }
    return ret; 
}

/*
** 单链表, 在第idx 位置插入元素, idx 从1开始计数
***/
bool LinkList_insert(LinkList *list, int idx, ElemType e)
{
    int i;
    bool ret = false;
    LinkNode *iter, *item, *prior_node;
    
    assert(list != NULL);

    if(idx<1 ||idx>list->length+1)
    {
        DEBUG_LOG(LOG_ERROR_LEVEL, "idx error", __func__);
        return ret;
    }

    item = (LinkNode*)malloc(sizeof(LinkNode));
    if(item == NULL)
    {
        DEBUG_LOG(LOG_ERROR_LEVEL, "malloc error", __func__);
        return ret;
    }
    memset(item, 0x0, sizeof(LinkNode));
    item->elem = e;
    item->next = NULL;

    if(list->length == 0 || idx == 1)
    {
        item->next = list->data;
        list->data = item;
        list->length++;
        return true;
    }

    i = 1;
    prior_node = list->data;
    iter = list->data;
    while(iter)
    {
        if(i++ == idx)
        {
            item->next = iter;
            prior_node->next = item;
            list->length++;
            ret = true;
            break;
        }
        iter = iter->next;
    }

    return ret; 
}

/*
** 单链表，删除第 idx 位置的元素, idx 从1开始计数 
***/
bool LinkList_delete(LinkList *list, int idx, ElemType *e)
{
    int i;
    bool ret = false;
    LinkNode *iter, *item, *prior_node;

    assert(list != NULL);
    if(idx <1 ||idx>list->length)
    {
        DEBUG_LOG(LOG_ERROR_LEVEL, "idx error", __func__);
        return ret;
    }

    i = 1;
    prior_node = NULL;
    iter = list->data;
    while(iter)
    {
        if(i++ == idx)
        {
            *e = iter->elem;
            item = iter;
            if(prior_node)
            {
                prior_node->next = iter->next;
            }
            else
            {
                list->data = iter->next;
            }

            free(item);
            ret = true;
            break; 
        }
        iter = iter->next;
    }
    return ret; 
}

/*
** 单链表，使用 visit 函数, 访问每一个元素
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
    printf("\n");
}


#if defined ENABLE_UNITTEST

/*
** 测试, 单链表的基本功能
***/

static bool _compare_func(ElemType a, ElemType b)
{
    return a == b? 0: 1;
}

static void _visit_func(ElemType e)
{
    printf("%d ", e);
}

void LinkList_test_01(void)
{
    LinkList list;
    bool ret = false;
    int idx, i, len;
    ElemType e, prior_e, next_e;

    DEBUG_LOG(LOG_DEBUG_LEVEL, "func called start", __func__);
    LinkList_init(&list);
    assert(LinkList_empty(&list));

    for(i=0; i<10; ++i)
        assert(LinkList_insert(&list, 1, i));

    LinkList_traverse(&list, _visit_func);

    len = LinkList_length(&list);
    assert(len == 10);

    ret = LinkList_get_elem(&list, 1, &e);
    assert(ret && e == 9);

    ret = LinkList_get_elem(&list, 10, &e);
    assert(ret && e == 0);

    ret = LinkList_get_elem(&list, 11, &e);
    assert(!ret);

    ret = LinkList_prior_elem(&list, 5, &prior_e);
    assert(ret && prior_e == 6);

    ret = LinkList_next_elem(&list, 5, &next_e);
    assert(ret && next_e == 4); 
    
    idx = LinkList_locate_elem(&list, 9, _compare_func);
    assert(idx == 1);
    
    ret = LinkList_delete(&list, 1, &e);
    assert(ret && e== 9);

    LinkList_traverse(&list, _visit_func);
    LinkList_destroy_list(&list);
    assert(LinkList_empty(&list));
    DEBUG_LOG(LOG_DEBUG_LEVEL, "func called done", __func__);
}

#endif          /*  ENABLE_UNITTEST */

