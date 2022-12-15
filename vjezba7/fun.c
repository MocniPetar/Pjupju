#define _CRT_SECURE_NO_WARNINGS

#include "fun.h"

void Print(Position p, int i) {

	if (NULL == p) {
		printf("\n\t Number of %d Dir(s)\n", i);
		return;
	}

	i++;

	printf("\n\t %s", p->name);

	Print(p->sibling, i);
}

Position Make(Position p, Position q) {

	if (NULL == q) {
		printf("\nERROR!!\n");
		return NULL;
	}

	if (NULL == p)
		return q;

	if (strcmp(p->name,q->name)>0) {
		q->sibling = p;
		return q;
	}

	if (strcmp(p->name, q->name) == 0) {
		printf("\nThe directory already exist!\n");
		return p;
	}

	p->sibling = Make(p->sibling, q);		

	return p;
}

Position GotoDir(Position p, char* Name) {

	if (NULL == p->child && strcmp(Name, p->name)==0)
		return p;

	if (strcmp(Name, p->sibling->name) != 0) {
		printf("\nThe directory do not exist");
		return p->parent;
	}

	p = GotoDir(p->sibling,Name);

	return p;
}

Position ExitDir(Position p) {

	if (NULL == p->parent){
		printf("\nYou are in C directory!");
		return p;
	}

	printf("\nYou are back at directory %s\n", p->parent->name);

	return p->parent;
}

Position Delete(Position p) {

	if (NULL == p)
		return NULL;

	Delete(p->sibling);
	Delete(p->child);

	free(p);

	return NULL;
}