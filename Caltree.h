#ifndef CALTREE_H
#define CALTREE_H

#include "LinkedListStack.h"

#define RIGHT 3
#define LEFT 4

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
typedef struct tagTreeStack TreeStack;

struct tagTreeStack
{
	TreeNode* Node;
	int depth;
	TreeStack* before;
};

int IsOperator(char*);
int Operator(char);

void Postinit(PostStack**);
void Postpush(PostStack** stack, char Operator, int Value);
int Postpop(PostStack**);
void Postdestroystack(PostStack**);
void Postprintstack(PostStack*);

void InitTreeStack(TreeStack**);
void PushTreeStack(TreeStack**, TreeNode *);
void PushTreeStackDepth(TreeStack**, TreeNode*, int);
int PopTreeStack(TreeStack**);
void DestroyTreeStack(TreeStack**);
void PrintTreeStack(TreeStack*);
int GetTreeStackSize(TreeStack*);

TreeNode* CreateTree(TreeNode**);
void AddTree(PostStack**, TreeNode**);
void TreePrint(TreeNode*, int);
void printspace(int);
int Evaluate(TreeNode*);
void DestroyTree(TreeNode*);

#endif CALTREE_H