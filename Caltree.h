#ifndef CALTREE_H
#define CALTREE_H

#include "LinkedListStack.h"

typedef struct tagStackNode
{
	char Operator;
	int Value;
	struct tagStackNode* before;
}PostStack;
typedef struct tagTreeNode
{
	struct tagTreeNode* LeftNode;
	struct tagTreeNode* RightNode;
	char Data;
	int Value;
}TreeNode;

int IsOperator(char*);
int Operator(char);
void Postinit(PostStack**);
void Postpush(PostStack** stack, char Operator, int Value);
int Postpop(PostStack**);
void Postdestroystack(PostStack**);
void Postprintstack(PostStack*);
TreeNode* CreateTree(TreeNode**);
void AddTree(PostStack**, TreeNode**);
void TreePrint(TreeNode*, int);
int Evaluate(TreeNode*);
void DestroyTree(TreeNode*);

#endif CALTREE_H