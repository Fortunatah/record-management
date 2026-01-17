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

bool confirm_edit( record oldRecord , record newRecord){
    clear_screen();
    // confirm with user if they want to edit
    printf("Old Record Student ID: %d <---> New Record Student ID: %d\n" , oldRecord.studentID , newRecord.studentID);
    printf("Old Record Student Name: %s <---> New Record Student Name: %s\n" , oldRecord.studentName , newRecord.studentName);
    printf("Old Record Book ID: %d <---> New Record Book ID: %d\n" , oldRecord.bookID , newRecord.bookID);
    printf("Old Record Book Name: %s <---> New Record Book Name: %s\n" , oldRecord.bookName , newRecord.bookName);
    while(1){
        printf("Would you like to confirm these edits(y/n)?: ");
        int yORn = verify_char();
        if( yORn == 1) return true;
        if( yORn == 0) return false;
        printf("Please enter y or n");    
    }
}

void prompt_for_edit(char *csvFile , record existingRecord , int rows){
    int edit = 0;
    clear_screen();
    printf("\nFollow the process to edit the record, at the end it will prompt you to confirm the edit\n");
    while(1){
        record oldRecord = existingRecord;
        record newRecord;

        // First grab the student ID
        printf("Student ID is currently %d, would you like to edit it(y/n)?: ", oldRecord.studentID);
        edit = verify_char();
        if(edit == 1){
            printf("Please enter in the new 3 digit student ID: ");
            int tempStudentID = verify_choice();
            reset_buffer();
            if( tempStudentID < 1 || int_length(tempStudentID) <=2 ){
                printf("Student ID needs to be 3 digits long and all numbers\n");
                continue;
            }
            // check if ID exists
            char ID[4];
            sprintf( ID , "%d" , tempStudentID);
            if((id_exists( ID , csvFile)) != NULL){
            printf("ID %s is already in Database\n" , ID);
            continue;
            }
            // if all passes put entered ID as studentID 
            newRecord.studentID = tempStudentID;
        }else if(edit == 0){
            newRecord.studentID = oldRecord.studentID;
        }else{
            continue;
        }

        // Student Name
        printf("\nStudent Name is currently %s, would you like to edit it(y/n)?: ", oldRecord.studentName);
        edit = verify_char();
        if(edit == 1){
            // Student's Name
            printf("Please enter in student's name: ");
            char *tempName = verify_string();
            if(tempName == NULL){
                printf("Please enter name with no numbers\n");
                continue;
            }
            newRecord.studentName = tempName;
        }else if(edit == 0){
            newRecord.studentName = oldRecord.studentName;
        }else{
            continue;
        }

        // Book ID
        printf("Book ID is currently %d, would you like to edit it(y/n)?: ", oldRecord.bookID);
        edit = verify_char();
        if(edit == 1){
            printf("Please enter in the new 5 digit book ID: ");
            int tempbookID = verify_choice();
            reset_buffer();
            if( tempbookID < 1 || int_length(tempbookID) != 5 ){
                printf("Book ID needs to be 5 digits long and all numbers\n");
                continue;
            }
            // if all passes put entered ID as studentID 
            newRecord.bookID = tempbookID;
        }else if(edit == 0){
            newRecord.bookID = oldRecord.bookID;
        }else{
            continue;
        }

        // Student Name
        printf("\nThe title of the book is currently %s, would you like to edit it(y/n)?: ", oldRecord.bookName);
        edit = verify_char();
        if(edit == 1){
            // Student's Name
            printf("Please enter in the title of the book: ");
            char *tempbookName = verify_string();
            if(tempbookName == NULL){
                printf("Please enter name with no numbers\n");
                continue;
            }
            newRecord.bookName = _strdup(tempbookName);
        }else if(edit == 0){
            newRecord.bookName = oldRecord.bookName;
        }else{
            continue;
        }
        
        bool rewriteRecord = confirm_edit( oldRecord , newRecord);
        if((rewriteRecord)){
            clear_screen();
            write_to_csv( csvFile , newRecord , rows ); 
            return;
        }else{
            clear_screen();
            return;
        }
        
    }
}

void verify_ID_exists( char *csvFile){
    int edit;
    while(1){
        printf("Enter the ID you would like to search , type 0 if you would like to escape this option: ");
        int searchNum = verify_choice();
        reset_buffer();
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
        record existingRecord = split_record( string );
        int rows = find_ID_row( csvFile , existingRecord.studentID);

        // prompt if they want to edit
        printf("Would you like to edit studentID: %d's record?(y/n): " , existingRecord.studentID);
        int edit = verify_char();
        if(edit == 1){
            prompt_for_edit(csvFile , existingRecord , rows );
            return;
        }else if(edit == 0){
            return;
        }

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