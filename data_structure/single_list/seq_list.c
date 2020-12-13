#include "seq_list.h"

#include <stdlib.h>

/*
 *  线性表初始化
 * */
void SeqList_init(SeqList *list)
{
    assert(list != NULL);
    
    list->elem = (ElemType*) malloc(sizeof(ElemType) * SEQ_LIST_INIT_SIZE);
    if(!list->elem)
    {
        DEBUG_LOG(LOG_ERROR_LEVEL, "malloc error", __func__);
        return;
    }

    memset(list->elem, 0x0, sizeof(ElemType) * SEQ_LIST_INIT_SIZE);
    list->length = 0;
    list->list_size = SEQ_LIST_INIT_SIZE; 
}

/*
**  线性表销毁
***/
void SeqList_destroy_list(SeqList *list)
{
    assert(list != NULL);
        
    if(list->elem)
    {
        free(list->elem);
        list->elem = NULL;
        list->length = 0;
        list->list_size = 0;
    }
}

/*
**  清空线性表
***/
void SeqList_clear(SeqList *list)
{
    assert(list != NULL);
    list->length = 0;
}

/*
**  判断线性表是否为空
***/
bool SeqList_empty(const SeqList *list)
{
    assert(list != NULL);
    return list->length == 0?true:false; 
}

/*
**  查询线性表长度
***/
int SeqList_length(const SeqList *list)
{
    assert(list != NULL);
    return list->length;
}

/*
** 查询线性表第 idx 个数据元素对象, idx 从1开始计数 
***/
bool SeqList_get_elem(const SeqList *list, int idx, ElemType *e)
{
    bool ret = true;

    assert(list != NULL);
    if(idx<1 || idx > list->length)
        return false;

    *e = list->elem[idx-1];
    return ret;      
}

/*
**  查询线性表，数据元素e, 所在的下标。（下标从1开始计数）
***/
int SeqList_locate_elem(const SeqList *list, ElemType e, compare_func compare)
{
    int ret = 0, i;
    
    assert(list != NULL); 
    if(compare==NULL)
        return ret;
   
    for(i=0; i<list->length; ++i)
    {
        if(compare(list->elem[i], e) == 0)
        {
            ret = i+1;
            break;
        }
    }
    return ret;
}

/*
** 查询线性表，数据元素 cur_e的前驱元素
***/
bool SeqList_prior_elem(const SeqList *list, ElemType cur_e, ElemType *pre_e)
{
    int i;
    bool ret = false;
    ElemType pre_elem;
   
    assert(list != NULL); 
    if(list->length == 0)
    {
        return ret;
    }
    pre_elem = list->elem[0];   

    for(i=1; i<list->length; ++i)
    {
        if(cur_e == list->elem[i])
        {
            *pre_e = pre_elem;
            ret = true;
            break;
        }
        
        pre_elem = list->elem[i];
    }
    return ret;
}

/*
** 查询线性表，数据元素 cur_e的后继元素
***/
bool SeqList_next_elem(const SeqList *list, ElemType cur_e, ElemType *next_e)
{
    int i;
    bool ret = false;
    assert(list != NULL);
    
    for(i=0; i<list->length-1; ++i)
    {
        if(list->elem[i] == cur_e)
        {
            *next_e = list->elem[i+1];
            ret = true;
            break;
        }
    }
    return ret;     
}

/*
** 线性表, 在第idx 位置插入元素, idx 从1开始计数
***/
bool SeqList_insert(SeqList *list, int idx, ElemType e)
{
    int i;
    bool ret = false;
    ElemType *base = NULL;

    assert(list != NULL);
    if(idx<1 || idx>list->length+1)
    {
        DEBUG_LOG(LOG_ERROR_LEVEL, "idx error", __func__);
        return ret;
    }

    // 检测 单链表是否需要扩容
    if(list->length >= list->list_size)
    {
        base = (ElemType*) malloc(sizeof(ElemType) * (list->list_size + LIST_INCREMENT)); 
        if(!base)
        {
            DEBUG_LOG(LOG_ERROR_LEVEL, "malloc error", __func__);
            return ret;
        }

        memset(base, 0x0, sizeof(list->list_size + LIST_INCREMENT));  
 
        // 单链表, 原始数据拷贝
        memcpy(base, list->elem, sizeof(ElemType)*list->list_size);
        // 释放原始数据缓冲区
        free(list->elem);    
        // 线性表指向新分配的缓冲区
        list->elem = base; 
        list->list_size += LIST_INCREMENT;
    }

    // 执行插入操作
    for(i=list->length; i>=0; --i)
    {
        if(i==idx-1)
        {
            list->elem[i] = e;
            ret = true;
            break;
        }
        
        // 元素后移
        list->elem[i] = list->elem[i-1];
    }

    /*
    指针实现版本
 
    ElemType *iter, *stop;
    *iter = list->elem[list->length];
    *stop = list->elem[idx]; 

    for( ; iter>= stop; --iter)
        *iter = *(iter-1);
    *iter= e;
    list->length++; 
    */

    if(ret)
        list->length++;   
    return ret; 
}

/*
** 线性表，删除第 idx 位置的元素  
***/
bool SeqList_delete(SeqList *list, int idx, ElemType *e)
{
    int i;

    assert(list != NULL);

    if(idx<1 || idx>list->length)
    {
        return false;
    }

    *e = list->elem[idx-1];
    
    for(i=idx-1; i<list->length-1; ++i)
    {
        list->elem[i] = list->elem[i+1];
    }

    list->length--;   
    return true;
}




/*
** 线性表，使用 visit 函数, 访问每一个元素
***/
void SeqList_traverse(const SeqList *list, visit_func visit)
{
    int i;
    assert(list != NULL);

    for(i=0; i<list->length; ++i)
    {
        visit(list->elem[i]);
    }
    printf("\n");
}


#if defined ENABLE_UNITTEST


static bool _compare_func(ElemType a, ElemType b)
{
    if(a == b)
        return 0;
    return 1;
}

static void _visit_func(ElemType a)
{
    printf("%d ", a);
}

/*
** 测试, 线性表的基本功能
***/
void SeqList_test_01(void)
{
    int idx, i, len;
    ElemType e, prior_e, next_e;
    bool ret = false;
    SeqList list;

    DEBUG_LOG(LOG_DEBUG_LEVEL, "func called start", __func__);
    SeqList_init(&list);
    assert(SeqList_empty(&list));

    for(i=0; i<10; ++i)
        SeqList_insert(&list, 1, i);

    len = SeqList_length(&list);
    assert(len == 10);  
    SeqList_traverse(&list, _visit_func);

    ret = SeqList_get_elem(&list, 1, &e);
    assert(ret && e==9);

    ret = SeqList_get_elem(&list, 10, &e);
    assert(ret && e==0);
    
    ret = SeqList_get_elem(&list, 11, &e);
    assert(!ret);

    ret = SeqList_prior_elem(&list, 5, &prior_e);
    assert(ret && prior_e==6);

    ret = SeqList_next_elem(&list, 5, &next_e);
    assert(ret && next_e==4);

    idx = SeqList_locate_elem(&list, 9, _compare_func);
    assert(idx==1);

    ret = SeqList_delete(&list, 1, &e);
    assert(ret && e==9);

    SeqList_traverse(&list, _visit_func);    
 
    SeqList_destroy_list(&list);
    assert(SeqList_empty(&list));
    DEBUG_LOG(LOG_DEBUG_LEVEL, "func called done", __func__); 
}

/*
** 测试, 线性表长度超出长度的基本功能
***/
void SeqList_test_02(void)
{
    int i;
    SeqList list;

    DEBUG_LOG(LOG_DEBUG_LEVEL, "func called start", __func__);
    SeqList_init(&list);

    for(i=0; i<150; ++i)
        SeqList_insert(&list, i+1, i+1);

    SeqList_traverse(&list, _visit_func);
    SeqList_destroy_list(&list);

    DEBUG_LOG(LOG_DEBUG_LEVEL, "func called done", __func__);
}

/*
** 测试, 线性表性能测试
***/
void SeqList_test_03(void)
{
    SeqList list;
    int i;
    DEBUG_LOG(LOG_DEBUG_LEVEL, "start called", __func__);
    SeqList_init(&list);

    DEBUG_LOG(LOG_DEBUG_LEVEL, "insert 10000 elem", __func__);
    for(i=0; i<10000; ++i)
    {
        SeqList_insert(&list, i+1, i+1);
    }
    //SeqList_traverse(&list, _visit_func);
    SeqList_destroy_list(&list);

    DEBUG_LOG(LOG_DEBUG_LEVEL, "end called", __func__);
    DEBUG_LOG(LOG_DEBUG_LEVEL, NULL, NULL);
}

#endif          /*  ENABLE_UNITTEST */

