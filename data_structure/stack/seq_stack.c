#include "seq_stack.h"

/*
 *  线性栈初始化
 * */
bool SeqStack_init(SeqStack *stack)
{
    assert(stack);

    stack.base = (ElemType *) malloc(sizeof(ElemType) * SEQ_STACK_INIT_SIZE);
    if(!stack.base)
    {
        DEBUG_LOG(LOG_ERROR_LEVEL, "malloc error", __func__);
        return;
    }

    memset(stack.base, 0x0, sizeof(ElemType) * SEQ_STACK_INIT_SIZE);
    stack->top = stack->base;
    stack->stack_size = SEQ_STACK_INIT_SIZE;
}

/*
 *  线性栈销毁
 * */
bool SeqStack_destroy(SeqStack *stack)
{
    assert(stack);

    if(stack->stack_size)
    {
        free(stack->base);
        stack->base = NULL;
        stack->top = NULL;
        stack->stack_size = 0;
    }
}

/*
 *  线性栈清空
 * */
bool SeqStack_clear(SeqStack *stack)
{
    ElemType *iter, e;

    assert(stack);

    while(stack->top != stack->base)
    {
        SeqStack_pop(stack, e);
    }
}

/*
 *  线性栈是否为空栈
 * */
bool SeqStack_empty(const SeqStack *stack)
{
    return stack->top == stack->base? true: false;
}

/*
 *  查询线性栈长度
 * */
int SeqStack_length(const SeqStack *stack)
{
    return (stack->top - stack->base);
}

/*
 *  查询栈顶项
 * */
bool SeqStack_get_top(const SeqStack *stack, ElemType *e)
{
    assert(stack);
    if(stack->base == stack->top)
        return false;

    *e = *(stack->top-1);
    return true;
}

/*
 *  入栈操作
 * */
bool SeqStack_push(SeqStack *stack, ElemType e)
{
    bool ret = false;
    ElemType *iterm = NULL;

    assert(stack);

    if(SeqStack_length(stack) >= stack->stack_size)
    {
        item = (ElemType*) malloc(sizeof(ElemType) * (stack->stack_size + SEQ_STACK_INCREMENT));
        if(!item)
        {
            DEBUG_LOG(LOG_ERROR_LEVEL, "malloc error", __func__)
            return ret;
        }
        memset(item, 0x0, sizeof(ElemType) * (stack->stack_size + SEQ_STACK_INCREMENT));
        // 拷贝原始栈的数据
        memcpy(item, stack->base, sizeof(ElemType) * stack->stack_size);
        free(stack->base);
        stack->base = item;
        stack->stack_size += SEQ_STACK_INCREMENT;
    }

    *stack->top++ = e;
    return true;
}

/*
 *  出栈操作
 * */
bool SeqStack_pop(SeqStack *stack, ElemType *e)
{
    assert(stack);

    if(stack->top == stack->base)
        return false;

    *e = *--stack->top;
    return true;
}

/*
 *  遍历栈操作
 * */
bool SeqStack_traverse(const SeqStack *stack, bool(*visit_func)(ElemType e))
{
    ElemType *iter;

    assert(stack);
    if(!visit)
        return false;

    iter = stack->base;
    while(iter != stack->top)
    {
        visit_func(*iter);
        iter++;
    }
    return true;
}

#if defined ENABLE_UNITTEST

bool _visit_func(ElemType e)
{
    printf("%d ", e);
    return true;
} 

void SeqStack_test_01(void)
{
    int i;
    ElemType e;
    SeqStack stack;
    SeqStack_init(&stack);

    assert(!SeqStack_length(&stack));

    for (i=1, i<=10; ++i)
    {
        SeqStack_push(&stack, i);
    }

    assert(SeqStack_length(&stack) == 10);

    SeqStack_traverse(&stack, _visit_func);

    assert(SeqStack_get_top(&stack, &e));
    assert(e == 10);

    for(i=1; i<=10; ++i)
    {
        SeqStack_pop(&stack, &e);
    }
    assert(!SeqStack_length(&stack));

    SeqStack_destroy(&stack);
}

#endif          /*  ENABLE_UNITTEST */


/*

应用
1 进制转换

2 括号匹配的校验

3 行编辑程序

4 迷宫求解

5. 表达式求值

6. 栈还有一个应用, 在程序设计语言中实现递归

7. 八皇后问题, 汉诺塔问题



*/
