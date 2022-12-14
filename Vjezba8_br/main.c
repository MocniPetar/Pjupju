#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "functions.h"

int main() {

	int a=0, b=0, x=0;
	Position root = NULL;

	while (1) {
		printf("Insert a number of function: ");
		printf("\n1. - Insert new element");
		printf("\n2. - Print tree");
		printf("\n3. - Delete element");
		printf("\n4. - Find Element");
		printf("\n5. - Exit");
		printf("\nAnswer: ");
		scanf("%d", &a);

		if (a == 1) {
			Position q = NULL;

			q = (Position)malloc(sizeof(Tree));

			printf("\nInsert a element in tree: ");
			scanf("%d", &q->El);
			printf("\n");
			q->Left = NULL;
			q->Right = NULL;
			
			root = Insert(root, q);
		}

		else if (a == 2) {
			while (1) {
				printf("\n\tChoose a print method: ");
				printf("\n\t1. - inorder");
				printf("\n\t2. - preorder");
				printf("\n\t3. - postorder");
				printf("\n\t4. - level order");
				printf("\n\t5. - exit");
				printf("\n\tAnswer: ");
				scanf("%d", &b);

				if (b == 1) {
					char mark[MAX_LINE] = { 0 };

					printf("\n\tInsert which method you want to print:");
					printf("\n\t\t - Increasing values");
					printf("\n\t\t - Decreasing values");
					printf("\n\tAnswer: ");
					scanf(" %s", mark);

					printf("\n\tRoot: %d\n", root->El);

					if (strcmp(mark, "Increasing values") == 0 || strcmp(mark, "Increasing") == 0 || strcmp(mark, "increasing") == 0) {
							printf("\n\tInorder increasing expression: ");
							PrintInOrderIncreasing(root);
					}

					else if(strcmp(mark, "Decreasing values") == 0 || strcmp(mark, "Decreasing") == 0 || strcmp(mark, "decreasing") == 0) {
						printf("\n\tInorder decreasing expression: ");
						PrintInOrderDecreasing(root);
					}

					else {
						printf("\n\tWrong input!\n\n");
					}
					printf("\n\n");
				}

				else if (b == 2) {
					printf("\n\tRoot: %d\n", root->El);
					printf("\n\tPreorder expression: ");
					PrintPreOrder(root);
					printf("\n\n");
				}

				else if (b == 3) {
					printf("\n\tRoot: %d\n", root->El);
					printf("\n\tPostorder expression: ");
					PrintPostOrder(root);
					printf("\n\n");
				}

				else if(b==4){
					printf("\n\tRoot: %d\n", root->El);
					printf("\n\tLevel order expression: ");
					PrintLevelOrder(root);
					printf("\n\n");
				}

				else if (b == 5)
					break;

				else
					printf("\n\tWrong input!\n\n");
			}
		}

		else if (a == 3) {
			printf("\nEnter element you want to delete: ");
			scanf("%d", &x);
			root = DeleteElement(root, x);		
		}

		else if (a == 4) {
			Position temp = NULL;

			printf("\nEnter element you want to find: ");
			scanf("%d", &x);

			temp = Find(root, x);

			if (temp == NULL)
				printf("Element do not exist!\nTray again!\n");
			else
				printf("\nElement %d exist in tree\n", temp->El);
		}

		else if (a == 5) {
			root = DeleteAll(root);
			break;
		}

		else
			printf("\nWrong input!\n\n");

		printf("\n");
	}

	return END;
}