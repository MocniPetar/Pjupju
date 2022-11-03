#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define END_OF_PROGRAME (0);
#define MAX_LINE (50)

struct person;
typedef struct person* Position;

 typedef struct person{
	char firstname[MAX_LINE];
	char lastname[MAX_LINE];
	int birthyear;
	Position next;
}Person;

void Add_Element(Position);
void PrintList(Position);
Position FindLast(Position);
Position FindPrevious(Position);
Position Find(Position);
void Delete(Position);

int main(int argc, char **argv) {
	
	char Lastname[MAX_LINE] = { 0 };
	struct person* q;
	int NumofFuc;

	Person head = {
		.firstname = { 0 },
		.lastname = { 0 },
		.birthyear = 0,
		.next = NULL
	};
	
	printf("Please insert number of function which you what to execute: \n1.Add person\n2.Print list\n3.Add person on the end of the list\n4.Find person by lastname\n5.Delete person\nAnswear: ");
	scanf("%d", &NumofFuc);

	if (NumofFuc == 1)
		Add_Element(&head);

	else if (NumofFuc == 2)
		PrintList(&head);

	else if (NumofFuc == 3) {
		q = FindLast(&head);
		Add_Element(q);
	}

	else if (NumofFuc == 4) {
		q = Find(head.next);
		if (NULL == q)
			printf("\n The person does not exist!");
		else
			printf("\n\tPerson is: %s %s, %d", q->firstname, q->lastname, q->birthyear);
	}

	else if (NumofFuc == 5)
		Delete(&head);

	else
		printf("\nWrong input!\n");

	return END_OF_PROGRAME;
}

void Add_Element(Position P) {

	Position q;

	q = (Position)malloc(sizeof(struct person));

	printf("\nInsert information about the person: ");
	scanf(" %s %s %d", q->firstname, q->lastname, &q->birthyear);

	q->next = P->next;
	P->next = q;
}

void PrintList(Position P){

	if (NULL == P)
		printf("\nThe list is empty!\n");

	else {

		printf("\nList: \n");

		while (P != NULL) {

			printf("\n\t %s %s %d", P->firstname, P->lastname, P->birthyear);
			P = P->next;

		}
	}

}

Position FindLast(Position P) {

	while (NULL != P)
		P = P->next;

	return P;
}

Position FindPrevious(Position P) {

	char lastnm[50] = {0};

	if (NULL == P->next)
		P = NULL;

	else {

		printf("Please insert persons lastname: ");
		scanf(" %s", lastnm);

		while (strcmp(P->next->lastname, lastnm)!=0 && P->next->next!=NULL)
			P = P->next;

		while (strcmp(P->next->lastname,lastnm)!=0)
			P = NULL;
		}

	return P;
}

Position Find(Position P) {

	char lastnm[50] = {0};

	printf("\nPlease insert persons, who you want to find, lastname: ");
	scanf(" %s", lastnm);

	while (P != NULL && strcmp(P->lastname, lastnm) != 0)
		P = P->next;

	return P;
}

void Delete(Position P) {

	Position prev;

	prev = FindPrevious(P);

	if (NULL != prev) {

		P = prev->next;
		prev->next = P->next;

		printf("\nPerson: %s %s %d is deleted", P->firstname, P->lastname, P->birthyear);

		free(P);
	}
	else
		printf("\nThe person do not exist in the list.");

}
