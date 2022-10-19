#define _CRT_SECURE_NO_WARNING

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT (0)
#define FILE_DID_NOT_OPEN (-1)
#define LENGHT_OF_FILE_NAME (256)
#define MAX_LENGHT_OF_LINE (1024)

typedef struct{
    char ime[50], prezime[50];
    int bodovi;
}student;

int countNumberOfStudents(FILE*, char []);
void UnosPodataka(FILE*,student*,char [],int);
void Ispis(FILE*,student*,int,char []);

int main(void){

    student *st;
    FILE *fp = NULL;
    int numOfStudents;
    char filename[LENGHT_OF_FILE_NAME];

    printf("Enter the name of the file:\nC>: ");
    scanf(" %s", filename);

    numOfStudents = countNumberOfStudents(fp,filename);
    st = (student *)malloc(sizeof(student) * numOfStudents);

    UnosPodataka(fp,st,filename,numOfStudents);
    Ispis(fp,st,numOfStudents,filename);

    fclose(fp);
    return EXIT;
}

int countNumberOfStudents(FILE *fp, char filename[LENGHT_OF_FILE_NAME]){

    char buffer[MAX_LENGHT_OF_LINE] = { 0 };
    int counter = 0;

    fp = fopen(filename , "r");
    if (fp == NULL){
        printf("Error occurred while opening %s", filename);
        exit(EXIT_FAILURE);
    }

    while(!feof(fp)){
        fgets(buffer,MAX_LENGHT_OF_LINE,fp);
        if(strcmp("\n",buffer) != 0){
            counter++;
        }
    }
    
    fclose(fp);
    return counter-1;
}

void UnosPodataka(FILE *fp, student *st, char filename[LENGHT_OF_FILE_NAME],int n){
    
    char buffer[MAX_LENGHT_OF_LINE] = { 0 };
    int i;
    
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Error occurred while opening %s", filename);
        exit(EXIT_FAILURE);
    }

    fscanf(fp,"%*[^\n]\n"); //Za preskocit prvi red u tekst datoteci

    for(i=0;i<n;i++){
        fscanf(fp,"%s %s %d", st[i].ime, st[i].prezime, &st[i].bodovi);
    }

    fclose(fp);
}

void Ispis(FILE *fp,student *st, int n,char filename[LENGHT_OF_FILE_NAME]){

    char buffer[MAX_LENGHT_OF_LINE] = { 0 };
    int maxBrojBodova;
    
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Error occurred while opening %s", filename);
        exit(EXIT_FAILURE);
    }

    fscanf(fp,"%*s %*s %*s %d", &maxBrojBodova); //Sa %*s ignoriramo inpute tipa string

    int i;
    for(i = 0;i < n;i++){
        printf("Ime i Prezime: %s %s \n", st[i].ime, st[i].prezime);
        printf("Broj bodova: %d\n", st[i].bodovi);
        printf("Relativan broj bodova: %.2f%%\n\n", ((float)st[i].bodovi/maxBrojBodova)*100);
    }

    fclose(fp);
}
