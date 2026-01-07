/*
This will be for my reused functions
makes it cleaner and easier to access
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "general_functions.h"

// Functions

int int_length( int num){
    int length = 0;
    if(num <= 0 ) return 1;
    while(num > 0 ){
        length++;
        num /= 10;
    }
    return length;
}

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

bool allCharacters(const char *buf){
    for( int i = 0; buf[i] != '\0' ; i++){
        if(!isalpha((unsigned char)buf[i])){
            if(buf[i] == ' '){
                continue;
            }return false;
        }
    }
    return true;
}

char *verify_string(void){

    char scanString[100];
    if (strchr(scanString, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    fgets(scanString , sizeof scanString , stdin);
    scanString[strcspn(scanString, "\n")] = '\0';

    if(allCharacters(scanString)){
        char *string = malloc(strlen(scanString) + 1);
        if(!string) return NULL;
        strcpy(string, scanString);
        return string;
    }
}