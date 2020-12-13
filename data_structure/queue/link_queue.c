
#include "link_queue.h"

/*
 *  链式队列初始化
 * */
bool LinkQueue_init(LinkQueue *queue)
{
    LinkQNode *item = NULL;
    assert(queue);

     item = (LinkQNode*)malloc(sizeof(LinkQNode));
    if(!item)
    {
        DEBUG_LOG(LOG_ERROR_LEVEL, "malloc error", __func__);
        return false;
    }
    memset(item, 0x0, sizeof(LinkQNode));
    queue->front = queue->rear = item;
    queue->length = 0;
    return true;
}

/*
 *  链式队列销毁
 * */
bool LinkQueue_destroy(LinkQueue *queue)
{
    LinkQNode *iter, *item;

    assert(queue);

    iter = queue->front;
    while(iter)
    {
        item = iter;
        iter = iter->next;
        free(item); 
    }
    queue->front = queue->rear = NULL;
    queue->length = 0;
    return true;
}

/*
 *  链式队列清空
 * */
bool LinkQueue_clear(LinkQueue *queue)
{
    LinkQueue_destroy(queue);
    LinkQueue_init(queue);
    return true;
}

/*
 *  链式队列判断是否为空
 * */
bool LinkQueue_empty(LinkQueue *queue)
{
    return queue->length == 0 ? true: false;
}

/*
 *  链式队列，查询队列长度
 * */
int LinkQueue_length(LinkQueue *queue)
{
    assert(queue);
    return queue->length;
}

/*
 *  链式队列, 返回队头元素
 * */
bool LinkQueue_get_head(LinkQueue *queue, ElemType *e)
{
    bool ret = false;
    assert(queue);

    if(queue->length == 0)
    {
        return ret;
    }

    *e = queue->front->next->elem;
    return true;
}

/*
 *  链式队列， 入队操作 (队尾插入新元素)
 * */
bool LinkQueue_en_queue(LinkQueue *queue, ElemType e)
{
    bool ret = false;
    LinkQNode *item;

    assert(queue);
    item = (LinkQNode*) malloc(sizeof(LinkQNode));
    if(!item)
    {
        DEBUG_LOG(LOG_ERROR_LEVEL, "malloc error", __func__);
        return ret;
    }
    memset(item, 0x0, sizeof(LinkQNode));
    item->elem = e;

    queue->rear->next = item;
    queue->rear = item;
    queue->length++;
    return true;
}


/*
 *  链式队列, 出队操作 (删除队头元素)
 * */
bool LinkQueue_de_queue(LinkQueue *queue, ElemType *e)
{
    bool ret = false;
    LinkQNode *item;
    assert(queue);

    if(queue->length==0)
    {
        return ret;
    }
    item = queue->front->next;
    queue->front = item->next;
    *e = item->elem;
    free(item);
    queue->length--;
    return true;
}


/*
 *  链式队列, 遍历操作
 * */
void LinkQueue_traverse(const LinkQueue *queue, void (*visit_func)(ElemType e))
{
    LinkQNode *iter;

    assert(queue);

    iter = queue->front->next;
    while(iter)
    {
        visit_func(iter->elem);
        iter = iter->next;
    }
}


#if defined ENABLE_UNITTEST

void LinkQueue_test_01(void)
{
    int i;
    ElemType e;
    LinkQueue queue;

    DEBUG_LOG(LOG_DEBUG_LEVEL, "call start", __func__);
    LinkQueue_init(&queue);
    assert(!LinkQueue_length(&queue));

    for(i=1; i<=10; ++i)
    {
        assert(LinkQueue_en_queue(&queue, i));
    }

    assert(LinkQueue_length(&queue));

    for(i=1; i<-10; ++i)
    {
        assert(LinkQueue_de_queue(&queue, &e));
        assert(e == i);
    }

    assert(LinkQueue_length(&queue));

    LinkQueue_destroy(&queue);
    DEBUG_LOG(LOG_DEBUG_LEVEL, "call done", __func__);
}

#endif              /*  ENABLE_UNITTEST */

