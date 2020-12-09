#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

#define DEBUG_MODE

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define STRCMP(a, op, b)    (strcmp(a, b) op 0)


typedef int ElemType;


typedef enum
{
    false=0,
    true
}bool;


/*
 *  日志输出级别
 * */
#define LOG_DEBUG_LEVEL     1
#define LOG_INFO_LEVEL      2
#define LOG_WARN_LEVEL      3
#define LOG_ERROR_LEVEL     4
#define LOG_FATAL_LEVEL     5
#define LOG_NONE_LEVEL      6                                       /*  禁用任何日志输出 */

// 设置日志输出到屏幕, 控制级别
#define LOG_HANDLE_LEVEL    LOG_DEBUG_LEVEL

// 设置日志记录到文件, 控制级别
#define LOG_WRITE_LEVEL     LOG_INFO_LEVEL

#if defined DEBUG_MODE
/*
 *  调试日志
 * */
void debug_log(int level, const char *msg, const char *position);
#endif


#if defined DEBUG_MODE

#define DEBUG_LOG(level, msg, position) debug_log(level, msg, position)
#else

#define DEBUG_LOG(level, msg, position)
#endif


/*
 *  执行单元测试代码
 * */
#define ENABLE_UNITTEST


/*
*   启动内存追踪, 跟踪内存分配情况
* */
//#define ENABLE_MYMALLOC

#endif

