#include "cycle_dlink_list.h"

/*
** 循环双向列表初始化
***/
void CycleDLinkList_init(CycleDLinkList *list)
{
    assert(list);
    memset(list, 0x0, sizeof(CycleDLinkList));
}

/*
** 循环双向列表销毁
***/
void CycleDLinkList_destroy_list(CycleDLinkList *list)
{
    CycleDLinkNode *iter, *item;

    assert(list);

    if(list->length)
    {
        iter = list->data;
        iter->prev->next = NULL;
        
        while(iter)
        {
            item = iter;
            iter = iter->next;
            free(item);
        }
        list->data = NULL;
        list->length = 0;
    }
}

/*
** 清空循环双向列表
***/
void CycleDLinkList_clear(CycleDLinkList *list)
{
    CycleDLinkList_destroy_list(list);
}

/*
** 判断循环双向列表是否为空
***/
bool CycleDLinkList_empty(const CycleDLinkList *list)
{
    assert(list);
    return list->length == 0 ? true: false;
}

/*
** 查询循环双向列表长度
***/
int CycleDLinkList_length(const CycleDLinkList *list)
{
    assert(list);
    return list->length;
}

/*
** 查询循环双向列表第 idx 个数据元素对象, idx 从1开始计数 
***/
bool CycleDLinkList_get_elem(const CycleDLinkList *list, int idx, ElemType *e)
{
    int i = 1;
    bool ret = false;
    CycleDLinkNode *iter;

    assert(list);    

    if(idx < 1 || idx > list->length)
        return ret;

    iter = list->data;
    do
    {
        if(i++ == idx)
        {
            *e = iter->elem;
            ret = true;
            break;
        }
        iter = iter->next;
    }while(iter != list->data);

    return ret;
}

/*
** 查询循环双向列表，数据元素e, 所在的下标。（下标从1开始计数）
***/
int CycleDLinkList_locate_elem(const CycleDLinkList *list, ElemType e, compare_func compare)
{
    int ret = 0, i = 1;
    CycleDLinkNode *iter;

    assert(list);
    if(!compare)
        return ret;

    iter = list->data;
    do
    {
        if(iter->elem == e)
        {
            ret =  i;
            break; 
        }

        i++;
        iter = iter->next;
    }while(iter != list->data);    

    return ret;
}

/*
** 查询循环双向列表，数据元素 cur_e的前驱元素
***/
bool CycleDLinkList_prior_elem(const CycleDLinkList *list, ElemType cur_e, ElemType *pre_e)
{
    bool ret = false;
    CycleDLinkNode *iter;

    assert(list);
    
    iter = list->data;
    do
    {
        if(iter->elem == cur_e)
        {
            *pre_e = iter->prev->elem;
            ret = true;
            break;
        }
        iter = iter->next;
    }while(iter != list->data);

    return ret;
}

/*
** 查询循环双向列表，数据元素 cur_e的后继元素
***/
bool CycleDLinkList_next_elem(const CycleDLinkList *list, ElemType cur_e, ElemType *next_e)
{
    bool ret = false;
    CycleDLinkNode *iter;

    assert(list);
    
    iter = list->data;
    do
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
    }while(iter != list->data);

    return ret;
}

/*
** 循环双向列表, 在第idx 位置插入元素, idx 从1开始计数
***/
bool CycleDLinkList_insert(CycleDLinkList *list, int idx, ElemType e)
{
    int i = 1;
    bool ret = false;
    CycleDLinkNode *iter, *item;
    
    assert(list);

    if(idx < 1 || idx > list->length+1)
        return ret;
    
    item = (CycleDLinkNode*)malloc(sizeof(CycleDLinkNode));
    if(item == NULL)
    {
        DEBUG_LOG(LOG_ERROR_LEVEL, "malloc error", __func__);
        return ret;
    }
    memset(item, 0x0, sizeof(CycleDLinkNode));
    item->elem = e; 
    
    if(list->length == 0)
    {
        item->prev = item;
        item->next = item;
        list->data = item;
        list->length++;
        return true;
    }

    iter = list->data;
    do
    {
        if(i++ == idx)
        {
            item->next = iter;
            iter->prev->next = item;
            item->prev = iter->prev;
            iter->prev = item;
            ret = true;
            break;
        }
        iter = iter->next; 
    }while(iter != list->data);

    if(idx == 1)
        list->data = item;
    list->length++;
    return ret;
}

/*
** 循环双向列表，删除第 idx 位置的元素, idx 从1开始计数 
***/
bool CycleDLinkList_delete(CycleDLinkList *list, int idx, ElemType *e)
{
    int i = 1;
    bool ret = false;
    CycleDLinkNode *iter, *item;

    assert(list);
   
    if(idx < 1 || idx > list->length)
        return ret;
 
    iter = list->data;
    do
    {
        if(i++ == idx)
        {
            if(idx == 1)
                list->data = iter->next;
            iter->prev->next = iter->next;
            iter->next->prev = iter->prev;
            item = iter;
            *e = item->elem;
            free(item);
            ret = true;
            break;
        }
        iter = iter->next;
    }while(iter != list->data); 

    list->length--;
    return ret;
}

/*
** 循环双向列表，使用 visit 函数, 访问每一个元素
***/
void CycleDLinkList_traverse(const CycleDLinkList *list, visit_func visit)
{
   CycleDLinkNode *iter;

    assert(list);
    iter = list->data;
    do
    {
        visit(iter->elem);
        iter = iter->next;
    }while(iter != list->data);
    printf("\n"); 
}


#if defined ENABLE_UNITTEST

static bool _compare_func(ElemType a, ElemType b)
{
    return a == b ? 0 : 1;
}

static void _visit_func(ElemType e)
{
    printf("%d ", e);
}

/*
** 测试, 循环双向列表的基本功能
***/
void CycleDLinkList_test_01(void)
{
    CycleDLinkList list;
    bool ret = false;
    int idx, i, len;
    ElemType e, prior_e, next_e;

    DEBUG_LOG(LOG_DEBUG_LEVEL, "func called start", __func__);
    CycleDLinkList_init(&list);
    assert(CycleDLinkList_empty(&list));

    for(i=0; i<10; ++i)
        assert(CycleDLinkList_insert(&list, 1, i));

    CycleDLinkList_traverse(&list, _visit_func);

    len = CycleDLinkList_length(&list);
    assert(len == 10);

    ret = CycleDLinkList_get_elem(&list, 1, &e);
    assert(ret && e == 9);

    ret = CycleDLinkList_get_elem(&list, 10, &e);
    assert(ret && e == 0);

    ret = CycleDLinkList_get_elem(&list, 11, &e);
    assert(!ret);

    ret = CycleDLinkList_prior_elem(&list, 5, &prior_e);
    assert(ret && prior_e == 6);

    ret = CycleDLinkList_next_elem(&list, 5, &next_e);
    assert(ret && next_e == 4);

    idx = CycleDLinkList_locate_elem(&list, 0, _compare_func);
    assert(idx == 10);
    
    ret = CycleDLinkList_delete(&list, 1, &e);
    assert(ret && e == 9);

    CycleDLinkList_traverse(&list, _visit_func);

    ret = CycleDLinkList_delete(&list, 9, &e);
    assert(ret && e == 0);
    
    CycleDLinkList_traverse(&list, _visit_func);
    CycleDLinkList_destroy_list(&list);
    assert(CycleDLinkList_empty(&list));
    DEBUG_LOG(LOG_DEBUG_LEVEL, "func called done", __func__);    
}

#endif          /*  ENABLE_UNITTEST */


