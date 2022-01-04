#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include <unistd.h>

const int MAX_LINE_LENGTH  = 160;
const int MAX_LINE_STORAGE = 64;

void show_help();
bool find_task_line(const char *line, int line_length);
void trim_line(char *line);

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
    int found_lines = 0;
    int line_number = 1;

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
        while((fgets(current_line, MAX_LINE_LENGTH, fp)) != NULL) {
            // If a match is found, format the line and add it to the list
            if(find_task_line(current_line, strlen(current_line))) {
                char *parsed_line = calloc(MAX_LINE_LENGTH, sizeof(char));
                snprintf(parsed_line, MAX_LINE_LENGTH, "- [ ] %s:%d | %s", argv[i], line_number, current_line);

                // Trimming the line before formatting
                char *start = (strstr(parsed_line, "TODO") + 4);
                for(int j = 0; j < strlen(parsed_line); j++) {
                    printf("%c", *(start + j));
                }
                printf("^ Check out this line! ^\n");
                sleep(1);

                // Adding the parsed line to the array and incrementing how many 
                // slots in the array are actually used. The number of found lines
                // also corresponds to the correct index in which to insert the
                // string, so I'll use that here.
                line_list[found_lines] = parsed_line;
                found_lines++;
            }
            line_number++;
        }

        line_number = 1;
        fclose(fp);
    }
    fp = NULL;

    // Writing the parsed lines to a new file
    fp = fopen("todo.md", "w+");
    if(fp == NULL) {
        printf("[ ERROR ] Could not open/create 'todo.md'. Abort.\n");
        return 1;
    }
    for(int i = 0; i < found_lines; i++) {
        fputs(line_list[i], fp);
    }


    // Closing files and freeing memory
    fclose(fp);
    fp = NULL;
    for(int i = 0; i < MAX_LINE_STORAGE; i++) {
        free(line_list[i]);
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

void trim_line(char *line) {

}
