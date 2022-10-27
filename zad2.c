#define _CRT_SECURE_NO_WARNING
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define END_OF_PROGRAM (0)
#define ERROR (-1)
#define MAX_NUM_OF_CHAR (256)

typedef struct Person *Position;
typedef struct Person{
    char firstName[MAX_NUM_OF_CHAR];
    char lastName[MAX_NUM_OF_CHAR];
    int birthYear;

    Position Next;   

}person;

int InsertData(Position);
int addElementAtFront(Position);
int printList(Position);
int addElementAtBack(Position);
int findElement(char*, Position);
int deleteElement(char*, Position);
Position prevElemnt(char*, Position);

int main(){

    char LastName[MAX_NUM_OF_CHAR] = {0};
    char ListFunctions[MAX_NUM_OF_CHAR] = {0};

    person Head = {
        .firstName = { 0 },
        .lastName = { 0 },
        .birthYear = 0,
        .Next = NULL
    };

    printf("List of functions for lists:\n");
    printf(" - Add element at front\n");
    printf(" - Add element at back\n");
    printf(" - Print list\n");
    printf(" - Find element\n");
    printf(" - Delete element\n");

    while(1){

    printf("Enter the name of a function: ");
    scanf(" %[^\n]s", ListFunctions);

    if(strcmp(ListFunctions, "Add element at front") == 0)
            addElementAtFront(&Head);

    else if(strcmp(ListFunctions, "Add element at back") == 0)
            addElementAtBack(&Head);

    else if(strcmp(ListFunctions, "Find element") == 0){
        printf("Enter the last name of the person: \n");
        scanf(" %s",LastName);
        findElement(LastName,&Head);
    }
    
    else if(strcmp(ListFunctions, "Delete element") == 0){
        printf("Enter the last name of the person to delete from list: \n");
        scanf(" %s",LastName);
        deleteElement(LastName,Head.Next);
    }

    else if(strcmp(ListFunctions, "Print list") == 0)
        printList(Head.Next);

    else if(strcmp(ListFunctions, "Stop") == 0)
        break;

    else
        printf("You searched for a function name that doesn't exit. Try again!\n");

    }

    return END_OF_PROGRAM;
}

int InsertData(Position p){
    printf("Enter the name,lastname and birth year: ");
    scanf(" %s %s %d", p->firstName, p->lastName, &p->birthYear);

    return END_OF_PROGRAM;
}

int addElementAtFront(Position p){
    Position q = NULL;
    q = (Position)malloc(sizeof(person));
    if(q == NULL)
        return ERROR;
    InsertData(q);
    q->Next = p->Next;
    p->Next = q;
    return END_OF_PROGRAM;
}

int addElementAtBack(Position p){
    Position last = NULL;
    while(p->Next != NULL)
        p=p->Next;
    last = p;
    addElementAtFront(last);
    return END_OF_PROGRAM;
}

int findElement(char* LastName, Position p){

    while(p->Next != NULL && (strcmp(p->lastName,LastName) != 0))
        p = p->Next;

    printf("%s %s %d \n", p->firstName,p->lastName,p->birthYear);

    return END_OF_PROGRAM;
}

int deleteElement(char* LastName, Position p){

    Position prev = NULL;
    Position curr = NULL;

    prev = prevElemnt(LastName,p);

    if(prev == NULL)
        return ERROR;
    
    curr = prev->Next;
    prev->Next = prev->Next->Next;
    free(curr);

    return END_OF_PROGRAM;
}

int printList(Position p){

    int i = 0;
    while(p != NULL){
        printf("%s %s %d \n",p->firstName,p->lastName,p->birthYear);
        p = p->Next;
        }
    return END_OF_PROGRAM;
}

Position prevElemnt(char* LastName, Position p){
    
    Position prev = NULL;
    Position curr = NULL;

    prev = p;
    curr = prev->Next;

    while(curr != NULL && (strcmp(LastName, curr->lastName) != 0)){
        prev = curr;
        curr = prev->Next;
    }

    if(curr == NULL)
        return NULL;

    return prev;
}