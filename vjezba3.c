#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define END_OF_PROGRAM (0)
#define MAX_LINE (256)
#define ERROR (-1)

struct person;
typedef struct person* Position;

typedef struct person {
	char firstname[MAX_LINE];
	char lastname[MAX_LINE];
	int birthyear;
	Position next;
}Person;

int AddPerson(Position);
int InsertData(Position);
int PrintList(Position);
int InsertInTheEnd(Position);
int FindPersonByLastname(Position);
int DeletePerson(Position);
Position FindPrevious(Position, char *);
int AddAfter(Position);
Position Find(Position, char *);
int AddBefore(Position);
Position FindBefore(Position, char *);
void Sort(Position);
int WriteToFile(Position);
int ReadFromFile(Position);
void DeleteFromBeginning(Position);


int main() {

	int NumofFunc;

	Person head = {
		.firstname = {0},
		.lastname = {0},
		.birthyear = 0,
		.next = NULL
	};

	while(1){

	printf("\nPlease insert a number of function you want to start: ");
	printf("\n1. Insert a person");
	printf("\n2. Print list");
	printf("\n3. Add a person to the end of list");
	printf("\n4. Find person by his lastname");
	printf("\n5. Delete person from the list");
	printf("\n6. Add person after an another person");
	printf("\n7. Add person before an another person");
	printf("\n8. Sort list by lastnames");
	printf("\n9. Write in file");
	printf("\n10. Read from file");
	printf("\n11. End program");
	printf("\nAnswer: ");
	scanf("%d", &NumofFunc);

	

	if (NumofFunc == 1)
		AddPerson(&head);

	else if (NumofFunc == 2)
		PrintList(&head);

	else if (NumofFunc == 3)
		InsertInTheEnd(&head);

	else if (NumofFunc == 4)
		FindPersonByLastname(&head);

	else if (NumofFunc == 5)
		DeletePerson(&head);

	else if (NumofFunc == 6)
		AddAfter(&head);

	else if (NumofFunc == 7)
		AddBefore(&head);

	else if (NumofFunc == 8)
		Sort(&head);

	else if (NumofFunc == 9)
		WriteToFile(&head);

	else if (NumofFunc == 10)
		ReadFromFile(&head);

	else if (NumofFunc == 11) {

		DeleteFromBeginning(&head);
		printf("Memory is clean!");
		break;
	}

	else
		printf("\nWrong input!\n");

	printf("\n");

	}

	return END_OF_PROGRAM;
}

int InsertData(Position P) {

	printf("\nEnter the person firstname, lastname and birthyear:  ");
	scanf(" %s %s %d", P->firstname, P->lastname, &P->birthyear);

	return END_OF_PROGRAM;
}

int AddPerson(Position P){

	Position q = NULL;

	q = (Position)malloc(sizeof(struct person));

	if (q == NULL)
		return ERROR;

	InsertData(q);

	q->next = P->next;
	P->next = q;

	return END_OF_PROGRAM;
}

int PrintList(Position P) {

	if (P->next == NULL)
		printf("The list is empty!");


	else {

		printf("\nList: ");

		while (P != NULL) {
			if ((P->firstname && P->lastname) != NULL && P->birthyear != 0) 
				printf("\n%s %s %d", P->firstname, P->lastname, P->birthyear);
			P = P->next;
		}
	}
	return END_OF_PROGRAM;
}

int InsertInTheEnd(Position P) {

	Position q = NULL;

	while (P->next != NULL)
		P = P->next;

	q = P;

	AddPerson(q);

	return END_OF_PROGRAM;
}

int FindPersonByLastname(Position P) {

	char lastnm[MAX_LINE] = { 0 };

	printf("\nEnter the person lastname: ");
	scanf(" %s", lastnm);

	while (P->next != NULL && strcmp(P->lastname, lastnm) != 0)
		P = P->next;

	printf("%s %s %d", P->firstname, P->lastname, P->birthyear);

	return END_OF_PROGRAM;
}

AddAfter(Position P) {

	char lastnm[MAX_LINE] = { 0 };

	printf("\nEnter the person lastname: ");
	scanf(" %s", lastnm);
	Position prev = NULL;

	prev = Find(P, lastnm);

	if (prev == NULL)
		return ERROR;

	AddPerson(prev);

	return END_OF_PROGRAM;
}

int DeletePerson(Position P) {

	char lastnm[MAX_LINE] = { 0 };

	printf("\nEnter the person lastname: ");
	scanf(" %s", lastnm);

	Position previous = NULL;
	Position Current = NULL;

	previous = FindPrevious(P,lastnm);

	if (previous == NULL)
		return ERROR;

	Current = previous->next;
	previous->next = previous->next->next;

	free(Current);

	return END_OF_PROGRAM;
}

Position FindPrevious(Position P, char* lastnm) {

	Position Previous = NULL;
	Position Current = NULL;

	Previous = P;
	Current = Previous->next;

	while (Current != NULL && (strcmp(lastnm,Current->lastname) != 0)) {

		Previous = Current;
		Current = Previous->next;
	}

	if (Current == NULL)
		return NULL;

	return Previous;
}

Position Find(Position P, char* lastnm) {

	while (P->next!=NULL && strcmp(P->lastname, lastnm)!=0)
		P = P->next;

	if (P == NULL)
		printf("Person does not exist!");

	return P;
}

int AddBefore(Position P) {

	char lastnm[MAX_LINE] = { 0 };

	printf("\nEnter the person lastname: ");
	scanf(" %s", lastnm);

	Position prevp = NULL;
	prevp = FindBefore(P, lastnm);

	if (prevp == NULL)
		return ERROR;

	AddPerson(prevp);

	return END_OF_PROGRAM;
}

Position FindBefore(Position P, char * lastnm) {

	Position prev = NULL;
	Position curr = NULL;

	prev = P;
	curr = prev->next;

	while (curr!=NULL && strcmp(curr->lastname, lastnm)!=0) {

		prev = curr;
		curr = prev->next;
	}

	if (curr == NULL)
		return NULL;

	return prev;
}

void Sort(Position P) {
	Position j, prev_j, temp, end;

	end = NULL;

	while (P->next != end) {

		prev_j = P;
		j = P->next;

		while (j->next != end) {

			if (strcmp(j->lastname, j->next->lastname) > 0) {

				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next=j;

				j = temp;
			}

			prev_j = j;
			j = j->next;
		}

		end = j;
	}
}

int WriteToFile(Position P){

	FILE* fp=NULL;

	char filename[MAX_LINE];

	printf("\nInsert filename: ");
	scanf(" %s", filename);

	fp = fopen(filename, "w");

	if (fp == NULL)
		return ERROR;

	P = P->next;

	while (P != NULL) {
		
		fprintf(fp, "\n%s %s %d", P->firstname, P->lastname, P->birthyear);
		P = P->next;
	}

	fclose(fp);

	return END_OF_PROGRAM;
}

int ReadFromFile(Position P){

	FILE* fp;

	char filename[MAX_LINE];
	
	Position temp;

	printf("\nInsert filename: ");
	scanf(" %s", filename);

	fp = fopen(filename, "r");

	if (fp == NULL) 
		return ERROR;

	while (feof(fp) == 0) {

		temp = (Position)malloc(sizeof(struct person));

		fscanf(fp," %s %s %d", temp->firstname, temp->lastname, &temp->birthyear);
		

		temp->next = P->next;
		P->next = temp;
		P = temp;
	}

	fclose(fp);

	return END_OF_PROGRAM;
}

void DeleteFromBeginning(Position P){

	Position temp;

	while (P->next!=NULL) {
		temp = P->next;
		P->next = P->next->next;
		free(temp);
	}
}
