# Record Management System (C)

## Overview

This project is a **command-line Record Management System written in C**, designed to practice **low-level programming concepts**, structured data handling, and defensive programming.

The program manages a collection of records (in this implementation: **library books**) and allows the user to **add, view, search, edit, and delete records** through a menu-driven interface.

Unlike simple calculator-style programs, this project maintains **program state** and works with **real structured data**, making it a transition from beginner to intermediate C programming.

---

## Features

* Menu-driven command-line interface
* Add new records with validation
* View all existing records
* Search records by field
* Edit existing records safely
* Delete records with confirmation
* Help menu describing usage
* Modular design using multiple `.c` and `.h` files
* CSV-backed data storage

---

## Data Persistence

Records are stored in a CSV file:

```
records/library-books.csv
```

This file acts as the **source of truth** for the dataset.

* Records are loaded from the CSV file at program startup
* Changes to records are reflected in the CSV file
* This design removes the need for a separate manual "Save" option

> **Design note:** Persistence is implicit and automatic. All record modifications are immediately reflected in the backing file.

---

## Project Structure

```
record-management/
├── record-management.c
├── build.bat
├── headers/
│   ├── add_record.c / .h
│   ├── delete_record.c / .h
│   ├── edit_record.c / .h
│   ├── search_record.c / .h
│   ├── view_record.c / .h
│   ├── general_functions.c / .h
│   ├── help.c / .h
├── records/
│   └── library-books.csv
```

Each major operation is implemented in its own module to encourage clean separation of concerns and maintainability.

---

## Compilation

### Linux / macOS

```bash
gcc -Wall -Wextra -Werror record-management.c headers/*.c -o record_manager
```

### Windows (MinGW)

build.bat

---

## Usage

Run the program from the command line:

```bash
./record_manager
```

### Windows

record_manager.exe

###

You will be presented with a menu that allows you to:

* Add a new record
* View records
* Search records
* Edit records
* Delete records
* Access help information
* Exit safely

All user input is validated to prevent crashes or undefined behavior.

---

## Learning Objectives

This project demonstrates and reinforces:

* Use of `struct` for data modeling
* Arrays of structured data
* Modular program design in C
* Defensive input validation
* Safe string handling
* File-backed program state
* CRUD-style system design

---

## Notes

* This project intentionally avoids higher-level abstractions to focus on **low-level reasoning**
* Emphasis is placed on **correctness, safety, and clarity**, not UI complexity

---

## Author

Hayden John Fortunata

---

## License

This project is for educational purposes.
