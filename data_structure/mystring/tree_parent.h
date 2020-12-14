/*
 *  树, 双亲存储表示
 * */
#ifndef TREE_PARENT_H
#define TREE_PARENT_H

#include "project_config.h"

#define MAX_TREE_SIZE           100

typedef struct _PTNode
{
    ElemType elem;
    int parent;                     // 双亲位置域
}PTNode;

typedef struct 
{
    PTNode nodes[MAX_TREE_SIZE];
    int n;                          // 结点数
}PTree;


#endif

