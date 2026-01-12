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
    printf("\n------------------------------------------------------------------------------------------------------\n");
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

int count_rows(char *fileName){
    FILE *file = fopen( fileName , "r");
    int rowsCount = 0;
    char buffer[1024];
    while (fgets(buffer , sizeof(buffer) , file)){
        rowsCount++;
    }
    return rowsCount;
}

char *create_tmp_path(char *fileName){

    int fileLength = strlen(fileName);
    int end = fileLength - 17; // library-books.csv is 17 characters long
    size_t bkupPathSize = 512;
    char *dir = malloc(bkupPathSize);
    
    // Create the string of th file
    for(int i = 0; i < end ; i++){
        dir[i] = fileName[i];
    }

    // Create the copy at it's path
    char bkupCSV[512];
    snprintf( bkupCSV  , sizeof(bkupCSV) , "%s%s" , dir , "tmp.csv");
    char * tmpLocation = malloc(sizeof(bkupCSV));
    strcpy(tmpLocation , bkupCSV);
    return tmpLocation;

}
void tmp_to_main( char *tmpFile , char *mainFile){
    FILE *tmp = fopen( tmpFile , "r");
    FILE *main = fopen( mainFile , "w");
    char string[256];
    while( fgets( string , sizeof(string) , tmp) != NULL){
        fputs(string , main);
    }
    fclose(main);
    fclose(tmp);
    remove(tmpFile);
}
void write_to_csv(char *fileName , record Record  , int rows){    
    char * tmpPath = create_tmp_path( fileName );
    FILE *mainFile;
    FILE *tmpFile = fopen( tmpPath, "a");
    char string[256];
    int count = 0;
    
    if((mainFile = fopen(fileName, "r"))){
        while( fgets( string , sizeof(string) , mainFile) != NULL){
            count++;
            if( rows == count ){
                if(rows == 1){
                    fprintf(tmpFile , "%s\n%d;%s;%d;%s;\n",
                    string,
                    Record.studentID,
                    Record.studentName,
                    Record.bookID,
                    Record.bookName);
                    break;
                    //printf("1.rows -> %d , put this string into file - >%s\n" , rows , string);
                }else{
                    fprintf(tmpFile , "%d;%s;%d;%s;\n",
                    Record.studentID,
                    Record.studentName,
                    Record.bookID,
                    Record.bookName);
                    // if end of file put string
                    // if not skip this string
                    if(fgets( string , sizeof(string) , mainFile) == NULL){
                        fputs( string , tmpFile );
                    } 
                    }
                }else{
                    fputs( string , tmpFile);
                }

            }
    }
    // we are closing them for now but we are going to copy tmp into main and delete temp
    fclose(mainFile);
    fclose(tmpFile);
    tmp_to_main( tmpPath , fileName );


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