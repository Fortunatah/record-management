/*
This will be for my reused functions
makes it cleaner and easier to access
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general_functions.h"

// Functions
void clear_screen(){
    #ifdef _WIN32 // if windows operating system
        system("cls");
    #else
        system("clear");
    #endif
} //void clear_screen()

int verify_choice(){
    int scanVal;
    if(scanf("%d" , &scanVal) !=1){
        while(getchar() !='\n');
        return -1;
    } // if(scanf("%d" , &scanVal) !=1)
    return scanVal;
}

char verify_string(){

    char scanString[100];
    fgets(scanString , sizeof scanString , stdin);
    //if(!fgets(scanString , sizeof scanString , stdin)){
    //    printf("Not working\n");
    //}
    if (strchr(scanString, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    printf("string = %s\n", scanString);

}