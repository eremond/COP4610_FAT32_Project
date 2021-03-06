# COP 4610: Project 3

- Group members:
  - Emmanuel Gonzalez
  - John Sanchez
  - Andrew Stringfellow
  
## Problem Statement
A FAT32 shell-like program capable of interpreting a FAT32 file system image file.

## Archive Contents

Filename: `proj3_gonzalez_sanchez_stringfellow.tar`

```
.
├── README.md // Markdown file containing documentation of our implementation of the assignment.
├── Makefile // Compiles the source code into a binary.
├── main.c // Opens and parses the file system image and starts the main program.
├── program.h // Declarations of the shell utility.
├── program.c // Definitions of the shell utility which acts as a terminal and handles the user's commands.
├── utils.h // Declarations of utility functions.
├── utils.c // Functions for finding free directory entries, clusters, etc.
├── dirparse.h // Declarations for directory parsing/editing functions.
├── dirparse.c // Helper functions to edit/view directories / display contents.
├── parse.h // Declarations for string conversion functions.
├── parse.c // Converts between standard format strings and FAT32 style strings.
├── filetable.h // Declarations of the file allocation table and its helper functions.
├── filetable.c // Definitions of the file allocation table helper functions.
├── ls.h // Declaration of the ls built-in.
├── ls.c // Definition of the built-in which prints the directories.
├── size.h // Declaration of the size built-in.
├── size.c // Definition of the size built-in.
├── creat.h // Declarations of the creat and mkdir built-ins.
├── creat.c // Definitions of the built-ins which create a new file and directory.
├── cd.h // Declaration of the cd built-in.
├── cd.c // Definitions of the built-in which changes the current directory.
├── open.h // Declaration of the open and close built-ins.
├── open.c // Definitions of the built-ins which opens and closes the files for reading or writing.
├── rm.h // Declarations of the rm and rmdir built-ins.
├── rm.c // Definitions of the built-ins which delete a file and directory.
└── FATImage.h // Declarations of the FAT32 file system reserved region fields.
```

## Build Instructions
To build: `$ make`

To clean: `$ make clean`

To run: `$ FATprog.x (img file)`

## Known Bugs and Unfinished Portions
- The read and write built-ins have not been implemented.

## Division of Labor
Emmanuel Gonzalez    
• Working on Main/Shell Program    
• Working on ls built in    
• Working on Utility functions    
• Cd Built-In    
• Size Built-In    
    
June Sanchez    
• Working on Main/Shell Program    
• Working on Utility functions    
• File Allocation Table    
• mkdir/creat Built-Ins    
• Cd Built-In    
• File Allocation Table    
• Parsing functions for files/directories    
    
Andrew Stringfellow    
• Working On Main Shell Program    
• Info Built-In    
• Working on Utility functions    
• Open/Close Built-Ins    
• Cd Built-In    
