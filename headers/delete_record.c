/*
This will available for the user to delete a record
*/

// Libraries

#include <stdio.h>
#include <stdbool.h>
#include "general_functions.h"
#include "delete_record.h"

void delete_student_record( char *csvFile , int ID){
    // create the temp path to write to and get the row count
    char *tmpPath = create_tmp_path(csvFile);
    FILE *tmpFile = fopen( tmpPath, "a");
    int rows = find_ID_row( csvFile , ID );
    FILE *mainFile;
    int count = 0;
    char string[256];

    if((mainFile = fopen(csvFile, "r"))){
        while( fgets( string , sizeof(string) , mainFile) != NULL){
            count++;
            if( rows == count ){
                fputs(string , tmpFile );
                fgets( string , sizeof(string) , mainFile);
                continue;
            }else{
                fputs( string , tmpFile );
            }
        }
    }
    fclose(mainFile);
    fclose(tmpFile);
    printf("Record %d deleted" , ID);
    tmp_to_main( tmpPath , csvFile );
}

bool confirm_deletion( record Record){
    clear_screen();
    // confirm with user if they want to delete the record
    printf("Student Name --> %s\n" , Record.studentName);
    printf("Student ID --> %d\n" , Record.studentID);
    printf("Student Name --> %s\n" , Record.bookName);
    printf("Student Name --> %d\n" , Record.bookID);
    while(1){
        printf("Would you like to delete this record(y/n)?: ");
        int yORn = verify_char();
        if( yORn == 1) return true;
        if( yORn == 0) return false;
        printf("Please enter y or n");    
    }
}

void get_id( char *csvFile){
    // get the ID and confirm deletion
    clear_screen();
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
            continue;
        }
        // split the record for printing purposes
        record Record = split_record( string );
        bool delete = confirm_deletion( Record );
        // if yes delete the record
        if((delete)){
            clear_screen();
            print_line();
            delete_student_record( csvFile , searchNum );
            print_line();
            return;
        }else{
            clear_screen();
            return;
        }
    }
}

int delete_menu(){
    printf("1) Would you like to delete a record?\n");
    printf("2) Or Go Back to the Main Menu\n");
    printf("Please select from 1 or 2: ");
    int num = verify_choice();
    return num;
}


void delete_record_main( char * csvFile ){
    clear_screen();
    printf("\n-------------Delete Records-------------\n");
    while(1){
        int deleteMenuOption = delete_menu();
        if ( deleteMenuOption >= 3 || deleteMenuOption < 1){
            printf("Invalid, please enter a number between 1-2\n");
            continue;
        } // if (menuOption == -1)

        switch(deleteMenuOption){
            case 1:
                get_id( csvFile );
                break;
            case 2:
                clear_screen();
                printf("\n-------------Library Books Management System-------------\n");
                return;
        }
    }
}