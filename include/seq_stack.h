/*
 *  线性栈，数据结构定义
 * */
#ifndef SEQ_STACK_H
#define SEQ_STACK_H

#include "project_config.h"

#define SEQ_STACK_INIT_SIZE     100;            // 线性栈存储空间初始分量
#define SEQ_STACK_ICREMENT      10;             // 线性栈存储空间分配增量


typedef struct
{
    ElemType *base;                             // 栈底指针
    ElemType *top;                              // 栈顶指针
    int stacksize;                              // 当前已分配的存储空间
}SeqStack;


/*
 *  线性栈初始化
 * */
bool SeqStack_init(SeqStack *stack);

/*
 *  线性栈销毁
 * */
bool SeqStack_destroy(SeqStack *stack);

/*
 *  线性栈清空
 * */
bool SeqStack_clear(SeqStack *stack);

/*
 *  线性栈是否为空栈
 * */
bool SeqStack_empty(const SeqStack *stack);

/*
 *  查询线性栈长度
 * */
int SeqStack_length(const SeqStack *stack);

/*
 *  查询栈顶项
 * */
bool SeqStack_get_top(const SeqStack *stack);

/*
 *  入栈操作
 * */
bool SeqStack_push(SeqStack *stack, ElemType e);

/*
 *  出栈操作
 * */
bool SeqStack_pop(SeqStack *stack, ElemType *e);

/*
 *  遍历栈操作
 * */
bool SeqStack_traverse(const SeqStack *stack, bool(*visit)(ElemType e));

#endif

