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
	PostStack* temp;
	Postinit(&temp);
	while (stack)
	{
		Postpush(&temp, stack->Operator, stack->Value);
		stack = stack->before;
	}
	while (temp)
	{
		if (!temp->Operator)
			printf("%d ", temp->Value);
		else
			printf("%c ", temp->Operator);
		Postpop(&temp);
	}
	Postdestroystack(&temp);

	/*if (stack->before != NULL)
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
	}*/
}

void InitTreeStack(TreeStack** stack)
{
	(*stack) = NULL;
}
void PushTreeStack(TreeStack** stack, TreeNode* node)
{
	if ((*stack) == NULL)
	{
		*stack = (TreeStack*)malloc(sizeof(TreeStack));
		(*stack)->before = NULL;
		(*stack)->Node = node;
		(*stack)->depth = 0;
	}
	else
	{
		TreeStack* tmp;
		tmp = (TreeStack*)malloc(sizeof(TreeStack));
		tmp->before = (*stack);
		tmp->Node = node;
		tmp->depth = 0;
		(*stack) = tmp;
	}
}
void PushTreeStackDepth(TreeStack** stack, TreeNode* node, int depth)
{
	if ((*stack) == NULL)
	{
		*stack = (TreeStack*)malloc(sizeof(TreeStack));
		(*stack)->before = NULL;
		(*stack)->Node = node;
		(*stack)->depth = depth;
	}
	else
	{
		TreeStack* tmp;
		tmp = (TreeStack*)malloc(sizeof(TreeStack));
		tmp->before = (*stack);
		tmp->Node = node;
		tmp->depth = depth;
		(*stack) = tmp;
	}
}
int PopTreeStack(TreeStack** stack)
{
	if ((*stack) == NULL)
	{
		return false;
	}
	else
	{
		TreeStack* tmp;
		tmp = (*stack)->before;
		/*if ((*stack)->Node != NULL)
		{
			printf("Node??\n");
			printf("%d\n", (*stack)->Node->Value);
			free((*stack)->Node);
			(*stack)->Node = NULL;
		}*/
		free(*stack);
		(*stack) = tmp;
		return true;
	}
}
void DestroyTreeStack(TreeStack** stack)
{
	while ((*stack) != NULL)
	{
		PopTreeStack(stack);
	}
}
void PrintTreeStack(TreeStack* stack)
{
	if (stack == NULL)
	{
		printf("Stack is EMPTY\n");
		return;
	}
	/*if (stack->before != NULL)
	{
		PrintTreeStack(stack->before);
	}
	if (!stack->Node->Data)
		printf("%d ", stack->Node->Value);
	else
		printf("%c ", stack->Node->Data);*/
	TreeStack* trees;
	InitTreeStack(&trees);
	while (stack)
	{
		PushTreeStack(&trees, stack->Node);
		stack = stack->before;
	}
	while (trees)
	{
		if (!trees->Node->Data)
			printf("%d ", trees->Node->Value);
		else
			printf("%c ", trees->Node->Data);
		trees = trees->before;
	}
	DestroyTreeStack(&trees);
	PrintTreeStack(trees);
}
int GetTreeStackSize(TreeStack* stack)
{
	int cnt = 0;
	while (stack)
	{
		stack = stack->before;
		cnt++;
	}
	return cnt;
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

void AddTree(PostStack** stack, TreeNode** tree)
{
	int Token = 0;
	//if ((*_TreeNode) == NULL)
	//{
	//	(*_TreeNode) = CreateTree(&(*_TreeNode));
	//}
	//Token = Operator((*stack)->Operator);
	//switch (Token)
	//{
	//case true:
	//	(*_TreeNode)->Data = (*stack)->Operator;
	//	//printf("%c ",(*stack)->Operator);
	//	Postpop(&(*stack));
	//	AddTree(&(*stack), &(*_TreeNode)->RightNode);
	//	AddTree(&(*stack), &(*_TreeNode)->LeftNode);
	//	break;
	//default:
	//	if ((*stack)->before == NULL)
	//	{
	//		(*_TreeNode)->Value = (*stack)->Value;
	//		//printf("%d ", (*stack)->Value);
	//	}
	//	else
	//	{
	//		(*_TreeNode)->Value = (*stack)->Value;
	//		printf("%d\n", (*_TreeNode)->Value);
	//		//printf("%d ", (*stack)->Value);
	//		Postpop(&(*stack));
	//	}
	//	break;
	//}
	//TreeNode* temp = &_TreeNode;
	TreeNode* _TreeNode;
	TreeStack* treestack;
	InitTreeStack(&treestack);
	printf("Tree : ");
	while ((*stack))
	{
		Token = Operator((*stack)->Operator);
		if (Token)	//연산자이면
		{
			CreateTree(&_TreeNode);
			_TreeNode->Data = (*stack)->Operator;
			printf("%c ", _TreeNode->Data);
			Postpop(&(*stack));
			PushTreeStack(&treestack, _TreeNode);
		}
		else		//숫자이면
		{
			if (!treestack->Node->RightNode)
			{
				treestack->Node->RightNode = CreateTree(&treestack->Node->RightNode);
				treestack->Node->RightNode->Value = (*stack)->Value;
				Postpop(&(*stack));
				printf("%d ", treestack->Node->RightNode->Value);
			}
			else
			{
				treestack->Node->LeftNode = CreateTree(&treestack->Node->LeftNode);
				treestack->Node->LeftNode->Value = (*stack)->Value;
				Postpop(&(*stack));
				printf("%d ", treestack->Node->LeftNode->Value);
			}
		}
		while (treestack->Node->RightNode && treestack->Node->LeftNode && treestack->before)
		{
			TreeNode* temp = treestack->Node;
			if (!treestack->before->Node->RightNode)
			{
				treestack->before->Node->RightNode = temp;
			}
			else if (!treestack->before->Node->LeftNode)
			{
				treestack->before->Node->LeftNode = temp;
			}
			PopTreeStack(&treestack);
		}
	}
	printf("\n");
	(*tree) = treestack->Node;
	DestroyTreeStack(&treestack);
	PrintTreeStack(treestack);
}

void TreePrint(TreeNode* Node, int Depth)
{
	/*if (Node == NULL)
	{
		printf("Tree is EMPTY\n");
		return;
	}
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
	}*/
	if (!Node)
	{
		printf("Tree is EMPTY\n");
		return;
	}
	TreeStack* treestack;
	InitTreeStack(&treestack);
	PushTreeStackDepth(&treestack, Node, 0);
	int depth = 0;
	while (GetTreeStackSize(treestack) > 0)
	{
		TreeNode* current = treestack->Node;
		depth = treestack->depth;
		PopTreeStack(&treestack);
		printspace(depth);
		if (current->Data)
			printf("%c\n", current->Data);
		else
			printf("%d\n", current->Value);
		TreeNode* temp = current->RightNode;
		if (temp)
		{
			PushTreeStackDepth(&treestack, temp, depth+1);
		}
		temp = current->LeftNode;
		if (temp)
		{
			PushTreeStackDepth(&treestack, temp, depth+1);
		}
	}
	printf("\n");
	DestroyTreeStack(&treestack);
	PrintTreeStack(treestack);
}

void printspace(int depth)
{
	for (int i = 0; i < depth; i++)
	{
		printf(" ");
	}
	printf(">");
}

//void iterativeInroder(TreeNode* Node)
//{
//	if (!Node)
//		return;
//	TreeStack* treestack;
//	InitTreeStack(&treestack);
//	TreeNode* current = Node;
//	while (true)
//	{
//		while (current)
//		{
//			PushTreeStack(&treestack, current);
//			current = current->LeftNode;
//		}
//		int size = GetTreeStackSize(treestack);
//		if (size)
//		{
//			current = treestack->Node;
//			PopTreeStack(&treestack);
//		}
//		if (!current)
//			break;
//		if (current->Data)
//			printf("%c \n", current->Data);
//		else
//			printf("%d \n", current->Value);
//		current = current->RightNode;
//	}
//	printf("\n");
//}

int Evaluate(TreeNode* Node)
{
	int res = 0;
	if (Node == NULL)
	{
		return 0;
	}
	//int Flag = Operator(Node->Data);    //연산자인지 구분하는 변수
	//switch (Flag)
	//{
	//case true:  //연산자이면
	//	Evaluate(Node->LeftNode);   //왼쪽노드 순회
	//	Evaluate(Node->RightNode);  //오른쪽노드 순회

	//	switch (Node->Data)
	//	{
	//	case '+':
	//		res = Node->LeftNode->Value + Node->RightNode->Value;
	//		Node->Value = res;
	//		break;
	//	case '-':
	//		res = Node->LeftNode->Value - Node->RightNode->Value;
	//		Node->Value = res;
	//		break;
	//	case '*':
	//		res = Node->LeftNode->Value * Node->RightNode->Value;
	//		Node->Value = res;
	//		break;
	//	case '/':
	//		res = Node->LeftNode->Value / Node->RightNode->Value;
	//		Node->Value = res;
	//		break;
	//	default:
	//		return 0;
	//	}
	//}
	TreeStack* treestack;
	InitTreeStack(&treestack);
	PushTreeStack(&treestack, Node);
	while (true)
	{
		if (treestack->Node->LeftNode->Data && treestack->Node->LeftNode->Value == NULL)
		{
			PushTreeStack(&treestack, treestack->Node->LeftNode);
		}
		else if (treestack->Node->RightNode->Data && treestack->Node->RightNode->Value == NULL)
		{
			PushTreeStack(&treestack, treestack->Node->RightNode);
		}
		else
		{
			switch (treestack->Node->Data)
			{
			case '+':
				res = treestack->Node->LeftNode->Value + treestack->Node->RightNode->Value;
				treestack->Node->Value = res;
				break;
			case '-':
				res = treestack->Node->LeftNode->Value - treestack->Node->RightNode->Value;
				treestack->Node->Value = res;
				break;
			case '*':
				res = treestack->Node->LeftNode->Value * treestack->Node->RightNode->Value;
				treestack->Node->Value = res;
				break;
			case '/':
				res = Node->LeftNode->Value / Node->RightNode->Value;
				treestack->Node->Value = res;
				break;
			default:
				return 0;
			}
			if (!treestack->before)	//만약 treestack의 before값이 없으면
			{
				int res = treestack->Node->Value;
				DestroyTreeStack(&treestack);
				PrintTreeStack(treestack);
				return res;
			}
			//TreeNode* _TreeNode = treestack->Node;
			////스택 이전 Node의 LeftNode에 Value값이 없다면 계산된 노드를 왼쪽에 넣기
			//else if (treestack->before->Node->LeftNode->Value == NULL)
			//{
			//	treestack->before->Node->LeftNode = _TreeNode;
			//}//아니고 오른쪽의 Value값이 없다면 계산된 노드를 오른쪽에 넣기
			//else if (treestack->before->Node->RightNode->Value == NULL)
			//{
			//	treestack->before->Node->RightNode = _TreeNode;
			//}
			PopTreeStack(&treestack);
		}
	}


	return res;
}

void DestroyTree(TreeNode* root)
{
	/*if (root == NULL) return;
	DestroyTree(root->LeftNode);
	DestroyTree(root->RightNode);
	free(root);*/

	if (!root)
		return;
	TreeStack* treestack;
	InitTreeStack(&treestack);
	PushTreeStack(&treestack, root);
	TreeNode* prev = NULL;
	while (treestack != NULL)
	{
		TreeNode* current = treestack->Node;
		if (!prev || prev->LeftNode == current || prev->RightNode == current)
		{
			if (current->LeftNode)
			{
				PushTreeStack(&treestack, current->LeftNode);
			}
			else if (current->RightNode)
			{
				PushTreeStack(&treestack, current->RightNode);
			}
		}
		else if (current->LeftNode == prev)
		{
			if (current->RightNode)
			{
				PushTreeStack(&treestack, current->RightNode);
			}
		}
		else
		{
			free(current);
			PopTreeStack(&treestack);
		}
		prev = current;
	}
	TreePrint(treestack, 0);
	DestroyTreeStack(&treestack);
	PrintTreeStack(treestack);
}