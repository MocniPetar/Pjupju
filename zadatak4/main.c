#define _CRT_SECURE_NO_WARNING
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define END (0)
#define MAX_CHAR (4094)
#define ERROR (-1)

static int count_ = 0;
struct polinomi;
typedef struct polinomi *pos;

typedef struct polinomi{
    int ind;
    int eks;

    pos next;

}pol;

int addElement(pos, char*);
int eliminate(pos);
int printList(pos);
int addingEachWEach(pos,pos,pos);
int add(pos,pos);
pos readFromFile(char*);
pos prevElement(pos,int);
pos multiplyPol(pos,pos);
pos findLast(pos);
pos addingTwoPol(pos,pos,pos);
void deleteList(pos);

int main(){

    char FileName[MAX_CHAR] = {0};
    char Operation[MAX_CHAR] = {0};
    pos ListaPolinoma = NULL;
    pos result = NULL;
    int pol1 = 0, pol2 = 0;

    pol Head = {
        .ind = 0,
        .eks = 0,
        .next = NULL
    };

    printf("Enter name of file: \n");
    scanf(" %s",FileName);

    ListaPolinoma = readFromFile(FileName);
    if(ListaPolinoma == NULL){
        printf("Error!!\n");
        return END;
    }

    while(1){

        printf("Add or multiply two polynomials: ");
        scanf(" %[^\n]s", Operation);

        if(strcmp("stop",Operation) == 0)
            break;

        printf("Choose two polynomials:\n");
        for(int i = 0; i < count_; i++){
            printf("\t%d. ", i+1);
            printList(&ListaPolinoma[i]);
        }
        scanf("%d %d", &pol1, &pol2);

        if(count_ >= pol1 && count_ >= pol2){
            if(strcmp("add",Operation) == 0){
                result = addingTwoPol(&ListaPolinoma[pol1-1],&ListaPolinoma[pol2-1],&Head);
                printf("Sum of polinomyal %d i polinomyal %d:\n\t",pol1,pol2);
                printList(result);
            }
            else if(strcmp("multiply",Operation) == 0){
                printf("Product of polinomyial %d and polinomyal %d:\n\n\t",pol1,pol2);
                result = multiplyPol(&ListaPolinoma[pol1-1],&ListaPolinoma[pol2-1]);
            }
            else
                printf("Wrong input! Enter again.\n");
        }
        printf("\n");
    }

    deleteList(result);
    for(int i = 0; i < count_; i++)
        deleteList(&ListaPolinoma[i]);

    return END;
}

pos readFromFile(char* fileName){

    FILE *fp = NULL;
    char buffer[MAX_CHAR] = {0};
    char *P = buffer;
    int n = 0;

    pos listOfPol = NULL;

    fp = fopen(fileName, "r");

    if(fp == NULL){
        printf("Error!!\n");
        return NULL;
    }

    while(1){
        if(fgets(buffer,MAX_CHAR,fp) == NULL)
            break;
        count_++;
    }

    listOfPol = (pos)malloc(sizeof(pol) * count_);

    rewind(fp);
    while(1){
        if(fgets(buffer,MAX_CHAR,fp) == NULL)
            break;
        pol Head = {
            .ind = 0,
            .eks = 0,
            .next = NULL
        };

        if(addElement(&Head, buffer) < 0){
            printf("Error!!\n");
            return NULL;
        }
        listOfPol[n] = Head;
        eliminate(&listOfPol[n]);
        n++;
    }
    fclose(fp);
    return listOfPol;
}

int addElement(pos p, char* buffer){

    char *P = NULL;
    int n = 0;
    P = buffer;

    pos temp = NULL, prev = NULL, q = NULL;

    while(strlen(P) > 0){
        q = (pos)malloc(sizeof(pol));
        if(q == NULL)
            return ERROR;

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

    return END;
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

pos addingTwoPol(pos p1, pos p2, pos p){

    pos q = NULL, temp = NULL;

    if(p1 == NULL || p2 == NULL){
        printf("Error!!\n");
        return NULL;
    }

    while(p1->next != NULL && p2->next != NULL){

        q = (pos)malloc(sizeof(pol));

        if(p1->next->eks == p2->next->eks){
            q->ind = p1->next->ind+p2->next->ind;
            q->eks = p1->next->eks;

            temp = findLast(p);
            add(temp,q);
            p1 = p1->next;
            p2 = p2->next;
        }
        else {
            if(p1->next->eks > p2->next->eks){
                q->ind = p1->next->ind;
                q->eks = p1->next->eks;
                
                temp = findLast(p);
                add(temp,q);
                p1 = p1->next;
            }
            else{
                q->ind = p2->next->ind;
                q->eks = p2->next->eks;

                temp = findLast(p);
                add(temp,q);
                p2 = p2->next;
            }
        }
    }

    if(p1->next == NULL)

        while(p2->next != NULL){
            q = (pos)malloc(sizeof(pol));
            q->ind = p2->next->ind;
            q->eks = p2->next->eks;

            temp = findLast(p);
            add(temp,q);
            p2 = p2->next;
        }
    else
        while(p1->next != NULL){
            q = (pos)malloc(sizeof(pol));
            q->ind = p1->next->ind;
            q->eks = p1->next->eks;

            temp = findLast(p);
            add(temp,q);
            p1 = p1->next;
        }

    return p;
}

pos multiplyPol(pos p1, pos p2){

    pos result_ = NULL, temp = NULL, tmp = NULL;
    pos p = NULL, p_ = NULL;
    int count = 0, n = 0;

    p = p_ = p1;
    while(p1->next != NULL){
        count++;
        p1 = p1->next;
    }

    result_ = (pos)malloc(sizeof(pol) * count);
    while(p->next != NULL){

        pol Head = {
            .ind = 0,
            .eks = 0,
            .next = NULL
        };

        addingEachWEach(p->next,p2->next,&Head);
        result_[n] = Head;
        n++;
        p = p->next;
    }

    n=0;
    while(p_->next->next != NULL){

        pol Head = {
            .ind = 0,
            .eks = 0,
            .next = NULL
        };
        addingTwoPol(&result_[n],&result_[n+1],&Head);
        n++;
        result_[n] = Head;
        temp = &result_[n];
        p_ = p_->next;
    }

    printList(temp);
    for(int i = 0; i < count; i++)
        deleteList(&result_[i]);

    return temp;
}

int addingEachWEach(pos p1, pos p2, pos p){

    pos temp = NULL, prev = NULL, q = NULL;
    temp = p;

    while(p2 != NULL){
        q = (pos)malloc(sizeof(pol));
        if(q == NULL)
            return ERROR;

        q->ind = p1->ind * p2->ind;
        q->eks = p1->eks + p2->eks;

        temp = findLast(p);
        q->next = temp->next;
        temp->next = q;
        p2 = p2->next;
    }

    return END;
}

int printList(pos p){

    p = p->next;

    if(p == NULL){
        printf("The list is empty!!\n");
        return ERROR;
    }
    while(p != NULL){
        printf("%dx^%d",p->ind,p->eks);
        if(p->next != NULL)
            printf("+");
        p = p->next;
        }
    printf("\n");
    return END;
}

pos findLast(pos p){
    while(p->next != NULL)
        p = p->next;
    
    return p;
}

int add(pos p, pos q){
     q->next = p->next;
     p->next = q;

     return END;
}

pos prevElement(pos p,int ind){

    pos prev = NULL, curr = NULL;

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

void deleteList(pos p){

    pos temp = NULL;
    while(p->next != NULL){
        temp = p->next;
        p->next = p->next->next;
        free(temp);
    }
}
