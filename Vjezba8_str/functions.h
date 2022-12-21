#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define END (0)
#define MAX_LINE (1024)

struct Tree;
typedef struct Tree* Position;
typedef struct Tree {
	char El[MAX_LINE];
	Position Left;
	Position Right;
}Tree;

Position Insert(Position, Position);
void PrintInOrderIncreasing(Position);
void PrintInOrderDecreasing(Position);
void PrintPreOrder(Position);
void PrintPostOrder(Position);
void PrintOrderLevel(Position);
void PrintLevelOrder(Position);
int Height(Position);
void PrintCurrentLevel(Position, int);
Position FindMin(Position);
Position FindMax(Position);
Position DeleteElement(Position, char*);
Position Find(Position, char*);
Position DeleteAll(Position);

#endif