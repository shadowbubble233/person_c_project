#include "sort.h"

static bool _visit_func(void *elem)
{
    printf("%d ", *(ElemType*)elem);
    return true;
}


bool sort_traverse(const void *base, size_t len, size_t size, bool(*visit_func)(void *elem))
{
    void *iter;
    bool ret = false;

    iter = (void*)base;
    while(iter < base + size * len)
    {
        ret = visit_func(iter);
        if(!ret)
        {
            DEBUG_LOG(LOG_ERROR_LEVEL, "data access error", __func__);
            return ret;
        }

        iter += size;
    }
    printf("\n");
    ret = true;
    return ret;
}


static int _sort_compare_func(const void *a, const void *b)
{
    ElemType *elem_a, *elem_b;
    elem_a = (ElemType*)a;
    elem_b = (ElemType*)b;
    return *elem_a - *elem_b;    
}


void _exchange_value(void *a, void *b)
{
    ElemType *elem_a, *elem_b, elem;
    elem_a = (ElemType *)a;
    elem_b = (ElemType *)b;
    
    // 交换元素
    elem = *elem_a;
    *elem_a = *elem_b;
    *elem_b = elem;
}



/*  冒泡排序    */
void bubble_sort(void *base, size_t len, size_t size, sort_compare_func compare_func)
{
    void *iter, *iter_next;
    int i, j;

    for(i=0; i<len-1; ++i)
    {
       for(j=0; j<len-i-1; ++j)
        {
            iter = base + j * size;
            iter_next = base + (j+1) * size;
            if(compare_func(iter, iter_next) > 0)
            {
                _exchange_value(iter, iter_next); 
            }
        } 
    }
    
}


/*  快速排序    */
static void _quick_sort(void *base, size_t len, size_t size, sort_compare_func compare_func, void *low_ptr, void *high_ptr);

void quick_sort(void *base, size_t len, size_t size, sort_compare_func compare_func)
{
    void *low_ptr = base;
    void *high_ptr = base + (len-1) * size;
    _quick_sort(base, len, size, compare_func, low_ptr, high_ptr); 
}

static void _quick_sort(void *base, size_t len, size_t size, sort_compare_func compare_func, void *low_ptr, void *high_ptr)
{
    void *i_ptr, *j_ptr, *key_ptr;

    if(low_ptr >= high_ptr)
        return;

    key_ptr = low_ptr;
    i_ptr = low_ptr;
    j_ptr = high_ptr;
    while(i_ptr < j_ptr)
    {
        // j 位置找一个比 key 小的
        while( i_ptr < j_ptr && compare_func(key_ptr, j_ptr) <= 0)  
            j_ptr -= size;  
   
        if(i_ptr >= j_ptr)
            break;

        _exchange_value(key_ptr, j_ptr); 
        
        // i 位置找一个比 key 大的
        while(i_ptr < j_ptr && compare_func(key_ptr, i_ptr) >= 0)
            i_ptr += size;
        
        if(i_ptr >= j_ptr)
            break;
        _exchange_value(key_ptr, i_ptr);
    }

    _quick_sort(base, len, size, compare_func, low_ptr, i_ptr);
    _quick_sort(base, len, size, compare_func, i_ptr+size, high_ptr);
}


/*  选择排序    */
void select_sort(void *base, size_t len, size_t size, sort_compare_func compare_func)
{
    void *iter, *last_val;
    int i, j;

    for(i=0; i<len; ++i)
    {
        for(j=0; j<len-i-1; ++j)
        {
            iter = base + j * size;
            last_val = base + (len-i-1) * size;
            if(compare_func(iter, last_val) > 0)
            {
                _exchange_value(iter, last_val);
            }
        } 
    }

}


/*  插入排序    */
void insert_sort(void *base, size_t len, size_t size, sort_compare_func compare_func)
{
    void *iter_ptr, *prior_ptr;
    int i, j;
    
    for(i = 0; i<len; ++i)
    {
        for(j = i; j >= 1; --j)
        {
            iter_ptr = base + j * size;
            prior_ptr = base + (j-1) * size;
            if(compare_func(iter_ptr, prior_ptr) < 0)
            {
                _exchange_value(iter_ptr, prior_ptr);
            }
        }
    }

}


/*  希尔排序(缩小增量排序)  */

static void _xier_sort(void *base, size_t len, size_t size, sort_compare_func compare_func, int step);

void xier_sort(void *base, size_t len, size_t size, sort_compare_func compare_func)
{
    int step = len/2;
    _xier_sort(base, len, size, compare_func, step);
}

static void _xier_sort(void *base, size_t len, size_t size, sort_compare_func compare_func, int step)
{
    int i, j;
    void *iter_ptr, *prior_ptr;
    if(step <1)
        return;
     
    for(i=0; i<len; i+= step)
    {
        for(j=i; j>=step; j-=step)
        {
            iter_ptr = base + j * size;
            prior_ptr = base + (j-step) * size; 
            if(compare_func(iter_ptr, prior_ptr) < 0)
            {
                _exchange_value(iter_ptr, prior_ptr);
            }
        }
    }
    _xier_sort(base, len, size, compare_func, step/2);
} 



/*  归并排序   */

static void _split_buf(void *base, size_t len, size_t size, sort_compare_func compare_func, void *start_ptr, void *end_ptr);

static void _merge_buf(void *base, size_t len, size_t size, sort_compare_func compare_func, void *start_ptr, void *mid_ptr, void *end_ptr);

void merger_sort(void *base, size_t len, size_t size, sort_compare_func compare_func)
{
    void *start_ptr, *end_ptr;
    start_ptr = base;
    end_ptr = base + len * size;

    _split_buf(base, len, size, compare_func, start_ptr, end_ptr);        
}


static void _split_buf(void *base, size_t len, size_t size, sort_compare_func compare_func, void *start_ptr, void *end_ptr)
{
    void *mid_ptr;  
    if(start_ptr >= end_ptr)
        return;

    mid_ptr = (void*) (((size_t)start_ptr + (size_t)end_ptr )/2);
    _split_buf(base, len, size, compare_func, start_ptr, mid_ptr);
    _split_buf(base, len, size, compare_func, mid_ptr, end_ptr);
    _merge_buf(base, len, size, compare_func, start_ptr, mid_ptr, end_ptr);
}

static void _merge_buf(void *base, size_t len, size_t size, sort_compare_func compare_func, void *start_ptr, void *mid_ptr, void *end_ptr)
{
    void *i_ptr, *j_ptr, *iter_ptr;
    i_ptr = start_ptr;
    j_ptr = mid_ptr;
    
    void *buf = malloc(end_ptr - start_ptr);
    if(!buf)
    {
        DEBUG_LOG(LOG_ERROR_LEVEL, "buf malloc error", __func__);
        return;
    }
    memset(buf, 0x0, end_ptr - start_ptr);

    iter_ptr = buf;
    while(i_ptr < mid_ptr && j_ptr < end_ptr)
    {
        if(compare_func(i_ptr, j_ptr) > 0)
        {
            *(ElemType*)iter_ptr = *(ElemType*)j_ptr;
            i_ptr += size;
        }
        else
        {
            *(ElemType*)iter_ptr = *(ElemType*)i_ptr;
            i_ptr += size;
        }
        iter_ptr += size;
    }

    while(i_ptr < mid_ptr)
    {
        memcpy(iter_ptr, i_ptr, mid_ptr-i_ptr);
    }

    while(j_ptr < end_ptr)
    {
        memcpy(iter_ptr, j_ptr, end_ptr-j_ptr);
    } 
    memcpy(base, buf, end_ptr-start_ptr); 
}


/*  堆排序    */
#define L_CHILD(idx)        (2 * idx + 1)
#define R_CHILD(idx)        (2 * idx + 2)

void build_heap(void *base, size_t len, size_t size, sort_compare_func compare_func);

void adjust_heap(void *base, size_t len, size_t size, sort_compare_func compare_func, int idx);

void heap_sort(void *base, size_t len, size_t size, sort_compare_func compare_func)
{
    int i = 0;
    void *iter_ptr, *first_ptr;
    build_heap(base, len, size, compare_func);
 
    // 堆排序,
    first_ptr = base; 
    for(i=len-1; i>=0; --i)
    {
        iter_ptr = base + i * size;
        _exchange_value(first_ptr, iter_ptr);  
        adjust_heap(base, i, size, compare_func, 0);
    } 
}

void build_heap(void *base, size_t len, size_t size, sort_compare_func compare_func)
{
    int i = (int)len/2;
    for(; i>=0; --i)
    {
        adjust_heap(base, len, size, compare_func, i);
    }
}

void adjust_heap(void *base, size_t len, size_t size, sort_compare_func compare_func, int idx)
{
    void *root_ptr, *lchild_ptr, *rchild_ptr, *item_ptr;
    if(idx >= len)
        return;

    root_ptr = base + idx * size;
    item_ptr = root_ptr;
    if(L_CHILD(idx) < len)
    {
        lchild_ptr = base + L_CHILD(idx) * size;
        item_ptr = compare_func(item_ptr, lchild_ptr) >= 0? item_ptr: lchild_ptr; 
    }
  
    if(R_CHILD(idx) < len)
    {
        rchild_ptr = base + R_CHILD(idx) * size;
        item_ptr = compare_func(item_ptr, rchild_ptr) >= 0? item_ptr: rchild_ptr;
    } 

    if(item_ptr != root_ptr)
    {
        _exchange_value(item_ptr, root_ptr);
    }
    adjust_heap(base, len, size, compare_func, L_CHILD(idx));
    adjust_heap(base, len, size, compare_func, R_CHILD(idx));
}


/*  tim sort 排序*/
void tim_sort(void *base, size_t len, size_t size, sort_compare_func compare_func)
{

}


#if defined ENABLE_UNITTEST

void Sort_test_01(void)
{
    #define arr_len 10
    // 排序前的数据缓冲区
    const ElemType origin_arr[arr_len] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    // 排序后的正确的数据缓冲区(用于断言, 测试是否排序正确)
    const ElemType aim_arr[arr_len] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 
    // 排序用的数据缓冲区
    ElemType arr[arr_len];

    DEBUG_LOG(LOG_DEBUG_LEVEL, "called start", __func__);

    // 1 冒泡排序
    DEBUG_LOG(LOG_DEBUG_LEVEL, "test sort_bubble", NULL);
    DEBUG_LOG(LOG_DEBUG_LEVEL, "before sort", NULL);
    // 重置待排序的数据缓冲区
    memcpy(arr, origin_arr, sizeof(ElemType) * arr_len);
    sort_traverse(arr, arr_len, sizeof(ElemType), _visit_func);
    bubble_sort(arr, arr_len, sizeof(ElemType), _sort_compare_func);
    sort_traverse(arr, arr_len, sizeof(ElemType), _visit_func);
    // 测试排序结果
    assert(!memcmp(arr, aim_arr, sizeof(ElemType) * arr_len));

    // 2 快速排序
    DEBUG_LOG(LOG_DEBUG_LEVEL, "test quick_sort", NULL);
    DEBUG_LOG(LOG_DEBUG_LEVEL, "before sort", NULL);
    // 重置待排序的数据缓冲区
    memcpy(arr, origin_arr, sizeof(ElemType) * arr_len); 
    sort_traverse(arr, arr_len, sizeof(ElemType), _visit_func);
    quick_sort(arr, arr_len, sizeof(ElemType), _sort_compare_func);
    sort_traverse(arr, arr_len, sizeof(ElemType), _visit_func);
    // 测试排序结果
    assert(!memcmp(arr, aim_arr, sizeof(ElemType) * arr_len));

    // 3 选择排序
    DEBUG_LOG(LOG_DEBUG_LEVEL, "test select_sort", NULL);
    DEBUG_LOG(LOG_DEBUG_LEVEL, "before sort", NULL);
    // 重置待排序的数据缓冲区
    memcpy(arr, origin_arr, sizeof(ElemType) * arr_len);
    sort_traverse(arr, arr_len, sizeof(ElemType), _visit_func);
    select_sort(arr, arr_len, sizeof(ElemType), _sort_compare_func);
    sort_traverse(arr, arr_len, sizeof(ElemType), _visit_func);
    // 测试排序结果
    assert(!memcmp(arr, aim_arr, sizeof(ElemType) * arr_len));

    // 4 插入排序
    DEBUG_LOG(LOG_DEBUG_LEVEL, "test insert_sort", NULL);
    DEBUG_LOG(LOG_DEBUG_LEVEL, "before sort", NULL);
    // 重置待排序的数据缓冲区
    memcpy(arr, origin_arr, sizeof(ElemType) * arr_len);
    sort_traverse(arr, arr_len, sizeof(ElemType), _visit_func);
    insert_sort(arr, arr_len, sizeof(ElemType), _sort_compare_func);
    sort_traverse(arr, arr_len, sizeof(ElemType), _visit_func);
    assert(!memcmp(arr, aim_arr, sizeof(ElemType) * arr_len));

    // 5 希尔排序
    DEBUG_LOG(LOG_DEBUG_LEVEL, "test xier_sort", NULL);
    DEBUG_LOG(LOG_DEBUG_LEVEL, "before sort", NULL);
    // 重置待排序的数据缓冲区
    memcpy(arr, origin_arr, sizeof(ElemType) * arr_len); 
    sort_traverse(arr, arr_len, sizeof(ElemType), _visit_func);
    xier_sort(arr, arr_len, sizeof(ElemType), _sort_compare_func);
    sort_traverse(arr, arr_len, sizeof(ElemType), _visit_func);    
    assert(!memcmp(arr, aim_arr, sizeof(ElemType) * arr_len));
   
    // 6 归并排序
    DEBUG_LOG(LOG_DEBUG_LEVEL, "test merger_sort", NULL);
    DEBUG_LOG(LOG_DEBUG_LEVEL, "before sort", NULL);
    // 重置待排序的数据缓冲区
    memcpy(arr, origin_arr, sizeof(ElemType) * arr_len); 
    sort_traverse(arr, arr_len, sizeof(ElemType), _visit_func);
    xier_sort(arr, arr_len, sizeof(ElemType), _sort_compare_func);
    sort_traverse(arr, arr_len, sizeof(ElemType), _visit_func);    
    assert(!memcmp(arr, aim_arr, sizeof(ElemType) * arr_len));

    // 7 堆排序
    DEBUG_LOG(LOG_DEBUG_LEVEL, "test heap_sort", NULL);
    DEBUG_LOG(LOG_DEBUG_LEVEL, "before sort", NULL);
    // 重置待排序的数据缓冲区
    memcpy(arr, origin_arr, sizeof(ElemType) * arr_len); 
    sort_traverse(arr, arr_len, sizeof(ElemType), _visit_func);
    heap_sort(arr, arr_len, sizeof(ElemType), _sort_compare_func);
    sort_traverse(arr, arr_len, sizeof(ElemType), _visit_func);    
    assert(!memcmp(arr, aim_arr, sizeof(ElemType) * arr_len));

    // 8 tim sort 排序
    DEBUG_LOG(LOG_DEBUG_LEVEL, "test tim_sort", NULL);
    DEBUG_LOG(LOG_DEBUG_LEVEL, "before sort", NULL);
    // 重置待排序的数据缓冲区
    memcpy(arr, origin_arr, sizeof(ElemType) * arr_len); 
    sort_traverse(arr, arr_len, sizeof(ElemType), _visit_func);
    tim_sort(arr, arr_len, sizeof(ElemType), _sort_compare_func);
    sort_traverse(arr, arr_len, sizeof(ElemType), _visit_func);    
    //assert(!memcmp(arr, aim_arr, sizeof(ElemType) * arr_len));

    DEBUG_LOG(LOG_DEBUG_LEVEL, "called done", __func__);
    DEBUG_LOG(LOG_DEBUG_LEVEL, NULL, NULL);
}

#endif

