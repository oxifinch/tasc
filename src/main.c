#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>

const int MAX_LINE_LENGTH  = 160;
const int MAX_LINE_STORAGE = 100;

void show_help();
bool find_task_line(const char *line, int line_length);

/*
                            == TASC: Task Scanner ==
   This program takes one or more files as an argument, and scans through them to
   look for lines that contain the word TODO. It then takes these lines and formats
   them into strings that contains the line number and file name, and writes these
   newly formatted lines into another file called todo.md.

   Main function:
       - Check for arguments (files).
       - For each argument, scan for TODO lines.
           - For each line, format and append to a list
           - When all lines are scanned, close the file
       - When all files are done, open/create todo.md and write lines to it.

   Other functions:
       - find_task_line: Looks through a line to see if it contains the word TODO, 
         both in uppercase or lowercase, and returns 1 or 0.
       - 
*/

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("[ ERROR ] Please provide at least one file as an argument!\n");
        show_help();
    }

    // File pointer declared here, as it will be reused
    FILE *fp;
    char current_line[MAX_LINE_LENGTH];
    char *parsed_lines[MAX_LINE_STORAGE];
    int line_number = 1;

    // Handling each file one by one
    for(int i = 1; i < argc; i++) {
        printf("File: %s\n", argv[i]);
        fp = fopen(argv[i], "r");
        if(fp == NULL) {
            printf("[ WARNING ] Could not open file: %s. Skipping...\n", argv[i]);
            continue;
        }

        // Line scanning loop
        while((fgets(current_line, MAX_LINE_LENGTH, fp)) != NULL) {
            //printf("%3d: %s", line_number, current_line); // DEBUGGING
            line_number++;
            if(find_task_line(current_line, strlen(current_line))) {
                //printf("Found a match on line %d\n", line_number); // DEBUGGING
            }
        }

        fclose(fp);
    }

    return 0;
}

// ----------------------------------------------------------------------------

void show_help() {
    printf("Usage: tasc FILE...\n");
}

bool find_task_line(const char *line, int line_length) {
    bool result = false;
    // Copying the string to make an uppercase conversion
    char *copy = calloc(line_length, sizeof(char));
    strncpy(copy, line, line_length);
    
    for(int i = 0; i < line_length; i++) {
        *(copy + i) = toupper(*(copy + i));
    }

    if(strstr(copy, "TODO") != NULL) {
        result = true;
    }

    free(copy);
    return result;
}
