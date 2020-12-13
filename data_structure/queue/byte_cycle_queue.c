#include "byte_cycle_queue.h"


bool ByteCycleQueue_init(ByteCycleQueue *queue, int buf_size)
{
    assert(queue);

    if(buf_size <= 0)
        buf_size = DEFAULT_CYCLE_QUEUE_SIZE;

    queue->base = (char*) malloc(sizeof(char) * buf_size);
    if(!queue->base)
    {
        DEBUG_LOG(LOG_ERROR_LEVEL, "malloc error", __func__);
        return false;
    }

    memset(queue->base, 0x0, sizeof(char) * buf_size);
    queue->read_idx = 0;
    queue->write_idx = 0;
    queue->length = 0;
    queue->buf_size = buf_size;
    return true;
}

bool ByteCycleQueue_destroy(ByteCycleQueue *queue)
{
    assert(queue);

    if(queue->base)
    {
        free(queue->base);
        queue->base = NULL;
        queue->read_idx = 0;
        queue->write_idx = 0;
        queue->length = 0;
        queue->buf_size = 0;
    }
    return true;
}


bool ByteCycleQueue_clear(ByteCycleQueue *queue)
{
    assert(queue);

    memset(queue->base, 0x0, queue->buf_size);
    queue->read_idx = 0;
    queue->write_idx = 0;
    queue->length = 0;
    return true;
}


bool ByteCycleQueue_empty(ByteCycleQueue *queue)
{
    assert(queue);
    return queue->length == 0 ? true: false;
}


int ByteCycleQueue_length(ByteCycleQueue *queue)
{
    assert(queue);
    return queue->length;
}

bool ByteCycleQueue_get_head(ByteCycleQueue *queue, char *out_buf, int out_len)
{
    bool ret = false;
    assert(queue);

    if(queue->length < out_len)
    {
        DEBUG_LOG(LOG_ERROR_LEVEL, "out_len error", __func__);
        return ret;
    }

    if(queue->read_idx + out_len <= queue->buf_size)
    {
        memcpy(out_buf, queue->base + queue->read_idx, out_len);
    }
    else
    {
        memcpy(out_buf, queue->base + queue->read_idx, queue->buf_size - queue->read_idx);
        memcpy(out_buf + (queue->buf_size - out_len), queue->base, (out_len - queue->buf_size + queue->read_idx));
    }

    return true;
}


bool ByteCycleQueue_en_queue(ByteCycleQueue *queue, char *in_buf, int in_len)
{
    bool ret = false;
    assert(queue);

    if(queue->buf_size - queue->length < in_len)
    {
        DEBUG_LOG(LOG_ERROR_LEVEL, "缓冲区内存不足, 无法写入数据", __func__);
        return ret;
    }

    if(queue->write_idx + in_len <= queue->buf_size)
    {
        memcpy(queue->base + queue->write_idx, in_buf, in_len);
    }
    else
    {
        memcpy(queue->base + queue->write_idx, in_buf, queue->buf_size - queue->write_idx);
        memcpy(queue->base, in_buf + (queue->buf_size - queue->write_idx), in_len - queue->buf_size + queue->write_idx);
    }

    queue->length += in_len;
    return true;
}


bool ByteCycleQueue_de_queue(ByteCycleQueue *queue, char *out_buf, int out_len)
{
    bool ret = false;
    assert(queue);

    if(queue->length < out_len)
    {
        DEBUG_LOG(LOG_ERROR_LEVEL, "out_len error", __func__);
        return ret;
    }

    if(queue->read_idx + out_len <= queue->buf_size)
    {
        memcpy(out_buf, queue->base + queue->read_idx, out_len);
    }
    else
    {
        memcpy(out_buf, queue->base + queue->read_idx, queue->buf_size - queue->read_idx);
        memcpy(out_buf + (queue->buf_size - out_len), queue->base, (out_len - queue->buf_size + queue->read_idx));
    }

    queue->length-=out_len;
    return true;
}

void ByteCycleQueue_traverse(const ByteCycleQueue *queue, void (*visit_func)(char* e))
{
    char *iter;
    assert(queue);

    if(queue->length == 0)
        return;

    // 访问第一部分数据
    iter = queue->base + queue->read_idx;
    while(iter < queue->base + queue->buf_size)
    {
        visit_func(iter++);
    }

    // 访问第二部分数据
    iter = queue->base;
    while(iter < queue->base + queue->write_idx)
    {
        visit_func(iter++);
    }
    printf("\n");
}


#if defined ENABLE_UNITTEST

static void _visit_func(char *e)
{
    printf("%c", *e);
}

void ByteCycleQueue_test_01(void)
{
    ByteCycleQueue queue;
    char in_buf[256];
    char out_buf[256];
    memset(in_buf, 0x0, 256);
    memset(out_buf, 0x0, 256);

    DEBUG_LOG(LOG_DEBUG_LEVEL, "called start", __func__);
    ByteCycleQueue_init(&queue, 0);

    strcpy(in_buf, "abcdefg") ;
    ByteCycleQueue_en_queue(&queue, in_buf, strlen(in_buf));

    ByteCycleQueue_traverse(&queue, _visit_func);

    ByteCycleQueue_get_head(&queue, out_buf, 7);
    assert(!strcmp(out_buf, in_buf));

    memset(&out_buf, 0x0, sizeof(256));
    ByteCycleQueue_de_queue(&queue, out_buf, 7);
    assert(!strcmp(out_buf, in_buf));

    DEBUG_LOG(LOG_DEBUG_LEVEL, out_buf, __func__);

    ByteCycleQueue_destroy(&queue);

    DEBUG_LOG(LOG_DEBUG_LEVEL, "called done", __func__);
}

#endif              /*  ENABLE_UNITTEST */
