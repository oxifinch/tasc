#include <stdio.h>
#include "files.h"
#include "parsing.h"

/*
  Reads a file located at [file_path] and scans through it line by line. For each
  line, it calls the parse_task_line function, which searches the line for any known
  keyword that indicated that the line is a comment with a task.
    - TODO: Create a string list(or something) which puts all the parsed strings
            together so that they can be used by the other functions that create the
            tasklist and corresponding file.
*/
void read_source_file(char *file_path) {
    FILE *fp;
    fp = fopen(file_path, "r");
    if(fp == NULL) {
        // TODO: This should go to STDERR
        printf("ERROR: File %s could not be opened.\n", file_path);
    }

    // Scan file line by line
    unsigned int ln_num = 1;
    char line[MAX_LINE_LENGTH];
    while(fgets(line, sizeof(line), fp)) {
        //printf("%3d: %s", ln_num, line); // For debugging only
        ln_num++;
        char *parsed_str[MAX_LINE_LENGTH];
        int result = parse_task_line(line, *parsed_str);
        printf("%d: Result: %d\n", ln_num, result);
    }
}
