#ifndef LINKEDLIST_STACK_H
#define LINKEDLIST_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY 0
#define true 1
#define false 0

typedef struct node {
	char data;
	struct stack* before;
}Stack;

void init(Stack**);
void printstack(Stack*);
char printLast(Stack*);
void push(Stack**, char);
int pop(Stack**);
void destroystack(Stack**);

#endif LINKEDLIST_STACK_H