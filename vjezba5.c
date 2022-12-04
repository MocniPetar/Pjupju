#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define END (0)
#define ERROR (-1)
#define MAX_LINE (1024)

typedef struct Stog;
typedef struct Stog* Position;
struct Stog {
    float broj;
    Position next;
} *head = NULL; 

int Push(float);
int Pop();
float ReadFromFile(char*);

int main(){

    float result = 0.0;
    char filename[MAX_LINE] = { 0 };

    printf("Enter the filename: ");
    scanf(" %s", filename);

    result = ReadFromFile(filename);

    printf("Result: %.2f", result);

    free(head);

    return END;
}

float ReadFromFile(char* filename) {
     
    char buffer[MAX_LINE] = { 0 }, mark[MAX_LINE] = { 0 };
    char* p = NULL;
    float num1 = 0.0, num2 = 0.0, value=0.0;
    int n = 0;

    FILE* fp = NULL;
    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("File did not open!");
        return ERROR;
    }

    fgets(buffer, MAX_LINE, fp);
    p = buffer;

    while (strlen(p) > 0)
    {
        if (sscanf(p, "%f %n", &value, &n) <= 0){
            sscanf(p, "%s %n", mark, &n);

            if (strcmp(mark, "+") != 0 && strcmp(mark, "-") != 0 && strcmp(mark, "*") != 0 && strcmp(mark, "/") != 0) {
                printf("The operation or value is not correct!");
                fclose(fp);
                exit(1);
            }

            if (head==NULL) {
                printf("Error, operation can not be first!");
                fclose(fp);
                exit(1);
            }

            num1 = Pop();
            num2 = Pop();
            
            
            if (strcmp(mark, "+") == 0) 
                Push(num2 + num1);

            else if (strcmp(mark, "-") == 0)
                Push(num2 - num1);

            else if (strcmp(mark, "*") == 0)
                Push(num2 * num1);

            else{
                if (num1 == 0.0) {
                    printf("Undefined!");
                    Pop();
                    fclose(fp);
                    exit(1);
                }
                else
                    Push(num2 / num1);
            } 
        }

        else 
            Push(value);

        p += n;
    }
        
    if (head != NULL && head->next == NULL) {
        fclose(fp);
        return Pop();
    }

    printf("There is more than one element left in stack!\n");
    fclose(fp);
    exit(1);
}

int Push(float x){

    Position temp =NULL;
    temp = (Position)malloc(sizeof(struct Stog));

    if (temp == NULL)
    {
        printf("ERROR!");
        return ERROR;
    }

    temp->broj = x;
    temp->next = NULL;

    temp->next = head;
    head = temp;

    return END;
}

int Pop(){

    Position temp;
    float result = 0.0;

    temp = head;
    result = temp->broj;

    head = head->next;
    free(temp);
    temp = NULL;

    return result;
}