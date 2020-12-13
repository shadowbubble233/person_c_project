#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "project_config.h"

typedef struct
{
    char *base;                         // 缓冲区基地址

} PriorityQeueue;


/*
 *  链式队列初始化
 * */
bool PriorityQeueue_init(PriorityQeueue *queue);

/*
 *  链式队列销毁
 * */
bool PriorityQeueue_destroy(PriorityQeueue *queue);

/*
 *  链式队列清空
 * */
bool PriorityQeueue_clear(PriorityQeueue *queue);

/*
 *  链式队列判断是否为空
 * */
bool PriorityQeueue_empty(PriorityQeueue *queue);

/*
 *  链式队列，查询队列长度
 * */
int PriorityQeueue_length(PriorityQeueue *queue);

/*
 *  链式队列, 返回队头元素
 * */
bool PriorityQeueue_get_head(PriorityQeueue *queue);

/*
 *  链式队列， 入队操作 (队尾插入新元素)
 * */
bool PriorityQeueue_en_queue(PriorityQeueue *queue, ElemType e);

/*
 *  链式队列, 出队操作 (删除队头元素)
 * */
bool PriorityQeueue_de_queue(PriorityQeueue *queue, ElemType *e);

/*
 *  链式队列, 遍历操作
 * */
void PriorityQeueue_traverse(const PriorityQeueue *queue);

#endif

