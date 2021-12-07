#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "parsing.h"

int find_pattern_index(char *substr, char *str) {
    int sub_ln = strlen(substr);
    int str_ln = strlen(str);

    int i;
    // Loop through str
    for(i = 0; i <= str_ln; i++) {
        int j;
        
        // Loop through substr
        for(j = 0; j < sub_ln; j++) {
            if(str[i + j] != substr[j]) {
                break;
            }
        }

        if(j == str_ln) {
            printf("Pattern found on index: %d\n", i);
            break;
        }
    }
    return i;
}

/*
   Reads [line](probably a line in a file), splits it up into tokens/words
   separated by whitespace, and compares each word to a list of known keywords that
   would indicate a task item. If any of the known keywords are found, the function
   copies the [line] into the [dest] string, and returns 1. Otherwise, the function
   returns 0 by default.
       - TODO: The function that finds a match should be decoupled from the actual
               parsing and formatting of the string that gets copied.
       - TODO: I get a segfault in some cases of calling this function, probably
               related to the strcpy call. 
*/
int parse_task_line(char *line, char *dest) {
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
                    strcpy(line, dest);
                    match_found = 1;
                    break;
                }
            }
        }
    }
    return match_found;
}
