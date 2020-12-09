#include "cycle_link_list.h"

/*
** 循环单链表初始化
***/
void CycleLinkList_init(CycleLinkList *list)
{
    assert(list != NULL);

    list->data = NULL;
    list->last = NULL;
    list->length = 0;
}


/*
** 循环单链表销毁
***/
void CycleLinkList_destroy_list(CycleLinkList *list)
{
    CycleLinkNode *iter, *item;

    assert(list != NULL);

    if(list->length)
    {
        iter = list->data;
        do
        {
            item = iter;
            iter = iter->next;
            free(item);
        }while(iter != list->data);
    }
    list->data = NULL;
    list->length = 0;
}

/*
** 清空循环单链表
***/
void CycleLinkList_clear(CycleLinkList *list)
{
   CycleLinkList_destroy_list(list); 
}

/*
** 判断循环单链表是否为空
***/
bool CycleLinkList_empty(const CycleLinkList *list)
{
    assert(list != NULL);
    return list->length == 0 ? true: false;    
}

/*
** 查询循环单链表长度
***/
int CycleLinkList_length(const CycleLinkList *list)
{
    assert(list != NULL);
    return list->length;
}

/*
** 查询循环单链表第 idx 个数据元素对象, idx 从1开始计数 
***/
bool CycleLinkList_get_elem(const CycleLinkList *list, int idx, ElemType *e)
{
    int i = 1;
    bool ret = false;
    CycleLinkNode *iter;

    assert(list != NULL);

    if(idx < 1 || idx>list->length)
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
** 查询循环单链表，数据元素e, 所在的下标。（下标从1开始计数）
***/
int CycleLinkList_locate_elem(const CycleLinkList *list, ElemType e, compare_func compare)
{
    int i = 1;
    bool ret = 0;
    CycleLinkNode *iter;
    
    assert(list != NULL);

    if(!compare)
        return ret;

    iter = list->data;
    do 
    {
        if(compare(e, iter->elem) == 0)
        {
            ret = i;
            break; 
        }
        iter = iter->next;
    }while(iter != list->data); 
    return ret; 
}

/*
** 查询循环单链表，数据元素 cur_e的前驱元素
***/
bool CycleLinkList_prior_elem(const CycleLinkList *list, ElemType cur_e, ElemType *pre_e)
{
    bool ret = false;
    CycleLinkNode *iter, *prior_node;

    assert(list);

    if(list->length <2)
        return ret;

    if(list->data->elem == cur_e)
        return ret;

    prior_node = list->data;
    iter = list->data->next;
    do
    {
        if(iter->elem == cur_e)
        {
            *pre_e = prior_node->elem;
            ret = true;
            break;
        }
        prior_node = iter;
        iter = iter->next;
    }while(iter != list->data);
    return ret;
}

/*
** 查询循环单链表，数据元素 cur_e的后继元素
***/
bool CycleLinkList_next_elem(const CycleLinkList *list, ElemType cur_e, ElemType *next_e)
{
    bool ret = false;
    CycleLinkNode *iter;

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
                break;
            }
        }

        iter = iter->next;
    }while(iter != list->data);
    return ret; 
}

/*
** 循环单链表, 在第idx 位置插入元素, idx 从1开始计数
***/
bool CycleLinkList_insert(CycleLinkList *list, int idx, ElemType e)
{
    int i;
    CycleLinkNode *iter, *item, *prior_node;
    bool ret = false;
 
    assert(list);
    if(idx <1 || idx > list->length+1)
        return ret;

    item = (CycleLinkNode*) malloc(sizeof(CycleLinkNode));
    if(!item)
    {
        DEBUG_LOG(LOG_ERROR_LEVEL, "malloc error", __func__);
        return ret;
    }    
    memset(item, 0x0, sizeof(CycleLinkNode));
    item->elem = e;
   
    /* 首节点位置插入数据 */
    if(idx == 1)
    {
        if(list->length == 0)
        {
            list->data = item;
            item->next = list->data;
            list->last = item;
        }
        else
        {
            item->next = list->data;
            list->data = item;
            list->last->next = item; 
        }
        list->length++;
        return true;        
    }    

    /* 中间节点位置插入数据 */
    i = 1;
    prior_node = NULL;
    iter = list->data->next;
    do 
    {
        if(i++ == idx)
        {
            item->next = iter;
            prior_node->next = item;
            ret = true;
            break; 
        }
        prior_node = iter;
        iter = iter->next;
    }while(iter != list->data);

    if(i == list->length+1)
        list->last = item;

    list->length++;
    return ret; 
}

/*
** 循环单链表，删除第 idx 位置的元素, idx 从1开始计数 
***/
bool CycleLinkList_delete(CycleLinkList *list, int idx, ElemType *e)
{
    int i = 1;
    bool ret = false;
    CycleLinkNode *iter, *prior_node, *item;

    assert(list);
    if(idx < 1 || idx > list->length)
        return ret;

    if(list->length == 1)
    {
        item = list->data;
        *e = item->elem;
        free(item);
        list->last = NULL;
        list->data = NULL;
        list->length--;
        return true;
    }

    if(idx == 1)
    {
        item = list->data;
        *e = item->elem;
        list->data = list->data->next;
        list->last->next = list->data;
        free(item);
        list->length--;
        return true;
    } 

    i = 2;
    prior_node = list->data;
    iter = list->data->next;
    do 
    {
        if(i == idx)
        {
            if(i == list->length)       /*  最后一个元素    */
            {
                item = iter;
                prior_node->next = iter->next;
                list->last = prior_node;
            }
            else
            {
                item = iter;
                prior_node->next = iter->next;
            }
            *e = item->elem;    
            free(item);
            ret = true;
            break;
        }
        prior_node = iter;
        iter = iter->next;
        i++; 
    }while(iter != list->data);
   
    list->length--; 
    return ret;
}

/*
** 循环单链表，使用 visit 函数, 访问每一个元素
***/

static bool _compare_func(ElemType a, ElemType b)
{
    return a == b ? 0 : 1;
}


static void _visit_func(ElemType e)
{
    printf("%d ", e);
}

void CycleLinkList_traverse(const CycleLinkList *list, visit_func visit)
{
    CycleLinkNode *iter;
    
    assert(list);

    if(!visit)
        return;

    if(list->length)
    {
        iter = list->data;
        do 
        {
            visit(iter->elem);
            iter = iter->next;
        }while(iter != list->data);
    }
    printf("\n");
}


#if defined ENABLE_UNITTEST

/*
** 测试, 循环单链表的基本功能
***/
void CycleLinkList_test_01(void)
{
    CycleLinkList list;
    bool ret = false;
    int idx, i, len;
    ElemType e, prior_e, next_e;
    
    DEBUG_LOG(LOG_DEBUG_LEVEL, "func called start", __func__);
    CycleLinkList_init(&list);
    assert(CycleLinkList_empty(&list));

    for(i=0; i<10; ++i)
        assert(CycleLinkList_insert(&list, 1, i));
  
    CycleLinkList_traverse(&list, _visit_func);
    
    len = CycleLinkList_length(&list);
    assert(len == 10);
    
    ret = CycleLinkList_get_elem(&list, 1, &e);
    assert(ret && e == 9);
    
    ret = CycleLinkList_get_elem(&list, 10, &e);
    assert(ret && e == 0);
    
    ret = CycleLinkList_get_elem(&list, 11, &e);
    assert(!ret);
    
    ret = CycleLinkList_prior_elem(&list, 5, &prior_e);
    assert(ret && prior_e == 6);
    
    ret = CycleLinkList_next_elem(&list, 5, &next_e);
    assert(ret && next_e == 4);
    
    idx = CycleLinkList_locate_elem(&list, 9, _compare_func);
    assert(idx == 1);
    
    ret = CycleLinkList_delete(&list, 1, &e);
    assert(ret && e == 9);

    CycleLinkList_traverse(&list, _visit_func);

    ret = CycleLinkList_delete(&list, 9, &e);
    assert(ret && e == 0);
    
    CycleLinkList_traverse(&list, _visit_func);
    CycleLinkList_destroy_list(&list);
    assert(CycleLinkList_empty(&list));
    DEBUG_LOG(LOG_DEBUG_LEVEL, "func called done", __func__);
}

#endif          /*  ENABLE_UNITTEST */


