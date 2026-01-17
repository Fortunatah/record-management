/*
help section is for users wondering what each tab is doing
*/

// libraries
#include <stdio.h>
#include "general_functions.h"

void delete_help_section(){
    printf("\nFor the delete section\n\tUser can search the whole database for record by ID");
    printf("\n\tIf ID exists the user will be able to delete the record");
    printf("\n\tIt will prompt the user for the confirmation before deleting the record");
}

void edit_help_section(){
    printf("\nFor the edit section\n\tUser can search the whole database for record by ID");
    printf("\n\tIf ID exists the user will be able to edit the record");
    printf("\n\tIt will prompt the user for the confirmation before deleting the record");
}

void search_help_section(){
    printf("\nFor the search section\n\tUser can search the whole database for by either keywords or IDs");
}

void view_help_section(){
    printf("\nFor the view section\n\tUser can view the whole file twenty lines at a time");
}

void add_help_section(){
    printf("\nFor the add section\n\tUser cannot input everything, there are strict parameters\n");
    printf("\tPress y at the end to write the record to the record management system");
}

void help_section(){
    clear_screen();
    print_line();
    printf("Follow the guidlines below for help");
    print_line();
    add_help_section();
    print_line();
    view_help_section();
    print_line();
    search_help_section();
    print_line();
    edit_help_section();
    print_line();
    delete_help_section();
    print_line();
    printf("Press enter to return to the main menu:");
    reset_buffer();
    getchar();
    clear_screen();
    return;
}