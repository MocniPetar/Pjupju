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

Position ReadFromFile(char *);
int PrintList(Position);
int Add(Position, char *);

int main() {

	char filename[MAX_LINE] = { 0 };
	int i;

	st Head = {
		.El = 0,
		.next=NULL
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

Position ReadFromFile(char * filename) {

	FILE* fp=NULL;

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

int Add(Position P, char *buffer) {

	if (P == NULL)
		return ERROR;

	Position q = NULL;
	Position temp = NULL;

	char* p = NULL;
	char mark[MAX_LINE] = { 0 };
	int n = 0;


	p = buffer;

	while (strlen(p) > 0) {

		q = (Position)malloc(sizeof(st));

		if (sscanf(p, "%f %n", &q->El, &n) <= 0)
			sscanf(p, "%s %n", mark, &n);

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