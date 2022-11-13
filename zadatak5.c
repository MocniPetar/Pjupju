#define _CRT_SECURE_NO_WARNING
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define END (0)
#define ERROR (-1)
#define MIN_CHAR (8)
#define MAX_CHAR (256)


static int count = 0;
struct stog;
typedef struct stog *pos;
typedef struct stog{
    float broj;
    pos next;
}st;

pos readFile(char*);
int push(pos, float);
int pop(pos, float);
int printList(pos);

int main(){

    st Head = {
        .broj = 0,
        .next = NULL
    };
    char fileName[MAX_CHAR] = {0};

    printf("Enter the name of the file:\n\t");
    scanf(" %s", fileName);

    pos List = NULL;

    List = readFile(fileName);
    if(List == NULL){
        printf("WARNING!!\n");
        return END;
    }
    return END;
}

pos readFile(char* fileName){

    FILE *fp = NULL;
    char buffer[MAX_CHAR] = {0}, oznaka[MIN_CHAR] = {0};
    char *p = NULL;
    int n = 0;
    float result = 0.0;
    int count_ = 0;
    pos List = NULL, temp = NULL, q = NULL;

    fp = fopen(fileName, "r");

    if(fp == NULL){
        printf("WARNING!!\n");
        return NULL;
    }

    while(1){
        if(fgets(buffer,MAX_CHAR,fp) == NULL)
            break;
        count++;
    }

    List = (pos)malloc(sizeof(st) * count);
    rewind(fp);

    while(1){

        if(fgets(buffer, MAX_CHAR, fp) == NULL)
            break;
        st Head = {
            .broj = 0,
            .next = NULL
        };
        temp = &Head;

        p = buffer;
        while(strlen(p) > 0){
            q = (pos)malloc(sizeof(st));
            if(sscanf(p, "%f%n", &q->broj, &n) <= 0){
                sscanf(p, "%s%n", oznaka, &n);
                
                if(strcmp(oznaka, "+") == 0){
                    result = temp->broj + temp->next->broj;
                    push(temp,result);
                    pop(&Head,result);
                }
                else if(strcmp(oznaka, "-") == 0){
                    result = temp->broj - temp->next->broj;
                    push(temp,result);
                    pop(&Head,result);
                }
                else if(strcmp(oznaka, "*") == 0){
                    result = temp->broj * temp->next->broj;
                    push(temp,result);
                    pop(&Head,result);
                }
                else {
                    result = temp->broj / temp->next->broj;
                    push(temp,result);
                    pop(&Head,result);
                }
            }
            else{
                sscanf(p, "%f%n", &q->broj, &n);
                while(temp->next != NULL)
                temp = temp->next;

                q->next = temp->next;
                temp->next = q;
            }

            p += n;
        }
    
        List[count_] = Head;
        count_++;
    }

    printList(&List[0]);

    return List;
}

int push(pos p, float r){

    if(p == NULL)
        return ERROR;
    
    while(p->next != NULL)
        p=p->next;
    
    p->broj = r;

    return END;
}

int pop(pos p, float r){

    if(p == NULL)
        return ERROR;
    
    pos temp = NULL;

    while(p->next != NULL && p->next->broj != r){
        temp = p->next;
        p = p->next->next;
        free(temp);
    }

    return END;
}

int printList(pos p){

    if(p == NULL)
        return ERROR;
    
    while(p->next != NULL){
        printf("%.2f ", p->next->broj);
        p = p->next;
    }

    return END;
    
}