/*
This will help the user search the record they are looking for
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "general_functions.h"

void print_base_header(){
    clear_screen();
    print_line();
    printf("Student ID , Student Name , Book ID, Book Name\n\n");
}

void clear_buffer(){
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

char *get_search_string(char *input){
    char *string = malloc(sizeof(input));
    strcpy( string , input ); 
    int length = strlen(string);
    int n; // for size
    if( length == 1 || length == 2){
        n = 1;
    }else{
        n = 3;
    }
    char *cpyString = malloc( n + 1);
    strncpy( cpyString , string , n);
    cpyString[n] = '\0';
    return cpyString;

}

bool keyword_in_string( char *tempString , char *searchString , size_t length){
    // remove the semicolons
    int i, j  = 0;
    size_t count = 0;
    char *cmpString = malloc(length + 1);
    cmpString[length] = '\0';
    for( i = 0; tempString[i] != '\0'; i++){
        if(tempString[i] != ';' && tempString[i] != ' '){
            tempString[j++] = tempString[i]; 
        }
    }
    // printf("string = %s\n" , tempString);
    // check if the search string exists
    for( i = 0; tempString[i] != '\0'; i++){
        if( count == length){
            if((strcmp( searchString , cmpString)) == 0) return true;
            count = 0;
        }else{
            cmpString[count] = tempString[i];
            count++;
        }
    }
    return false;
}

void print_found_keyword( char **lines , char *searchString){
    int count = 0;
    size_t length = strlen( searchString );
    char tempString[512];
    bool noneFound = true;
    int lineCount = 0;

    print_base_header();
    while(lines[count] != NULL){
        strncpy(tempString, lines[count], sizeof tempString - 1);
        tempString[sizeof tempString - 1] = '\0';
        bool truth = keyword_in_string( tempString , searchString , length ); 
        if((truth)){
            printf("%s" , lines[count]);
            noneFound = false;
            lineCount++;
        }
        count++;
    }
    // return to menu
    if((noneFound)){
        printf("\nFound no records containing %s\n" , searchString);
        printf("Press enter to return to menu: ");
        char buf[4];
        fgets( buf , sizeof(buf) , stdin);
        return;
    }else{
        printf("\nFound %d records containing %s\n", lineCount , searchString);
        printf("Press enter to return to menu: ");
        char buf[4];
        fgets( buf , sizeof(buf) , stdin);
        return;
    }
}

void search_record_byKeyword( char *csvFile){
    int rows = count_rows(csvFile);
    FILE *file = fopen( csvFile , "r");
    char buffer[1024];
    int arrayCount = 0;

    while(1){
        clear_buffer();
        printf("Enter the keyword you would like to search , type 0 if you would like to escape this option: ");
        char input[100];
        
        if(fgets( input , sizeof(input) , stdin)){
            // strip the new character
            input[strcspn(input, "\n")] = '\0';
            // quit if pressed 0
            if(strcmp(input , "0") == 0){
                clear_screen();
                return;
            }
            fgets( buffer , sizeof(buffer) , file); //  read the header and do nothing
            char **lines = malloc((size_t)rows * sizeof *lines);

            // add the strings to an array
            while((fgets( buffer , sizeof(buffer) , file))){
                lines[arrayCount] = malloc(strlen(buffer) + 1);
                strcpy(lines[arrayCount] , buffer);
                arrayCount++;
            }
            lines[arrayCount] == NULL;
            fclose(file);
            char *searchString = get_search_string( input );
            print_found_keyword( lines , searchString );
            clear_screen();
            return;
        }
    }
}

void print_found_record( char *string){
    clear_screen();
    printf("StudentID Name   BookID    Book Name\n\n");
    printf("%s\n" , string);
    printf("Press enter to return:");
    char buf[4];
    fgets( buf , sizeof(buf) , stdin);
    clear_buffer();
    clear_screen();
}

void search_record_byID( char *csvFile){
    while(1){
        printf("Enter the ID you would like to search , type 0 if you would like to escape this option: ");
        int searchNum = verify_choice();
        // quit option
        if( searchNum == 0 ){
            clear_screen();
            return;
        }
        if( int_length(searchNum) != 3 || searchNum < 0){
            printf("ID needs to be 3 digits long and all numbers\n\n");
            continue;
        }
        char IDstring[20];
        snprintf( IDstring , sizeof(IDstring) , "%d" , searchNum);
        char *string = id_exists( IDstring , csvFile );
        // check if the record even exists
        if(string == NULL){
            printf("Could not find %s in database\n" , IDstring);
            return;
        }
        size_t printedString_size = 512;
        char *printedString = malloc(printedString_size);
        // remove the semicolon and print it
        for(size_t i = 0; i < strlen(string) ; i++){
            if(string[i] == ';'){
                string[i] = '\t';
            }
            printedString[i] = string[i];
        }
        print_found_record( printedString );
        return;
    }
}

int search_menu(){
    printf("1) Would you like to search a record by student ID?\n");
    printf("2) Would you like to search a record by keyword\n");
    printf("3) Or Go Back to the Main Menu\n");
    printf("Please select from 1 or 3: ");
    int num = verify_choice();
    return num;
}

void search_record_main( char *csvFile ){
    clear_screen();
    printf("\n-------------Search Records-------------\n");
    while(1){
        int searchMenuOption = search_menu();
        if ( searchMenuOption >= 4 || searchMenuOption < 1){
            printf("Invalid, please enter a number between 1-2\n");
            continue;
        } // if (menuOption == -1)

        switch(searchMenuOption){
            case 1:
                search_record_byID( csvFile );
                break;
            case 2:
                search_record_byKeyword( csvFile );
                break;
            case 3:
                clear_screen();
                printf("\n-------------Library Books Management System-------------\n");
                return;
        }
    }
}