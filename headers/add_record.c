#include <stdio.h>
#include "add_record.h"

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
                printf("Hello\n");
                break;
            case 2:
                clear_screen();
                printf("\n-------------Library Books Management System-------------\n");
                return;
        }
    }
}