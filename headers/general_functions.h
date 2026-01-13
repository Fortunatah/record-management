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
int count_rows(char *fileName);
void print_line();
int verify_char();


typedef struct{
    int studentID;
    char * studentName;
    int bookID;
    char * bookName;
} record;

void write_to_csv(char *fileName , record Record , int cols); 
char * create_tmp_path(char * fileName);
void temp_to_main( char *tmpFile , char *mainFile);
char *id_exists( char *ID , char *csvFile);

#endif