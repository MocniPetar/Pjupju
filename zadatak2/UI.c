#include "UI.h"

int UI(){

    person Head = {
        .firstName = { 0 },
        .lastName = { 0 },
        .birthYear = 0,
        .Next = NULL
    };


    char LastName[MAX_NUM_OF_CHAR] = {0};
    char FileName[MAX_NUM_OF_CHAR] = {0};
    char ListFunctions[MAX_NUM_OF_CHAR] = {0};

    printf("List of functions for lists:\n");
    printf(" - Add element at front\n");
    printf(" - Add element at back\n");
    printf(" - Print list\n");
    printf(" - Find element\n");
    printf(" - Delete element\n");
    printf(" - Add element infront another\n");
    printf(" - Add element behind another\n");
    printf(" - Sort list\n");
    printf(" - Store list in file\n");
    printf(" - Read from file\n");
    printf(" - Stop\n");

    while(1){

    printf("Enter the name of a function: ");
    scanf(" %[^\n]s", ListFunctions);

    if(strcmp(ListFunctions, "Add element at front") == 0){
            if(addElement(&Head) < 0){
                return END_OF_PROGRAM;
            }
    }

    else if(strcmp(ListFunctions, "Add element at back") == 0){
            if(addElementAtBack(&Head) < 0){
                return END_OF_PROGRAM;
            }
    }

    else if(strcmp(ListFunctions, "Find element") == 0){
        printf("Enter the last name of the person: \n");
        scanf(" %s",LastName);
        if(findElement(LastName,&Head) < 0){
                return END_OF_PROGRAM;
            }
    }
    
    else if(strcmp(ListFunctions, "Delete element") == 0){
        printf("Enter the last name of the person to delete from list: \n");
        scanf(" %s",LastName);
        if(deleteElement(LastName,Head.Next) < 0){
                return END_OF_PROGRAM;
            }
    }

    else if(strcmp(ListFunctions, "Print list") == 0)
        printList(Head.Next);

    else if(strcmp(ListFunctions, "Add element infront another") == 0){
        printf("Enter the last name of the person: \n");
        scanf(" %s",LastName);
        if(addElementInfrontAnother(LastName, &Head) < 0){
                return END_OF_PROGRAM;
            }
    }

    else if(strcmp(ListFunctions, "Add element behind another") == 0){
        printf("Enter the last name of the person: \n");
        scanf(" %s",LastName);
        if(addElementInfrontAnother(LastName, Head.Next) < 0){
                return END_OF_PROGRAM;
            }
    }

    else if(strcmp(ListFunctions, "Store list in file") == 0){
        if(writeListToFile(Head.Next) < 0){
                return END_OF_PROGRAM;
            }
    }

    else if(strcmp(ListFunctions, "Read from file") == 0){
        printf("Enter the name of the file: \n\t");
        scanf(" %s",FileName);
        if(readFromFile(FileName, &Head) < 0){
                return END_OF_PROGRAM;
            }
    }

    else if(strcmp(ListFunctions, "Sort list") == 0)
        sortList(&Head);
    
    else if(strcmp(ListFunctions, "Stop") == 0){
        deleteList(&Head);
        break;
    }

    else
        printf("You searched for a function name that doesn't exit. Try again!\n");

    }

    return END_OF_PROGRAM;
}