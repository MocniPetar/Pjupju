#include<stdio.h>
#include "UI.h"

int main(){

    if(UI() < 0){
        printf("ERROR!\n");
        return ERROR;
    }

    return END_OF_PROGRAM;
}