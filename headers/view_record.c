/*
this will be for viewing the record in C
it will print 20 lines at a time
*/

// libraries

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "view_records.h"
#include "general_functions.h"


void print_header(){
    clear_screen();
    print_line();
    printf("\nStudent ID\t\t\tStudent Name\t\t\tBook ID\t\t\tBook Name\n\n");
}

void flush_buffer( int count , int rows){
    int num = rows - count;
    if( num > 21){
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
}

void print_record( char *csvFile){
    FILE *file;
    char buffer[1024];
    int count = 0;
    int character;
    int rows = count_rows( csvFile );

    // clear the screen and print the initial header
    clear_screen();
    print_header();
    if((file = fopen(csvFile , "r"))){
        fgets( buffer , sizeof(buffer) , file); // read the header and do nothing
        while(fgets( buffer , sizeof(buffer) , file)){ // loop the trough the file
            count++;
            if( count % 21 == 0){
                printf("\n\nCurrently displaying 20 records, press ENTER to see next 20");
                char buf[4];
                fgets( buf , sizeof(buf) , stdin);
                // if count is less than 21 do not flush the buffer
                flush_buffer( count , rows);
                print_header();
            } // if( count % 20 == 0)

            printf("%d." , count);
            for( int i = 0 ; i < strlen(buffer) ; i++){ // parse the string
                // for semicolons print a lot of tabs instead
                if( buffer[i] == ';'){
                    printf("\t\t\t\t");
                }else{
                    printf("%c" , buffer[i]);
                } // if( buffer[i] == ';')
            }
        }
        char buf[50];
        printf("\nPress ENTER to return to view menu:");
        fgets(buf , sizeof(buf) , stdin);
        fclose( file );
        clear_screen();
    }else{
        printf("Could not open file");
        return;
    } // if((file = fopen(csvFile , "r")))
}


int view_menu(){
    printf("1) Would you like to view the record?\n");
    printf("2) Or Go Back to the Main Menu\n");
    printf("Please select from 1 or 2: ");
    int num = verify_choice();
    return num;
}


void view_record_main( char * csvFile ){
    clear_screen();
    printf("\n-------------View Records-------------\n");
    while(1){
        int viewMenuOption = view_menu();
        if ( viewMenuOption >= 3 || viewMenuOption < 1){
            printf("Invalid, please enter a number between 1-2\n");
            continue;
        } // if (menuOption == -1)

        switch(viewMenuOption){
            case 1:
                print_record( csvFile );
                break;
            case 2:
                clear_screen();
                printf("\n-------------Library Books Management System-------------\n");
                return;
        }
    }
}