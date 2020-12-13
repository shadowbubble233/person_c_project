#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H

typedef struct _QNode
{
    ElemType elem;
    struct _QNode *next;
}LinkQNode, *LinkQueuePtr;


typedef struct
{
    LinkQueuePtr front;                 // 队头指针
    LinkQueuePtr rear;                  // 队尾指针
    int length;                             // 队列长度
} LinkQueue;


/*
 *  链式队列初始化
 * */
bool LinkQueue_init(LinkQueue *queue);

/*
 *  链式队列销毁
 * */
bool LinkQueue_destroy(LinkQueue *queue);

/*
 *  链式队列清空
 * */
bool LinkQueue_clear(LinkQueue *queue);

/*
 *  链式队列判断是否为空
 * */
bool LinkQueue_empty(LinkQueue *queue);

/*
 *  链式队列，查询队列长度
 * */
int LinkQueue_length(LinkQueue *queue);

/*
 *  链式队列, 返回队头元素
 * */
bool LinkQueue_get_head(LinkQueue *queue, ElemType *e);

/*
 *  链式队列， 入队操作 (队尾插入新元素)
 * */
bool LinkQueue_en_queue(LinkQueue *queue, ElemType e);

/*
 *  链式队列, 出队操作 (删除队头元素)
 * */
bool LinkQueue_de_queue(LinkQueue *queue, ElemType *e);

/*
 *  链式队列, 遍历操作
 * */
void LinkQueue_traverse(const LinkQueue *queue, void (*visit_func)(ElemType e));


#if defined ENABLE_UNITTEST

void LinkQueue_test_01(void);

#endif              /*  ENABLE_UNITTEST */


#endif

