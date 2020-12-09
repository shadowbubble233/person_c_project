#include <stdio.h>

#include "project_config.h"

/*  单元测试 */
#if defined ENABLE_UNITTEST

#include "seq_list.h"
void test_single_seq_list(void);


#endif

int main(void)
{
    DEBUG_LOG(LOG_INFO_LEVEL, "program start", "main");   

    #if defined ENABLE_UNITTEST

    test_single_seq_list();
    #endif
    

    DEBUG_LOG(LOG_INFO_LEVEL, "program end", "main"); 
    return 0;
}


#if defined ENABLE_UNITTEST

void test_single_seq_list(void)
{
    SeqList_test_01();
    SeqList_test_02();
    SeqList_test_03();
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


