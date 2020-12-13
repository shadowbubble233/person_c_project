/*
    字节循环缓冲区 (字节循环缓冲队列)
*/
#ifndef BYTE_CYCLE_QUEUE
#define BYTE_CYCLE_QUEUE

#include "project_config.h"

#define DEFAULT_CYCLE_QUEUE_SIZE    2048


typedef struct
{
    char *base;                                 // 缓冲池
    int read_idx;                               // 读指针
    int write_idx;                              // 写指针
    int length;                                 // 数据长度
    int buf_size;                               // 缓冲区大小
} ByteCycleQueue;


/*
 *  字节循环缓冲区初始化
 * */
bool ByteCycleQueue_init(ByteCycleQueue *queue, int buf_size);

/*
 *  字节循环缓冲区销毁
 * */
bool ByteCycleQueue_destroy(ByteCycleQueue *queue);

/*
 *  字节循环缓冲区清空
 * */
bool ByteCycleQueue_clear(ByteCycleQueue *queue);

/*
 *  字节循环缓冲区判断是否为空
 * */
bool ByteCycleQueue_empty(ByteCycleQueue *queue);

/*
 *  字节循环缓冲区，查询队列长度
 * */
int ByteCycleQueue_length(ByteCycleQueue *queue);

/*
 *  字节循环缓冲区, 返回队头元素
 * */
bool ByteCycleQueue_get_head(ByteCycleQueue *queue, char *out_buf, int out_len);

/*
 *  字节循环缓冲区， 入队操作 (队尾插入新元素)
 * */
bool ByteCycleQueue_en_queue(ByteCycleQueue *queue, char *in_buf, int in_len);

/*
 *  字节循环缓冲区, 出队操作 (删除队头元素)
 * */
bool ByteCycleQueue_de_queue(ByteCycleQueue *queue, char *out_buf, int out_len);

/*
 *  字节循环缓冲区, 遍历操作
 * */
void ByteCycleQueue_traverse(const ByteCycleQueue *queue, void (*visit_func)(char* e));


#if defined ENABLE_UNITTEST

void ByteCycleQueue_test_01(void);

#endif              /*  ENABLE_UNITTEST */


#endif
