#include "mymalloc.h"

#if defined ENABLE_MYMALLOC

static MemUsage mem_used;

/*
    需要一个 哈希表
*/

void *mymalloc(size_t size)
{
    mem_used.peak_val += size;
    mem_used.cur_val += size;
    return malloc(size);
}


void free(void *ptr)
{
    int size;
    mem_used.cur_val -= size; 
}

#endif

