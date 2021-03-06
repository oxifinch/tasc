#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>

const int MAX_LINE_LENGTH  = 160;
const int MAX_LINE_STORAGE = 64;

void show_help();
bool find_task_line(const char *line, int line_length);
void trim_line(char *line, int max_len);

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

    FILE *fp;
    char current_line[MAX_LINE_LENGTH];
    char *line_list[MAX_LINE_STORAGE];
    int lines_found = 0;
    int line_number = 0;

    for(int i = 0; i < MAX_LINE_STORAGE; i++) {
        line_list[i] = (char*)malloc(MAX_LINE_LENGTH);
    }


    // Scanning each file
    for(int i = 1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if(fp == NULL) {
            printf("[ WARNING ] Could not open file: %s. Skipping...\n", argv[i]);
            continue;
        }

        // Line scanning loop
        bool was_one = false;
        while((fgets(current_line, MAX_LINE_LENGTH, fp)) != NULL) {
            // If a match is found, format the line and add it to the list
            if(find_task_line(current_line, strlen(current_line))) {
                trim_line(current_line, strlen(current_line));
                char *parsed_line = calloc(MAX_LINE_LENGTH, sizeof(char));

                // Really ugly/silly solution for offsetting only the first line in a
                // file by 1.
                if(line_number == 0) {
                    was_one = true;
                    line_number++;
                }

                snprintf(parsed_line, MAX_LINE_LENGTH, "- [ ] %s:%d | %s", argv[i], line_number, current_line);

                if(was_one) {
                    was_one = false;
                    line_number--;
                }

                // Adding the parsed line to the array and incrementing how many 
                // slots in the array are actually used. The number of found lines
                // also corresponds to the correct index in which to insert the
                // string, so I'll use that here.
                line_list[lines_found] = parsed_line;
                lines_found++;
            }
            line_number++;
        }

        line_number = 1;
        fclose(fp);
    }
    fp = NULL;

    if(lines_found < 1) {
        printf("Found and parsed %d TODO items.\n", lines_found);
        return 1;
    }

    // Writing the parsed lines to a new file
    fp = fopen("todo.md", "w+");
    if(fp == NULL) {
        printf("[ ERROR ] Could not open/create 'todo.md'. Abort.\n");
        return 1;
    }
    for(int i = 0; i < lines_found; i++) {
        fputs(line_list[i], fp);
    }

    // Closing files and freeing memory
    fclose(fp);
    fp = NULL;
    for(int i = 0; i < MAX_LINE_STORAGE; i++) {
        free(line_list[i]);
    }

    printf("Found and parsed %d TODO items.\n", lines_found);
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

void trim_line(char *line, int max_len) {
    char *token_str = (char*)calloc(6, sizeof(char));
    strncpy(token_str, "TODO", 5);

    if((strstr(line, "TODO")) == NULL) {
        strncpy(token_str, "todo", 5);
        if((strstr(line, "todo")) == NULL) {
            printf("[ ERROR ] Unable to validate TODO token. Aborting...\n");
            exit(-1);
        }
    }
    char *start = (strstr(line, token_str) + 4);
    free(token_str);

    // Move pointer one step forward if there is a : character
    if(start[0] == ':') {
        ++start;
    }

    // Use the same method to remove leading spaces
    while(isspace(start[0])) {
        ++start;
    }
    strncpy(line, start, max_len);
}
