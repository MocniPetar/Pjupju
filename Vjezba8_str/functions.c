#define _CRT_SECURE_NO_WARNINGS

#include "functions.h"

Position Insert(Position p, Position q) {

	if (NULL == p)
		return q;

	if (strcmp(p->El, q->El)>0)
		p->Right = Insert(p->Right, q);
	else if (strcmp(p->El, q->El) < 0)
		p->Left = Insert(p->Left, q);

	else {
		printf("\nElement already exist!\nTry again!\n");
		return p;
	}

	return p;
}

void PrintInOrderDecreasing(Position p) { 

	if (NULL == p)
		return;

	PrintInOrderDecreasing(p->Right);
	printf("%s ", p->El);
	PrintInOrderDecreasing(p->Left);
}

void PrintInOrderIncreasing(Position p) { 

	if (NULL == p)
		return;

	PrintInOrderIncreasing(p->Left);
	printf("%s ", p->El);
	PrintInOrderIncreasing(p->Right);
}

void PrintPostOrder(Position p) {

	if (NULL == p)
		return;

	PrintPostOrder(p->Left);
	PrintPostOrder(p->Right);
	printf("%s ", p->El);
}

void PrintPreOrder(Position p) {

	if (NULL == p)
		return;

	printf("%s ", p->El);
	PrintPreOrder(p->Left);
	PrintPreOrder(p->Right);
}

void PrintLevelOrder(Position p) {

	int h = 0, i = 0;

	h = Height(p);

	for (i = 1; i <= h; i++){
		printf("Level %d:", i);
		PrintCurrentLevel(p, i);
		printf("\n\t\t\t\t");
	}
}

int Height(Position p){

	if (p == NULL)
		return 0;

	else {
		int leftheight = 0, rightheight = 0;

		leftheight = Height(p->Left);
		rightheight = Height(p->Right);

		if (leftheight > rightheight)
			return (leftheight + 1);

		else
			return (rightheight + 1);
	}
}

void PrintCurrentLevel(Position p, int level){

	if (p == NULL)
		return;

	if (level == 1) 
		printf(" %s ", p->El);

	else if (level > 1) {
		PrintCurrentLevel(p->Left, level - 1);
		PrintCurrentLevel(p->Right, level - 1);
	}
}
 
Position DeleteElement(Position p, char* a) {

	if (p == NULL) {
		printf("Element do not exist!\nTray again!\n");
		return p;
	}

	if (strcmp(p->El, a) < 0)
		p->Left = DeleteElement(p->Left, a);

	else if (strcmp(p->El, a) > 0)
		p->Right = DeleteElement(p->Right, a);

	else {
		if (p->Left) {
			Position temp = NULL;
			temp = FindMax(p->Left);
			strcpy(p->El, temp->El);
			//p->El = temp->El;
			p->Left = DeleteElement(p->Left, temp->El);
		}

		else if (p->Right) {
			Position temp = NULL;
			temp = FindMin(p->Right);
			strcpy(p->El, temp->El);
			//p->El = temp->El;
			p->Right = DeleteElement(p->Right, temp->El);
		}

		else {
			free(p);
			return NULL;
		}
	}

	return p;
}

Position FindMin(Position p) {

	if (p == NULL)
		return NULL;

	if (NULL == p->Left)
		return p;

	return FindMin(p->Left);
}

Position FindMax(Position p) {

	if (p == NULL)
		return NULL;

	if (NULL == p->Right)
		return p;

	return FindMax(p->Right);
}

Position Find(Position p, char* a) {

	if (NULL == p)
		return NULL;

	if (strcmp(p->El, a) > 0)
		return Find(p->Right, a);
	if (strcmp(p->El, a) < 0)
		return Find(p->Left, a);

	return p;
}

Position DeleteAll(Position p) {

	if (p == NULL)
		return NULL;

	DeleteAll(p->Left);
	DeleteAll(p->Right);

	free(p);

	return NULL;
}