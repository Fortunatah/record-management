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

void print_line(){
    printf("\n--------------------------------------------\n");
}


int verify_char() {
    char line[64];
    int c;

    if (!fgets(line, sizeof line, stdin)) {
        printf("Please enter either y or n\n");
        return 2;
    }

    if (line[strlen(line) - 1] != '\n') {
        while ((c = getchar()) != '\n' && c != EOF) {}
    }

    if (line[0] == 'y' && line[1] == '\n') return 1;
    if (line[0] == 'n' && line[1] == '\n') return 0;

    printf("Please enter either y or n\n");
    return 2;
}

int count_columns(char *fileName){
    FILE *file = fopen( fileName , "r");
    int columnCount = 0;
    char buffer[1024];
    while (fgets(buffer , sizeof(buffer) , file)){
        columnCount++;
    }
    return columnCount;
}

void write_to_csv(char *fileName , record Record ){
    int count = count_columns(fileName);
    printf("count columns = %d\n"  , count);
}

int int_length( int num ){
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