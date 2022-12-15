#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "fun.h"

int main() {
	
	int n = 0;
	
	dir root = {
		.name = "C",
		.sibling=NULL,
		.child=NULL,
		.parent=NULL	
	};
	
	Position ParDir = NULL;
	ParDir = &root;

	while (1) {
		printf("You are in %s directory\n", ParDir->name);
		printf("Insert number of function: ");
		printf("\n1. - md");
		printf("\n2. - cd dir");
		printf("\n3. - cd..");
		printf("\n4. - dir");
		printf("\n5. - exit");
		printf("\nAnswer: ");
		scanf("%d", &n);

		if (n == 1) {
			Position q = NULL;

			q = (Position)malloc(sizeof(dir));
			q->sibling = NULL;
			q->child = NULL;
			q->parent = ParDir;

			printf("Insert name of new directory: ");
			scanf(" %s", q->name);

			ParDir->child=Make(ParDir->child, q);
		}

		else if (n == 2) {
			char Name[MAX_LINE] = { 0 };

			printf("Insert name of directory you want to go to: ");
			scanf(" %s", Name);

			ParDir = GotoDir(ParDir->child,Name);
		}

		else if (n == 3)
			ParDir = ExitDir(ParDir);

		else if (n == 4) {
			int i = 0;
			printf("\nDirectory %s:", ParDir->name);
			Print(ParDir->child, i);
		}

		else if (n == 5) {
			ParDir = Delete(ParDir->child);
			break;
		}

		else
			printf("Wrong input!\n");

		printf("\n");
	}

	return END;
}