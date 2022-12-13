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
		printf("Insert number of function: ");
		printf("\n1. - md");
		printf("\n2. - cd dir");
		printf("\n3. - cd..");
		printf("\n4. - dir");
		printf("\n5. - exit");
		printf("\nAnswer: ");
		scanf("%d", &n);

		if (n == 1)
			Make(ParDir);
		else if (n == 2)
			ParDir = GotoDir(ParDir);
		else if (n == 3)
			ParDir = ExitDir(ParDir);
		else if (n == 4)
			Print(ParDir);
		else if (n == 5)
			break;
			
		else
			printf("Wrong input!\n");

		printf("\n");
	}

	return END;
}