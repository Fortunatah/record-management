@echo off
gcc %CD%\record-management.c headers/*.c -I headers -o record-management.exe
