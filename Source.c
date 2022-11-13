#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define END (0)
#define ERROR (-1)
#define MAX_LINE (1024)

static int count = 0;

struct Stog;
typedef struct Stog* Position;

typedef struct Stog {
	float El;
	Position next;
}st;

Position ReadFromFile(char*);
int PrintList(Position);
int Add(Position, char*);
Position PrevElement(Position);
int deleteElement(Position);
Position findPosition(Position);

int main() {

	char filename[MAX_LINE] = { 0 };
	int i;

	st Head = {
		.El = 0,
		.next = NULL
	};

	printf("Insert filename: ");
	scanf(" %s", filename);

	Position List = NULL;

	List = ReadFromFile(filename);

	if (List == NULL) {
		printf("\nThe list is empty!\n");
		return END;
	}
	for (i = 0; i < count; i++) {
		PrintList(&List[i]);
	}

	return END;
}

Position ReadFromFile(char* filename) {

	FILE* fp = NULL;

	char buffer[MAX_LINE] = { 0 };

	int n = 0;

	Position List = NULL;
	Position q = NULL;

	fp = fopen(filename, "r");

	if (fp == NULL) {

		printf("Warning!");
		return NULL;
	}

	while (1) {
		if (fgets(buffer, MAX_LINE, fp) == NULL)
			break;
		count++;
	}


	List = (Position)malloc(sizeof(st) * count);

	rewind(fp);

	while (1) {
		if (fgets(buffer, MAX_LINE, fp) == NULL)
			break;
		st Head = {
			.El = 0,
			.next = NULL
		};
		if (Add(&Head, buffer) < 0) {
			printf("Error!!\n");
			return NULL;
		}
		List[n] = Head;
		n++;
	}

	fclose(fp);
	return List;
}

int Add(Position P, char* buffer) {

	if (P == NULL)
		return ERROR;

	Position q = NULL;
	Position temp = NULL;
	Position temp1 = NULL;
	Position temp2 = NULL;

	char* p = NULL;
	char mark[MAX_LINE] = { 0 };
	char buff[MAX_LINE] = { 0 };
	int n = 0;
	float result = 0;

	p = buffer;

	while (strlen(p) > 0) {

		q = (Position)malloc(sizeof(st));

		if (sscanf(p, "%f %n", &q->El, &n) <= 0) {

			sscanf(p, "%s %n", mark, &n);

			if (strcmp(mark, "+") == 0) {
				temp1 = PrevElement(P);
				temp2 = temp1->next;
				result = (temp1->El) + (temp2->El);
				deleteElement(P);
				temp = findPosition(P);
				deleteElement(temp);
			}

			if (strcmp(mark, "-") == 0) {
				temp1 = PrevElement(P);
				temp2 = temp1->next;
				result = (temp1->El) - (temp2->El);
				deleteElement(P);
			}

			if (strcmp(mark, "*") == 0) {
				temp1 = PrevElement(P);
				temp2 = temp1->next;
				result = (temp1->El) * (temp2->El);
				deleteElement(P);
			}

			if (strcmp(mark, "/") == 0) {
				temp1 = PrevElement(P);
				temp2 = temp1->next;
				result = (temp1->El) / (temp2->El);
				deleteElement(P);
			}

			q->El = result;
		}

		else
			sscanf(p, "%f %n", &q->El, &n);

		while (P->next != NULL)
			P = P->next;

		temp = P;

		q->next = P->next;
		P->next = q;

		p += n;
	}

	return END;
}
int deleteElement(Position p) {

	Position prev = NULL;
	Position curr = NULL;

	prev = PrevElement(p);

	if (prev == NULL)
		return ERROR;

	curr = prev->next;
	prev->next = curr->next;

	free(curr);

	return END;
}

int PrintList(Position P) {


	if (P == NULL) {
		printf("The list is empty!!\n");
		return ERROR;
	}

	while (P->next != NULL) {

		printf("%f ", P->next->El);
		P = P->next;
	}

	printf("\n");

	return END;
}

Position PrevElement(Position P) {

	Position prev = NULL, curr = NULL;

	prev = P;
	curr = prev->next;

	while (curr == NULL) {
		
		prev = curr;
		curr = prev->next;
		
	}

	return prev;
}

Position findPosition( Position p) {

	while (p->next != NULL)
		p = p->next;

	if (p == NULL) {
		return NULL;
	}

	return p;
}