#include "calculator1.h"

int IsNumber(char Cipher)
{
	switch (Cipher) {
	case PLUS:
	case MINUS:
		return 2;
	case MULTIPLY:
	case DIVIDE:
		return 3;
	case LEFT_PARENTHESIS:
		return 4;
	case RIGHT_PARENTHESIS:
		return 5;
	default:
		if (Cipher >= 48 && Cipher <= 57)
		{
			return true;
		}
		return false;
	}
}

void Addmodification(char** calculation, char chr)
{
	if (strlen(*calculation) == 0)
	{
		sprintf(*calculation, "%c", chr);
	}
	else if (IsNumber(chr) == 1)
	{
		sprintf(*calculation, "%s%c", *calculation, chr);
	}
	else
	{
		sprintf(*calculation, "%s %c", *calculation, chr);
	}
}

void EraseSpace(char* ap_string)
{
	char* p_dest = ap_string;
	while (*ap_string != 0) {
		if (*ap_string != ' ') {
			if (p_dest != ap_string) *p_dest = *ap_string;
			p_dest++;
		}
		ap_string++;
	}
	*p_dest = 0;
}

char* inorder_to_postorder(char* argcal)
{
	char* inordercal, * postordercal;
	int lenspace = strlen(argcal);
	//printf("%d\n", lenspace);
	inordercal = (char*)malloc(sizeof(char) * (lenspace + 10));
	postordercal = (char*)malloc(sizeof(char) * (lenspace + 1000));
	postordercal[0] = 0;
	strcpy(inordercal, argcal);
	EraseSpace(inordercal);


	printf("%s\n", inordercal);

	int i = 0;
	Stack* stack;
	init(&stack);
	for (i = 0; i < strlen(inordercal); i++)
	{
		//printf("char : %c, ", inordercal[i]);
		if (IsNumber(inordercal[i]) == true) //숫자일떄
		{
			Addmodification(&postordercal, inordercal[i]);
		}
		else if (IsNumber(inordercal[i]) == 2)   //+ - 일떄
		{
			if (printLast(stack) == 0)
			{
				push(&stack, inordercal[i]);
				sprintf(postordercal, "%s ", postordercal);
			}
			else if (IsNumber(printLast(stack)) == 2)    //마지막 스택 값이 + - 일 때
			{
				Addmodification(&postordercal, printLast(stack));
				if(IsNumber(inordercal[i+1]) == true) sprintf(postordercal, "%s ", postordercal);
				pop(&stack);
				push(&stack, inordercal[i]);
			}
			else if (IsNumber(printLast(stack)) == 3)    //마지막 스택 값이 * / 일때
			{
				Addmodification(&postordercal, printLast(stack));
				pop(&stack);
				while (printLast(stack) != 0 && printLast(stack) != LEFT_PARENTHESIS)
				{
					Addmodification(&postordercal, printLast(stack));
					pop(&stack);
				}
				push(&stack, inordercal[i]);
				sprintf(postordercal, "%s ", postordercal);
			}
			else // 마지막 스택 값이 ( 일떄
			{
				push(&stack, inordercal[i]);
				sprintf(postordercal, "%s ", postordercal);
			}

		}
		else if (IsNumber(inordercal[i]) == 3)   // * / 일 때
		{
			if (printLast(stack) == 0)
			{
				push(&stack, inordercal[i]);
				sprintf(postordercal, "%s ", postordercal);
			}
			else if (IsNumber(printLast(stack)) == 2) //마지막 스택 값이 + - 일 때
			{
				push(&stack, inordercal[i]);
				sprintf(postordercal, "%s ", postordercal);
			}
			else if (IsNumber(printLast(stack)) == 3)    //마지막 스택 값이 * / 일 때
			{
				Addmodification(&postordercal, printLast(stack));
				if (IsNumber(inordercal[i + 1]) == true) sprintf(postordercal, "%s ", postordercal);
				pop(&stack);
				push(&stack, inordercal[i]);
			}
			else // 마지막 스택 값이 ( 일떄
			{
				push(&stack, inordercal[i]);
				sprintf(postordercal, "%s ", postordercal);
			}

		}
		else if (IsNumber(inordercal[i]) == 4)   //( 일떄
		{
			push(&stack, inordercal[i]);
		}
		else if (IsNumber(inordercal[i]) == 5)   //) 일때
		{
			while (printLast(stack) != LEFT_PARENTHESIS)
			{
				Addmodification(&postordercal, printLast(stack));
				pop(&stack);
			}
			pop(&stack);
			//printstack(stack);
			//스택의 마지막 연산자가 * / 이면 계속 빼낸다.
			while (printLast(stack) == MULTIPLY || printLast(stack) == DIVIDE)
			{
				Addmodification(&postordercal, printLast(stack));
				pop(&stack);
			}
			//다음 연산자가 + - 이면 스택의 연산자를 전부 뺀다.
			if (inordercal[i + 1] == MINUS || inordercal[i + 1] == PLUS)
			{
				while (stack != NULL && printLast(stack) != LEFT_PARENTHESIS)
				{
					printf("%c ", printLast(stack));
					Addmodification(&postordercal, printLast(stack));
					pop(&stack);
				}
			}
		}
		/*if (strlen(postordercal) > 0)
		{
			printf("LEN : %d\n", strlen(postordercal));
			printf("|%s|\n", postordercal);
			printstack(stack);
		}*/
	}
	while (printLast(stack) != 0)
	{
		Addmodification(&postordercal, printLast(stack));
		pop(&stack);
	}
	destroystack(&stack);
	free(inordercal);
	return postordercal;
}

int main(int argc, char* argv[])
{
	//char *p = "2*(12+14)+3*2";
	//char* p = "((((1+2+3)*(3-1-2-4)+98765432/2-(12345678*(37-33)/2/2))/2/7-1)-100)/100+(2*3+2+1)-3";
	char* p;
	p = (char*)malloc(sizeof(char) * 1000);
	printf("calculation : ");
	scanf("%[^\n]", p);
	char* postcal = inorder_to_postorder(p);
	printf("|%s|\n", postcal);

	char* postsplit = strtok(postcal, " ");
	PostStack* stackpost;
	Postinit(&stackpost);
	while (postsplit != NULL)
	{
		//printf("%s\n", postsplit);
		if (IsOperator(postsplit))
		{
			Postpush(&stackpost, postsplit[0], NULL);
		}
		else
		{
			Postpush(&stackpost, NULL, atoi(postsplit));
		}
		postsplit = strtok(NULL, " ");
	}
	Postprintstack(stackpost);
	printf("\n");
	printf("=======================\n");
	TreeNode* tree = NULL;
	//printf("=-=-=-=-=-=-=-=-=-=-=-=\n");
	AddTree(&stackpost, &tree);
	printf("=======================\n");
	TreePrint(tree, 0);
	printf("=======================\n");
	int res = Evaluate(tree);
	printf("Result Answer : %d\n", res);
	Postdestroystack(&stackpost);
	DestroyTree(tree);
	free(postcal);
	free(p);
	int a;
	scanf("%d", &a);
	return 0;
}


//gcc calculator1.c Caltree.c LinkedListStack.c -o calculator1.exe && ./calculator1.exe

//2 * (1 + 4) + 3 * ((1 + 2) * 7) + 10
//2 1 4 + * 3 1 2 + 7 * * + 10 +
//2*(12+14)+3*2
//100 - 2 * ( 4 - 7 ) * 8 + 3 * 4
//100 2 4 7 - * 8 * - 3 4 * +