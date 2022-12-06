#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define END (0)
#define ERROR (-1)
#define MAX_NUM_OF_CHAR (256)

struct stog;
struct postfix;
typedef struct stog *pos;
typedef struct postfix *Pos;

typedef struct stog{
    char sign[MAX_NUM_OF_CHAR];
    pos next;
}S;

typedef struct postfix{
    char PostFix[MAX_NUM_OF_CHAR];
    Pos next;
}P;

Pos readFromFile(char*);
Pos oprStog(pos, pos, Pos, char*);
int print(Pos);
int Push(Pos, char*);
int push(pos, char*);
int pop(pos);
int convertToString(Pos);

static int count = 0;
char string[MAX_NUM_OF_CHAR] = {0};

int main(){

    Pos izrazi = NULL;
    char FileName[MAX_NUM_OF_CHAR] = {0};
    scanf(" %[^\n]%*c", FileName);
    izrazi = readFromFile(FileName);
    if(izrazi == NULL)
        return ERROR;

    print(izrazi);
    convertToString(izrazi);
    printf("%s\n", string);

    return END;
}

Pos readFromFile(char *FileName){

    FILE *fp = NULL , *fc = NULL;
    char buffer[MAX_NUM_OF_CHAR], opr[MAX_NUM_OF_CHAR] = {0}, num[MAX_NUM_OF_CHAR] = {0}, new_fileName[256] = "newFile.txt";
    char *p = NULL;
    int check = 0, n = 0, i = 0;
    Pos izraz = NULL, post_temp = NULL, q_p = NULL;
    pos stog_temp = NULL, start = NULL, prev_ = NULL;

    izraz = (Pos)malloc(sizeof(P));

    fp = fopen(FileName,"r");
    if(fp != NULL){
        while(1){
            if(fgets(buffer,MAX_NUM_OF_CHAR,fp) == NULL)
                break;
            count++;
        }
        rewind(fp);
    }
    else { 
        fc = fopen(new_fileName, "w+");
        if(fc == NULL){
            printf("Error occured while opening file!\n");
            return NULL;
        }
        fprintf(fc,"%s",FileName);
        while(1){
            if(fgets(buffer,MAX_NUM_OF_CHAR,fc) == NULL)
                break;
            count++;
        }
        rewind(fc);
    }

    while(1){

        if(fp != NULL){
            if(fgets(buffer,MAX_NUM_OF_CHAR,fp) == NULL)
                break;
        }
        else {
            if(fgets(buffer,MAX_NUM_OF_CHAR,fc) == NULL)
                break;
        }

        P Post = { .PostFix = {0}, .next = NULL };
        S Stog = { .sign = {0}, .next = NULL };

        post_temp = &Post;
        stog_temp = &Stog;

        p = buffer;
        while(strlen(p) > 0){
            q_p = (Pos)malloc(sizeof(P));
            if(sscanf(p,"%d %n", &check, &n) <= 0){
                sscanf(p,"%s %n", opr, &n);
                post_temp = oprStog(&Stog,stog_temp,post_temp,opr);
                stog_temp = stog_temp->next;
                if(stog_temp == NULL){
                    stog_temp = &Stog;
                    stog_temp = stog_temp->next;
                }
            }
            else {
                sscanf(p,"%s %n", num, &n);
                Push(post_temp,num);
                post_temp = post_temp->next;
            }
            p+=n;
        }
        
        stog_temp = start = prev_ = &Stog;
        while(start->next != NULL){
            while(stog_temp->next != NULL){
                prev_ = stog_temp;
                stog_temp = stog_temp->next;
            }
            Push(post_temp,stog_temp->sign);
            post_temp = post_temp->next;
            pop(prev_);
            stog_temp = start;
        }
        izraz[i] = Post;
        i++;
    }
    fclose(fp);
    fclose(fc);
    return izraz;
}

Pos oprStog(pos s_head, pos s_curr , Pos p, char *opr){

    if(s_head == NULL){
        printf("Greska u oprStog!!\n");
        return NULL;
    }

    pos temp = NULL, start = NULL, tmp = NULL;
    temp = start = tmp = s_head;

    if(strcmp(s_curr->sign,opr) != 0 && strcmp(s_curr->sign,"*") == 0){
        if(strcmp(opr,"+") == 0 || strcmp(opr,"-") == 0 ){
            while(start->next != NULL){
                while(temp->next != NULL){
                    tmp = temp;
                    temp = temp->next;
                }
                Push(p,temp->sign);
                p = p->next;
                tmp->next = NULL;
                free(temp);
                temp = start;
            }
            push(start,opr);
        }
        else
            push(s_curr,opr);
    }
    else
        push(s_curr,opr);

    return p;
}

int Push(Pos s, char *post){

    if(s == NULL){
        printf("Greska u Push!!\n");
        return ERROR;
    }
    Pos q = NULL;
    q = (Pos)malloc(sizeof(P));
    strcpy(q->PostFix,post);
    q->next = s->next;
    s->next = q;

    return END;
}

int push(pos s, char *opr){

    if(s == NULL){
        printf("Greska u push!!\n");
        return ERROR;
    }
    pos q = NULL;
    q = (pos)malloc(sizeof(S));
    strcpy(q->sign,opr);
    q->next = s->next;
    s->next = q;

    return END;
}

int pop(pos s){

    if(s == NULL){
        printf("Greska u pop!!\n");
        return ERROR;
    }
    pos temp = NULL;
    temp = s->next;
    s->next = s->next->next;
    free(temp);

    return END;
}

int print(Pos p){

    if(p == NULL){
        printf("The list is empty!!\n");
        return ERROR;
    }
    while(p->next != NULL){
        printf("%s ", p->next->PostFix);
        p = p->next;
    }
    printf("\n");

    return END;
}

int convertToString(Pos p){

    if(p == NULL){
        printf("Not able to convert to string!!\n");
        return ERROR;       
    }

    while(p->next != NULL){
        strcat(string,p->next->PostFix);
        p = p->next;
    }

    return END;
}
