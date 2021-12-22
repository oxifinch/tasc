#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "parsing.h"

/*
   Reads [line](probably a line in a file), splits it up into tokens/words
   separated by whitespace, and compares each word to a list of known keywords that
   would indicate a task item. If any of the known keywords are found, the function
   returns 1. Otherwise, the function returns 0 by default.
*/
bool verify_todo_item(char *line) {
    int match_found = 0;

    // TODO: Maybe these should be available outside of the function?
    char keywords[4][6] = {"TODO", "todo", "TODO:", "todo:"};
    char* word = strtok(line, " ");

    while(word != NULL) {
        word = strtok(NULL, " ");
        
        if(word != NULL) {
            bool result = 0;
            for(int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++) {
                if(strcmp(word, keywords[i]) == 0) {
                    match_found = 1;
                    break;
                }
            }
        }
    }
    return match_found;
}

/*
  Reads a line and returns a formatted representation of it with the line number and
  source file where it was found. It should look something like this:
  "- [ ] src/my-file.js:52 | Do the thing."
*/
void parse_task_line(char *buf, char *line, int ln_num, char src_file_name) {
    char task_str[MAX_LINE_LENGTH];
    snprintf(task_str, MAX_LINE_LENGTH, "- [ ] %s:%d | %s", &src_file_name, ln_num, line);
    strncpy(buf, task_str, sizeof(buf) - 1);
}
