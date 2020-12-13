#include <stdio.h>

#include "project_config.h"

/*  单元测试 */
#if defined ENABLE_UNITTEST

/*  测试 线性表函数  */
#include "seq_list.h"
void test_single_seq_list(void);

/*  测试 单链表函数  */
#include "link_list.h"
void test_single_link_list(void);

/*  测试 循环单向单链表函数  */
#include "cycle_link_list.h"
void test_cycle_link_list(void);

/*  测试 循环双向链表函数   */
#include "cycle_dlink_list.h"
void test_cycle_dlink_list(void);

/*  测试 顺序栈函数 */
#include "seq_stack.h"
void test_seq_stack(void);

/*  测试 链式队列函数   */
#include "link_queue.h"
void test_link_queue(void);

/*  测试 字节循环缓冲区*/
#include "byte_cycle_queue.h"
void test_byte_cycle_queue(void);


/*  测试 排序算法   */
#include "sort.h"
void test_sort(void);


#endif      /*  ENABLE_UNITTEST  */

int main(void)
{
    DEBUG_LOG(LOG_INFO_LEVEL, "program start", __func__);   

    #if defined ENABLE_UNITTEST
    // 单链表结构
    test_single_seq_list();
    test_single_link_list();
    test_cycle_link_list();
    test_cycle_dlink_list();

    // 栈
    test_seq_stack(); 

    // 队列
    test_link_queue(); 
    test_byte_cycle_queue();

    // 堆


    // 排序算法
    test_sort();

    #endif
    

    DEBUG_LOG(LOG_INFO_LEVEL, "program end", __func__); 
    return 0;
}


#if defined ENABLE_UNITTEST

void test_single_seq_list(void)
{
    SeqList_test_01();
    SeqList_test_02();
    SeqList_test_03();
}

void test_single_link_list(void)
{
    LinkList_test_01();
}

void test_cycle_link_list(void)
{
    CycleLinkList_test_01();
}

void test_cycle_dlink_list(void)
{
    CycleDLinkList_test_01();
}

void test_seq_stack(void)
{
    SeqStack_test_01();
}

void test_link_queue(void)
{
    LinkQueue_test_01();
}


void test_byte_cycle_queue(void)
{
    ByteCycleQueue_test_01();
}


void test_sort(void)
{
    Sort_test_01();
}

#endif

/* 日志处理函数, 根据日志级别过滤输出  */
#if defined DEBUG_MODE

static char LOG_MAPPING[6][8] = {
    "[     ]",
    "[DEBUG]",
    "[INFO ]",
    "[WARN ]",
    "[ERROR]",
    "[FATAL]",
};

void debug_log(int level, const char *msg, const char *position)
{
    if(level <LOG_DEBUG_LEVEL || level > LOG_FATAL_LEVEL)
        return;

    if (level >= LOG_HANDLE_LEVEL)
    {
        if(msg && position)
            printf("%s: %s, %s\n", LOG_MAPPING[level], msg, position);
        else if(msg && !position)
            printf("%s: %s\n", LOG_MAPPING[level], msg);
        else if(!msg && !position)
            printf("\n");
    }

}

#endif


