#ifndef LIST_H
#define LIST_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define END_OF_PROGRAM (0)
#define ERROR (-1)
#define MAX_NUM_OF_CHAR (256)

struct Person;
typedef struct Person *Position;
typedef struct Person{
    char firstName[MAX_NUM_OF_CHAR];
    char lastName[MAX_NUM_OF_CHAR];
    int birthYear;

    Position Next;   

}person;

int InsertData(Position p);
int addElement(Position p);
int printList(Position p);
int addElementAtBack(Position p);
int deleteElement(char* LastName, Position p);
int addElementInfrontAnother(char* LastName, Position p);
int addElementBehindAnother(char* LastName, Position p);
int writeListToFile(Position p);
int readFromFile( char* fileName, Position p);
int findElement(char* LastName, Position p);
void deleteList(Position p);
void sortList(Position p);
Position prevElement(char* LastName, Position p);
Position findPosition(char* LastName, Position p);

#endif