#include "list.h"

int InsertData(Position p){
    printf("\tEnter the name,lastname and birth year: ");
    scanf(" %s %s %d", p->firstName, p->lastName, &p->birthYear);

    return END_OF_PROGRAM;
}

int addElement(Position p){
    Position q = NULL;
    q = (Position)malloc(sizeof(person));

    if(q == NULL)
        return ERROR;
    
    InsertData(q);
    q->Next = p->Next;
    p->Next = q;

    return END_OF_PROGRAM;
}

int findElement(char* LastName, Position p){

    while(p->Next != NULL && (strcmp(p->lastName,LastName) != 0))
        p = p->Next;

    if(p == NULL)
        return ERROR;

    printf("%s %s %d \n", p->firstName,p->lastName,p->birthYear);

    return END_OF_PROGRAM;
}

int addElementAtBack(Position p){
    Position last = NULL;
    while(p->Next != NULL)
        p=p->Next;
    last = p;
    addElement(last);
    return END_OF_PROGRAM;
}

int deleteElement(char* LastName, Position p){

    Position prev = NULL;
    Position curr = NULL;

    prev = prevElement(LastName,p);

    if(prev == NULL)
        return ERROR;
    
    curr = prev->Next;
    prev->Next = prev->Next->Next;
    free(curr);

    return END_OF_PROGRAM;
}

int printList(Position p){

    if(p == NULL){
        printf("Lista je prazna!!\n");
        return ERROR;
    }
    while(p != NULL){
        printf("%s %s %d \n",p->firstName,p->lastName,p->birthYear);
        p = p->Next;
        }
    return END_OF_PROGRAM;
}

int addElementInfrontAnother(char* LastName, Position p){
    
    Position pos = NULL;
    pos = prevElement(LastName, p);

    if(pos == NULL)
        return ERROR;

    addElement(pos);

    return END_OF_PROGRAM;
}

int addElementBehindAnother(char* LastName, Position p){

    Position prev = NULL;
    prev = findPosition(LastName, p);

    if(prev == NULL)
        return ERROR;

    addElement(prev);

    return END_OF_PROGRAM;
}

int writeListToFile(Position p){

    if(p == NULL)
        return ERROR;

    FILE *fp;
    fp = fopen("lista.txt", "w");

    if(fp == NULL){
        printf("Greska!\n");
        return ERROR;
    }

    while(p != NULL){
        fprintf(fp,"%s %s %d \n", p->firstName, p->lastName, p->birthYear);
        p = p->Next;
    }

    fclose(fp);
    return 0;
}

int readFromFile(char* fileName, Position p){

    Position q = NULL;
    FILE *fp;
    fp = fopen(fileName,"r");

    if(fp == NULL){
        printf("Greska!");
        return ERROR;
    }

    while(!feof(fp)){
        q = (Position)malloc(sizeof(person));

        if(q == NULL)
            break;
        
        fscanf(fp,"%s %s %d", q->firstName, q->lastName, &q->birthYear);

        q->Next = p->Next;
        p->Next = q;
    }

    fclose(fp);
    return END_OF_PROGRAM;
}

void deleteList(Position p){

    Position temp;

    while(p->Next != NULL){
        temp = p->Next;
        p->Next = p->Next->Next;
        free(temp);
    }
}

void sortList(Position p){

    Position curr, prev, temp, end;

    end = NULL;
    while(p->Next != end){
        prev = p;
        curr = p->Next;
        while(curr->Next != end){
            if(strcmp(curr->lastName, curr->Next->lastName) > 0){
                temp = curr->Next;
                prev->Next = temp;
                curr->Next = temp->Next;
                temp->Next = curr;

                curr = temp;
            }
            prev = curr;
            curr = curr->Next;
        }
        end = curr;
    }
}

Position prevElement(char* LastName, Position p){
    
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

Position findPosition(char* LastName, Position p){

    while(p->Next!= NULL && (strcmp(p->Next->lastName,LastName) != 0))
        p = p->Next;

    if(p == NULL){
        printf("Element doesn't exist!\n");
        return NULL;
    }

    return p;
}