/*
This will be the add record script
Here the user can add library records and students IDs
*/


// Functions
#include <stdio.h>
#include <string.h>
#include "add_record.h"
#include "general_functions.h"

int prompt_for_record(record Record){
    printf("\nFollow the process to add the record, at the end it will prompt you to confirm the writing of it\n");
    while(1){
        // First grab the student ID
        printf("Please enter in 3 digit student ID: ");
        int tempStudentName = verify_choice();
        if( tempStudentName < 1 || int_length(tempStudentName) <=2){
            printf("ID needs to be 3 digits long and all numbers\n");
            continue;
        }
        // if all passes put entered ID as studentID 
        Record.studentID = tempStudentName;
        
        // Student's Name
        printf("Please enter in student's name: ");
        char *tempName = verify_string();
        if(tempName == NULL){
            printf("Please enter name with no numbers\n");
            continue;
        }
        // if all passes put entered name as Student Name
        Record.studentName = tempName;

        // First grab the student ID
        printf("Please enter in 5 digit Book ID: ");
        int tempBookID = verify_choice();
        if( tempBookID < 1 || int_length(tempBookID) <=4){
            printf("Book ID needs to be 5 digits long and all numbers\n");
            continue;
        }
        // if all passes put entered ID as studentID 
        Record.bookID = tempBookID;

        // Student's Name
        printf("Please enter in the title of the book: ");
        char *tempTitle = verify_string();
        if(tempTitle == NULL){
            printf("Please enter name with no numbers\n");
            continue;
        }
        // if all passes put entered name as Student Name
        Record.studentName = tempTitle;
    }
}

int add_menu(){
    printf("1) Would you like to add a record?\n");
    printf("2) Or Go Back  to the Main Menu\n");
    printf("Please select from 1 or 2: ");
    int num = verify_choice();
    return num;
}

void add_record_main(){
    clear_screen();
    printf("\n-------------Add Records-------------\n");
    while(1){
        int addMenuOption = add_menu();
        if ( addMenuOption >= 3 || addMenuOption < 1){
            printf("Invalid, please enter a number between 1-2\n");
            continue;
        } // if (menuOption == -1)

        switch(addMenuOption){
            case 1:
                record Record;
                prompt_for_record( Record );
                break;
            case 2:
                clear_screen();
                printf("\n-------------Library Books Management System-------------\n");
                return;
        }
    }
}