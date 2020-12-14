/*
 *  二叉树(顺序存储结构)
 * */
#ifndef SEQ_BINARY_TREE_H
#define SEQ_BINARY_TREE_H

#include "project_config.h"


#define MAX_TREE_SIZE       100             // 二叉树最大结点数


typedef ElemType SeqBinaryTree[MAX_TREE_SIZE];


/*  按先序次序输入二叉树结点的值(一个数字)*/
bool SeqBinaryTree_create_tree(SeqBinaryTree *tree);


/*  先序遍历二叉树  */
bool SeqBinaryTree_pre_order_traverse(SeqBinaryTree *tree, bool(*visit_func)(ElemType e));

/*  中序遍历二叉树  */
bool SeqBinaryTree_in_order_traverse(SeqBinaryTree *tree, bool(*visit_func)(ElemType e));

/*  后序遍历二叉树  */
bool SeqBinaryTree_post_order_traverse(SeqBinaryTree *tree, bool(*visit_func)(ElemType e));

/*  层次遍历二叉树  */
bbool SeqBinaryTree_level_order_traverse(SeqBinaryTree *tree, bool(*visit_func)(ElemType e));

#endif

