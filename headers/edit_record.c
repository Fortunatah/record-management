/*
edit_record.c
This sript will be to edit the record
*/

// LIBRARIES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "general_functions.h"
#include "edit_record.h"

record split_record( char *string){
    record existingRecord;
    int semiCount = 0;
    char tempString[1024];
    char studentID[512];
    char studentName[512];
    char bookID[512];
    char bookName[512];
    int i;
    int sID = 0 , sName = 0 , bID   = 0 , bName = 0; // index of records
    strcpy( tempString , string );
    for(i = 0; semiCount < 4; i++){
        if( string[i] == ';'){
            semiCount++;
            continue;
        }
        if(semiCount == 0){
            studentID[sID] = tempString[i];
            sID++;
        }else if( semiCount == 1 ){
            studentName[sName] = tempString[i];
            sName++;
        }else if( semiCount == 2 ){
            bookID[bID] = tempString[i];
            bID++;
        }else if( semiCount == 3 ){
            bookName[bName] = tempString[i];
            bName++;
        }
    }
    // null terminator and create record
    studentID[sID] = '\0';
    existingRecord.studentID = (int) strtol( studentID , NULL , 10);
    studentName[sName] = '\0';
    existingRecord.studentName = studentName;
    bookID[bID] = '\0';
    existingRecord.bookID = (int) strtol( bookID , NULL , 10);
    bookName[bName] = '\0';
    existingRecord.bookName = bookName;

    return existingRecord;
}

void verify_ID_exists( char *csvFile){
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
        record exisitngRecord = split_record( string );

    }
}


int edit_menu(){
    printf("1) Would you like to edit a record?\n");
    printf("2) Or Go Back to the Main Menu\n");
    printf("Please select from 1 or 2: ");
    int num = verify_choice();
    return num;
}


void edit_record_main( char * csvFile ){
    clear_screen();
    printf("\n-------------Edit Records-------------\n");
    while(1){
        int editMenuOption = edit_menu();
        if ( editMenuOption >= 3 || editMenuOption < 1){
            printf("Invalid, please enter a number between 1-2\n");
            continue;
        } // if (menuOption == -1)

        switch(editMenuOption){
            case 1:
                verify_ID_exists(csvFile);
                break;
            case 2:
                clear_screen();
                printf("\n-------------Library Books Management System-------------\n");
                return;
        }
    }
}