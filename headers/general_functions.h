/*
This will be for my reused functions
makes it cleaner and easier to access
*/
#ifndef GENERAL_FUNCTIONS_H
#define GENERAL_FUNCTIONS_H

void clear_screen();
int verify_choice();
char * verify_string();
int int_length( int num );
int count_columns(char *fileName);
void print_line();
int verify_char();

typedef struct{
    int studentID;
    char * studentName;
    int bookID;
    char * bookName;
} record;

void write_to_csv(char *fileName , record Record); 

#endif