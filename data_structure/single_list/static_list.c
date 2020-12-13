#include "static_list.h"

/*
 *  静态链表初始化  下标0的StaticNode 作为头结点, 不存储元素
 * */
void StaticList_init(StaticList *list)
{ 
    int i; 
    StaticNode *head; 
    assert(list);
     
    list->data = (StaticNode*)malloc(sizeof(StaticNode) * STATIC_LIST_INIT_SIZE);
    if(!list->data)
    {
        DEBUG_LOG(LOG_ERROR_LEVEL, "malloc error", __func__);
        return;
    }

    list->length = 0;
    list->list_size = STATIC_LIST_INIT_SIZE;

    // 初始化头结点, 头结点指向有效数据链表。 -1 为无效索引
    head = list->data;   
    head->next = -1;

    // 其他数据结点, 添加到空闲链表中
    for(i=1; i<list->list_size -1; ++i)
    {
        list->data[i].next = i+1;
    }
    // 最后一个数据结点, 置-1
    list->data[list->list_size-1].next = -1;
    
    list->free_cur = 1; 
}

/*
 *  静态链表销毁
 * */
void StaticList_destroy_list(StaticList *list)
{
    assert(list);    

    if(list->list_size)
    {
        free(list->data);
        list->data = NULL;

        list->free_cur = -1;    
        list->length = 0;
        list->list_size = 0;
    }
}

/*
 *  清空静态链表
 * */
void StaticList_clear(StaticList *list)
{
    int i;
    StaticNode *head;

    assert(list);

    // 头结点清空
    head = list->data;
    head->next = -1;

    // 数据结点全部添加到 空闲链表中
    for(i=1; i<list->list_size-1; ++i)
    {
        list->data[i].next = i+1;
    }
    list->data[list->length-1].next = -1;    

    list->length = 0;
    list->free_cur = -1;
}

/*
 *  判断静态链表是否为空
 * */
bool StaticList_empty(const StaticList *list)
{
    assert(list);

    return list->length == 0 ? true: false;
}

/*
 *  查询静态链表长度
 * */
int StaticList_length(const StaticList *list)
{
    assert(list);

    return list->length;
}

/*
 * 查询静态链表第 idx 个数据元素对象, idx 从1开始计数 
 * */
bool StaticList_get_elem(const StaticList *list, int idx, ElemType *e)
{
    int i=1;
    bool ret=false;
    StaticNode *iter, *head;

    assert(list);

    if(idx <1 ||idx > list->length)
        return ret;

    head = &list->data[0];
    iter = list->data + head->next;
    for(; iter->next!=-1; iter=list->data + iter->next, ++i)
    {
        if(i == idx)
        {
            *e = iter->elem;
            ret = true;
            break;
        }
    }

    return ret;
}

/*
 *  查询静态链表，数据元素e, 所在的下标。（下标从1开始计数）
 * */
int StaticList_locate_elem(const StaticList *list, ElemType e, bool (*compare_func)(ElemType a, ElemType b))
{
    int ret = 0, i;
    StaticNode *head, *iter;

    assert(list);

    if(!compare_func)
        return ret;

    head = list->data;
    iter = list->data + head->next;
    for(i=1; iter < list->data + list->list_size; ++i, iter=list->data + iter->next)
    {
        if(iter->elem == e)
        {
            ret = i;
            break;
        }
    }

    return ret;
} 

/*
 *  查询静态链表，数据元素 next_e的前驱元素
 * */
bool StaticList_prior_elem(const StaticList *list, ElemType next_e, ElemType *pre_e)
{
    int i;
    bool ret = false;
    StaticNode *head, *iter, *prior_node=NULL;

    assert(list);

    head = list->data;
    iter = list->data + head->next;
    for(i=1; iter->next != -1; ++i, iter=list->data + iter->next)
    {
        if(iter->elem == next_e && prior_node)
        {
            *pre_e = prior_node->elem;
            ret = true;
            break;           
        } 
        prior_node = iter;
    }    

    return ret;
}

/*
 *  查询静态链表，数据元素 next_e的后继元素
 * */
bool StaticList_next_elem(const StaticList *list, ElemType cur_e, ElemType *next_e)
{
    bool ret = false;
    StaticNode *head, *iter;
    
    assert(list);

    head = list->data;
    iter = list->data + head->next;
    for(; iter->next != -1; iter=list->data + iter->next)
    {
        if(iter->elem == cur_e && iter->next!=-1)
        {
            *next_e = (list->data + iter->next)->elem;
            ret = true;
            break;
        }
    }

    return ret;
}

/*
 *  静态链表, 在第idx 位置插入元素, idx 从1开始计数
 * */
bool StaticList_insert(StaticList *list, int idx, ElemType e)
{
    int i;
    int item_idx;                                   // 待插入结点所在下标
    bool ret = false;
    StaticNode *head, *iter, *item=NULL;

    assert(list);

    if(idx < 1 ||idx > list->length+1)
        return ret;

    // 取一个空闲结点作为插入结点
    item_idx = list->free_cur;
    item = list->data + item_idx;
    item->elem = e;

    // 空闲头结点下标后移
    list->free_cur = item->next;

    head = list->data;
    if(idx == 1)
    {
        item->next = head->next;
        head->next = item_idx;
        return true; 
    }

    iter = list->data + head->next;
    for(i=1; iter->next != -1; ++i, iter=list->data + iter->next)
    {
        if(i == idx-1)
        {
            // 插入结点是尾结点 
            if(iter->next == -1)
            {
                item->next = -1;
                iter->next = item_idx; 
            }
            else
            {
                item->next = iter->next;
                iter->next = item_idx;
            }
            ret = true;
            break;
        }
    }

    return ret;
}

/*
 *  静态链表，删除第 idx 位置的元素, idx 从1开始计数 
 * */
bool StaticList_delete(StaticList *list, int idx, ElemType *e)
{
    int i;
    bool ret = false;
    int delete_idx;
    StaticNode *head, *iter, *delete_node;

    assert(list);

    if(idx < 1 || idx > list->length)
        return ret;

    head = list->data;

    if(idx == 1)
    {
        delete_idx = head->next;
        delete_node = list->data + delete_idx;
        *e = delete_node->elem;
        head->next = delete_node->next;

        // 删除结点回收到空闲链表中
        delete_node->next = list->free_cur;
        list->free_cur = delete_idx;

        list->length--;
        return true;         
    }

    iter = list->data + head->next;
    for(i=1; iter->next!=-1; ++i, iter=list->data + iter->next)
    {
        if(idx-1 == i)
        {
            delete_idx = iter->next;
            delete_node = list->data + iter->next;

            iter->next = delete_node->next;

            // 删除结点回收到空闲链表中
            delete_node->next = list->free_cur;
            list->free_cur = delete_idx;
            ret = true;
            break;
        } 
   
    }

    list->length--;
    return ret;
}

/*
 *  静态链表，使用 visit 函数, 访问每一个元素
 * */
void StaticList_traverse(const StaticList *list, void (*visit_func)(ElemType e))
{
    StaticNode *head, *iter;

    assert(list);

    head = list->data;
    iter = list->data + head->next;
    while(iter->next != -1)
    {
        visit_func(iter->elem);
    }
    printf("\n");
}


#if defined ENABLE_UNITTEST

/*
 *  测试, 静态链表的基本功能
 * */
void StaticList_test_01(void);

#endif          /*  ENABLE_UNITTEST */


