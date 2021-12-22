/* 
                            == TASC: Tasc Scanner ==
--------------------------------------------------------------------------------
  For each file provided as an argument:
    - Open the file.
    - Scan through the file lines by line to find task items.
    - Create a new string for each task line and remove comment markers.
    - Format the string to include a checkbox, filename and line number.
    - Add the string(s) to the str_list. 
    - Close the file.
 
  When the str_list is finished, write to the file "todo.md" or create it if it
  doesn't exist. The begin writing to the file:
  
  For each string in the str_list:
    - Append string to file.
    - Check for errors.

  When all write operations are done, close the file. If any errors were
  encountered, report them. Then exit the program.
--------------------------------------------------------------------------------
*/

#include <stdio.h>

#include "files.h"
#include "parsing.h"

void show_help() {
    printf("Usage:\n");
    printf("    tasc FILE...\n");
}

int main(int argc, char *argv[]) {
    // Checking that at least one argument is provided
    if(argc < 2) {
        printf("[ ERROR ] Please provide at least one file to operate on.\n");
        show_help();
        return 1;
    }

    // The list of strings to save the tasks in
    char *str_list[100][MAX_LINE_LENGTH];

    // Some comments just for testing
    // TODO: HELLO THERE!
    // todo: eat beans lmao

    for(int i = 1; i < argc; i++) {
        read_source_file(argv[i], **str_list);
    }

    return 0;
}
