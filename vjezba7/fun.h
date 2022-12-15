#ifndef FUN_H
#define FUN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define END (0)
#define ERROR (-1)
#define MAX_LINE (1024)

struct direktorij;
typedef struct direktorij* Position;
typedef struct direktorij {
	char name[MAX_LINE];
	Position sibling;
	Position child;
	Position parent;
}dir;

void Print(Position, int);
Position Make(Position, Position);
Position ExitDir(Position);
Position GotoDir(Position, char *);
Position Delete(Position);

#endif