#define _CRT_SECURE_NO_WARNING
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define END (0)
#define MAX_CHAR (4094)
#define ERROR (-1)

struct polinomi;

typedef struct polinomi *pos;

typedef struct polinomi{
    int ind;
    int eks;

    pos next;

}pol;

pos readFromFile(char*);
pos prevElement(pos,int);
void addElement(pos, char*);
int eliminate(pos);
int printList(pos);

int main(){

    char FileName[MAX_CHAR] = {0};
    pos ListaPolinoma;

    printf("Enter name of file: \n");
    scanf(" %s",FileName);

    ListaPolinoma = readFromFile(FileName);
    if(ListaPolinoma == NULL){
        printf("Greska!!\n");
        return END;
    }

    return END;
}

pos readFromFile(char* fileName){

    FILE *fp = NULL;
    char buffer[MAX_CHAR] = {0};
    char *P = buffer;
    int temp_ind = 0, temp_eks = 0;
    int n = 0;
    int count = 0;

    pos listOfPol = NULL;

    fp = fopen(fileName, "r");

    if(fp == NULL){
        printf("Warning!!\n");
        return NULL;
    }

    while(1){
        if(fgets(buffer,MAX_CHAR,fp) == NULL)
            break;
        count++;
    }

    listOfPol = (pos)malloc(sizeof(pol) * count);

    rewind(fp);
    while(1){
        if(fgets(buffer,MAX_CHAR,fp) == NULL)
            break;
        pol Head = {
            .ind = 0,
            .eks = 0,
            .next = NULL
        };
        addElement(&Head, buffer);
        listOfPol[n] = Head;
        eliminate(&listOfPol[n]);
        printList(&listOfPol[n]);
        printf("\n");
        n++;
    }
    fclose(fp);
    return listOfPol;
}

void addElement(pos p, char* buffer){

    char *P = NULL;
    int n = 0;
    P = buffer;

    pos temp = NULL, prev = NULL, q = NULL;

    // Objasni ovo na papiru !!!
    while(strlen(P) > 0){
        q = (pos)malloc(sizeof(pol));
        sscanf(P, "%d %d %n", &q->ind, &q->eks, &n);
        temp = p->next;
        prev = p;
        while(temp != NULL && temp->eks > q->eks){
            prev = temp;
            temp = temp->next;
        }
        prev->next = q;
        if(temp != NULL)
            q->next = temp;
        else
            q->next = NULL;
        P+=n;
    }
}

int eliminate(pos p){

    pos temp = NULL, prev = NULL, next_ = NULL, curr = NULL, temp1 = NULL;

    curr = p;
    temp = p;

    while(temp->next != NULL){
        if(temp->eks == temp->next->eks){
            if(temp->ind < temp->next->ind){
                prev = prevElement(curr,temp->ind);
                next_ = temp->next->next;

                temp = prev->next;
                free(temp);
                temp = temp->next;
                free(temp);
                temp = next_;
                prev->next = next_;
            }
        }
        else
            temp = temp->next;
    }

    return END;
}

int printList(pos p){

    p = p->next;

    if(p == NULL){
        printf("Lista je prazna!!\n");
        return ERROR;
    }
    while(p != NULL){
        printf("%dx^%d ",p->ind,p->eks);
        p = p->next;
        }
    return END;
}

pos prevElement(pos p,int ind){
    pos prev = NULL;
    pos curr = NULL;

    prev = p;
    curr = prev->next;

    while(curr != NULL && curr->ind != ind){
        prev = curr;
        curr = prev->next;
    }

    if(curr == NULL)
        return NULL;

    return prev;
}