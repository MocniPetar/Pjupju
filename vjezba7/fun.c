#define _CRT_SECURE_NO_WARNINGS

#include "fun.h"

int Print(Position p)
{
	int i = 0;

	printf("\nDirectory of %s", p->name);

	p = p->child;

	while (p != NULL) {
		printf("\n\t %s", p->name);
		p = p->sibling;
		i++;
	}

	printf("\n\t Number of %d Dir(s)", i);

	return END;
}

int Make(Position p) {

	Position q = NULL;

	q = (Position)malloc(sizeof(dir));
	q->sibling = NULL;
	q->child = NULL;
	q->parent = p;

	printf("Insert name of new directory: ");
	scanf(" %s", q->name);

	if (NULL == q) {
		printf("\nERROR!!");
		return END;
	}

	else
	{
		if (NULL == p->child)
			p->child = q;

		else
		{
			q->sibling = p->child;
			p->child = q;
		}
	}

	printf("\nYou are in %s directory", p->name);

	return END;
}

Position GotoDir(Position p)
{
	Position temp = NULL;
	temp = p->child;

	char Name[MAX_LINE] = { 0 };

	printf("Insert name of directory you want to go to: ");
	scanf(" %s", Name);

	while (temp != NULL && strcmp(temp->name, Name) != 0)
		temp = temp->sibling;

	if (NULL == temp)
		printf("\nDirectory do not exist!!!");

	else
		return temp;

	return p;
}

Position ExitDir(Position p)
{
	if (NULL == p->parent)
	{
		printf("Nalazimo se u root direktoriju!\nIz njega se ne moze izaci!");
		return p;
	}

	printf("\nYou are back at directory %s", p->parent->name);

	return p->parent;
}