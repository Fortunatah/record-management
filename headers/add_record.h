#ifndef ADD_RECORD_H
#define ADD_RECORD_H

#include <stdio.h>

void add_record_main();
void clear_screen();
int verify_choice();
typedef struct{
    int studentID;;
    char studentName[512];
    int bookID;
    char bookTitle[512];
} Record;

#endif