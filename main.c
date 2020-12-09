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


#endif      /*  ENABLE_UNITTEST  */

int main(void)
{
    DEBUG_LOG(LOG_INFO_LEVEL, "program start", __func__);   

    #if defined ENABLE_UNITTEST
    test_single_seq_list();
    test_single_link_list();
    test_cycle_link_list();
    test_cycle_dlink_list();


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
        printf("%s: %s, %s\n", LOG_MAPPING[level], msg, position);
    }

}

#endif


