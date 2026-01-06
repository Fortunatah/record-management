/*
record-management.c
Library Record Management system by Hayden Fortunata
This will be the main file in which my record system runs
*/

// LIBRARIES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "headers\add_record.h"
#include "headers\general_functions.h"


// FUNCTIONS

// General Functions

FILE copy_and_create_csv( const char *dir  , const char *recordFile){
    // check if file exists, if so copy it and create new, if not create new
    FILE *file;
    char bkup_path[512];
    int character;

    // if  corrupted file exists create a backup
    // else create the file
    if((file = fopen(recordFile , "r"))){
        snprintf(bkup_path , sizeof(bkup_path) ,"%s%s" , dir , "records/library-books.bak");
        FILE *bak = fopen( bkup_path , "w");
        while( (character = fgetc(file)) != EOF){
            fputc( character , bak);
        }
        // close the files and remove the corrupted
        fclose(file);
        fclose(bak);
        printf("Removed corrupted file %s\n" , recordFile);
        printf("Created backup file at the location: %s\n" , bkup_path);
    }
    if(!(file = fopen(recordFile , "w+"))){
        perror("File creation failed!!\n");
        exit(EXIT_FAILURE);
    }else{
        fprintf(file, "studentID; studentName; bookID; bookTitle;");
    }
    fclose(file);

} //copy_and_create_csv()

bool check_corruption(const char *path){
    FILE *file = fopen( path , "r");
    if(!file) return false;
    
    char line[1024]; // most amount of linegenerally
    int cols = -1;

    // Check for null/binary garbage
    while( fgets( line , sizeof(line) , file)){
        for (size_t i = 0 ; i < strlen(line) ; i++){
            if( line[i] == '\0'){
                fclose(file);
                return false;
            }  // if( line[i] == '\0')
        } //for (size_t i = 0 ; i < strlen(line) , i++)

    } // while( fgets( line , sizeof(line) , file))

    line[strcspn(line, "\n")] = 0;

    // Validate Column count
    int count = 1;
    for (size_t i = 0; i < strlen(line); i++) {
        if (line[i] == ';') count++;
    } // for (size_t i = 0; i < strlen(line); i++)

        // Set column count based on first valid row
    if (cols == -1) cols = count;

    // Validate consistent column count
    if (count != cols || count != 5) {
        fclose(file);
        return false;
    }

    // Check for unclosed quotes
    bool in_quotes = false;
    for(size_t i = 0; i < strlen(line) ; i++){
        if(line[i] = '"') in_quotes =  !in_quotes;
    } //for(size_t i = 0; i < strlen(line) ; i++)
    if (in_quotes){
        fclose(file);
        return false;
    }

    //if no valid lines, could be corrupt
    if (cols == -1) {
        fclose(file);
        return false;
    }
    return true;
} // bool check_corruption()

char * check_record_file(){
    // In order to get the correct dir, we need to remove record-management.c from 
    // the dir string

    const char *file = __FILE__; // this will grab the current file we are running this in
    int fileLength = strlen(file);
    
    // dynaimically set our files
    size_t dirSize = 512;
    char *dir = malloc(dirSize);
    char main_csv[512];
    
    // get rid of record-management from file name
    int end = fileLength - 19; // record-management.c is 19 characters long
    for( int i = 0; i < end; i++){
        dir[i] = file[i];
    } // for( int i = 0; i < 19; i++)

    snprintf(main_csv,  sizeof(main_csv) , "%s%s" , dir ,  "records/library-books.csv");
    bool validFile = check_corruption(main_csv);
    if(!validFile){
        copy_and_create_csv( dir , main_csv );
    }
    char * location = malloc(sizeof(main_csv));
    strcpy(location , main_csv);
    // return the CSV file after check
    return location;

} // FILE check_record_file()


// Main Menu 
int menu(){
    int num;
    printf("1. Add record\n");
    printf("2. View all records\n");
    printf("3. Search records\n");
    printf("4. Edit record\n");
    printf("5. Delete record\n");
    printf("6. Save records\n");
    printf("7. Load records\n");
    printf("8. Help\n");
    printf("9. Quit\n");
    printf("Please enter in a number 1-9: ");
    num = verify_choice();
    return num;
} // int menu;

int main(){
    clear_screen();
    char * csvFile = check_record_file();
    printf("\n-------------Library Books Management System-------------\n");
    while(1){
    int menuOption = menu();
    if ( menuOption >= 10 || menuOption < 1){
            printf("Invalid, please enter a number between 1-9\n");
            continue;
        } // if (menuOption == -1)
    
    switch(menuOption){
        case 1:
            add_record_main();
            break;
        case 2:
            printf("view");
            break;
        case 3:
            printf("search");
            break;
        case 4:
            printf("edit");
            break;
        case 5:
            printf("delete");
            break;
        case 6:
            printf("save");
            break;
        case 7:
            printf("load");
            break;
        case 8:
            printf("help");
            break;
        case 9:
            return 0;
        
        } // switch(menuOption)
    } // while(1)

} // main