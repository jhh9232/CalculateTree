#include "LinkedListStack.h"

void init(Stack** stack)
{
	(*stack) = NULL;
}
void printstack(Stack* stack)
{
	if (stack == NULL)
	{
		printf("Stack is Empty\n");
	}
	else
	{
		Stack* tmp;
		printf("=-=-=-=\n");
		for (tmp = stack; tmp > 0; tmp = tmp->before)
		{
			printf("   %c\n", tmp->data);
		}
		printf("=-=-=-=\n");
	}
}
char printLast(Stack* stack)
{
	if (stack == NULL || stack->data == NULL)
	{
		return 0;
	}
	else
	{
		return stack->data;
	}
}
void push(Stack** stack, char Data)
{
	if ((*stack) == NULL)
	{
		*stack = (Stack*)malloc(sizeof(Stack));
		(*stack)->data = Data;
		(*stack)->before = NULL;
	}
	else
	{
		Stack* tmp;
		tmp = (Stack*)malloc(sizeof(Stack));
		tmp->before = (*stack);
		tmp->data = Data;
		(*stack) = tmp;
	}
}
int pop(Stack** stack)
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
void destroystack(Stack** stack)
{
	while ((*stack) != NULL)
	{
		pop(stack);
	}
}

// int main() {
// 	Stack *stack;
// 	init(&stack);
// 	printstack(stack);
// 	push(&stack, '-');
// 	push(&stack, '+');
// 	push(&stack, '*');
// 	printf("LAST : %c\n", printLast(stack));
// 	pop(&stack);
// 	printf("LAST : %c\n", printLast(stack));
// 	destroystack(&stack);
// 	printf("LAST : %c\n", printLast(stack));
// 	return 0;
// }