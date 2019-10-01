#include "Caltree.h"

int IsOperator(char* Data)
{
	if (!strcmp(Data, "+") || !strcmp(Data, "-") || !strcmp(Data, "*") || !strcmp(Data, "/"))
	{
		return true;
	}
	else
	{
		return false;
	}
}
int Operator(char Data)
{
	switch (Data)
	{
	case '+':
	case '-':
	case '*':
	case '/':
		return true;
	default:
		return false;
	}
}
void Postinit(PostStack** stack)
{
	(*stack) = NULL;
}
void Postpush(PostStack** stack, char Operator, int Value)
{
	if ((*stack) == NULL)
	{
		*stack = (PostStack*)malloc(sizeof(PostStack));
		(*stack)->before = NULL;
		if (Operator == NULL)
		{
			(*stack)->Operator = NULL;
			(*stack)->Value = Value;
		}
		else
		{
			(*stack)->Operator = Operator;
			(*stack)->Value = NULL;
		}
	}
	else
	{
		PostStack* tmp;
		tmp = (PostStack*)malloc(sizeof(PostStack));
		tmp->before = (*stack);
		if (Operator == NULL)
		{
			tmp->Operator = NULL;
			tmp->Value = Value;
		}
		else
		{
			tmp->Operator = Operator;
			tmp->Value = NULL;
		}
		(*stack) = tmp;
	}
}
int Postpop(PostStack** stack)
{
	if ((*stack) == NULL)
	{
		return false;
	}
	else
	{
		Stack* tmp;
		tmp = (*stack)->before;
		free(*stack);
		(*stack) = tmp;
		return true;
	}
}
void Postdestroystack(PostStack** stack)
{
	while ((*stack) != NULL)
	{
		Postpop(&(*stack));
	}
}
void Postprintstack(PostStack* stack)
{
	if (stack->before != NULL)
	{
		Postprintstack(stack->before);
	}
	if (stack->Operator == NULL)
	{
		printf("%d ", stack->Value);
	}
	else
	{
		printf("%c ", stack->Operator);
	}
}

TreeNode* CreateTree(TreeNode** _TreeNode)
{
	(*_TreeNode) = (TreeNode*)malloc(sizeof(TreeNode));
	(*_TreeNode)->LeftNode = NULL;
	(*_TreeNode)->RightNode = NULL;
	(*_TreeNode)->Data = NULL;
	(*_TreeNode)->Value = NULL;
	return *_TreeNode;
}

void AddTree(PostStack** stack, TreeNode** _TreeNode)
{
	int Token = 0;
	if ((*_TreeNode) == NULL)
	{
		(*_TreeNode) = CreateTree(&(*_TreeNode));
	}
	Token = Operator((*stack)->Operator);
	switch (Token)
	{
	case true:
		(*_TreeNode)->Data = (*stack)->Operator;
		//printf("%c ",(*stack)->Operator);
		Postpop(&(*stack));
		AddTree(&(*stack), &(*_TreeNode)->RightNode);
		AddTree(&(*stack), &(*_TreeNode)->LeftNode);
		break;
	default:
		if ((*stack)->before == NULL)
		{
			(*_TreeNode)->Value = (*stack)->Value;
			//printf("%d ", (*stack)->Value);
		}
		else
		{
			(*_TreeNode)->Value = (*stack)->Value;
			//printf("%d ", (*stack)->Value);
			Postpop(&(*stack));
		}
		break;
	}
}

void TreePrint(TreeNode* Node, int Depth)
{
	for (int i = 0; i < Depth; i++)
	{
		printf(" ");
	}
	if (Node->Data != NULL)
	{
		printf("%c\n", Node->Data);
	}
	else
	{
		printf("%d\n", Node->Value);
	}
	if (Node->LeftNode != NULL)
	{
		TreePrint(Node->LeftNode, Depth + 1);
	}
	if (Node->RightNode != NULL)
	{
		TreePrint(Node->RightNode, Depth + 1);
	}
}

int Evaluate(TreeNode* Node)
{
	int res = 0;
	if (Node == NULL)
	{
		return 0;
	}
	int Flag = Operator(Node->Data);    //연산자인지 구분하는 변수
	switch (Flag)
	{
	case true:  //연산자이면
		Evaluate(Node->LeftNode);   //왼쪽노드 순회
		Evaluate(Node->RightNode);  //오른쪽노드 순회

		switch (Node->Data)
		{
		case '+':
			res = Node->LeftNode->Value + Node->RightNode->Value;
			Node->Value = res;
			break;
		case '-':
			res = Node->LeftNode->Value - Node->RightNode->Value;
			Node->Value = res;
			break;
		case '*':
			res = Node->LeftNode->Value * Node->RightNode->Value;
			Node->Value = res;
			break;
		case '/':
			res = Node->LeftNode->Value / Node->RightNode->Value;
			Node->Value = res;
			break;
		default:
			return 0;
		}
	}
	return res;
}

void DestroyTree(TreeNode* Node)
{
	if (Node == NULL) return;
	DestroyTree(Node->LeftNode);
	DestroyTree(Node->RightNode);
	free(Node);
}