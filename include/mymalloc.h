/*
** 包装 stdlib 库的 malloc, free函数, 追踪内存分配情况     
**/
#ifndef MYMALLOC_H
#define MYMALLOC_H


#include <stdlib.h>

#if defined ENABLE_MYMALLOC

typedef struct
{
    unsigned long long int peak_val;
    unsigned long long int cur_val;
}MemUsage;


void *mymalloc(size_t size);

void free(void *ptr);

#define MALLOC(size) mymalloc(size)
#define FREE(ptr)   myfree(ptr)

#else

#define MALLOC(size) malloc(size)
#define FREE(ptr)    free(ptr)

#endif              /*  ENABLE_MYMALLOC    */

#endif

