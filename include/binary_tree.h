/*
 *  二叉树(链式存储结构)
 * */
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "project_config.h"


typedef struct _BiTNode
{
    ElemType elem;
    struct _BiTNode *lchild, *rchild;
} BiTNode, *BiTree;


/*  按先序次序输入二叉树结点的值(一个数字)*/
bool BinaryTree_create_tree(BinaryTree *tree);


/*  先序遍历二叉树  */
bool BinaryTree_pre_order_traverse(BinaryTree *tree, bool(*visit_func)(ElemType e));

/*  中序遍历二叉树  */
bool BinaryTree_in_order_traverse(BinaryTree *tree, bool(*visit_func)(ElemType e));

/*  后序遍历二叉树  */
bool BinaryTree_post_order_traverse(BinaryTree *tree, bool(*visit_func)(ElemType e));

/*  层次遍历二叉树  */
bool BinaryTree_level_order_traverse(BinaryTree *tree, bool(*visit_func)(ElemType e));

#endif

