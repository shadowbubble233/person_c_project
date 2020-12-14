/*
 *  线索叉树(链式存储结构)
 * */
#ifndef CLUE_BINARY_TREE_H
#define CLUE_BINARY_TREE_H

#include "project_config.h"


typedef enum
{
    link = 0,                                   // 指针
    clue                                        // 线索
} PointerTag;


typedef struct _BiTClueNode
{
    ElemType elem;
    struct _BiTClueNode *lchild, *rchild;       // 左右标志
    PointerTag ltag, rtag;                      // 左右标志
} BiTClueNode, *BiTClueTree;


/*  按先序次序输入二叉树结点的值(一个数字)*/
bool BitClueTree_create_tree(BitClueTree *tree);


/*  先序遍历二叉树  */
bool BitClueTree_pre_order_traverse(BitClueTree *tree, bool(*visit_func)(ElemType e));

/*  中序遍历二叉树  */
bool BitClueTree_in_order_traverse(BitClueTree *tree, bool(*visit_func)(ElemType e));

/*  后序遍历二叉树  */
bool BitClueTree_post_order_traverse(BitClueTree *tree, bool(*visit_func)(ElemType e));

/*  层次遍历二叉树  */
bool BitClueTree_level_order_traverse(BitClueTree *tree, bool(*visit_func)(ElemType e));

#endif

