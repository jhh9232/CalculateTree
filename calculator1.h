#ifndef CALCULATOR1_H
#define CALCULATOR1_H

#include "Caltree.h"

typedef enum
{
	LEFT_PARENTHESIS = '(', RIGHT_PARENTHESIS = ')',
	PLUS = '+', MINUS = '-',
	MULTIPLY = '*', DIVIDE = '/',
	SPACE = ' ', OPERAND
} SYMBOL;

int IsNumber(char);
void Addmodification(char**, char);
void EraseSpace(char*);
char* inorder_to_postorder(char*);

#endif CALCULATOR1_H