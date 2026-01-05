@echo off
gcc %CD%\record-management.c headers/add_record.c -I headers -o record-management.exe
