#include <stdio.h>
#include <string.h>

char *parse_task_line(char *line) {
    // If TODO is found in line
    // Remove everything up to and including TODO, leave the rest
    // return the string

    //printf("LINE: %s", line);
    //char str[] = "// TODO: This is an example line.";

    char* word = strtok(line, " ");
    while(word != NULL) {
        printf("%s\n", word);
        word = strtok(NULL, " ");
        // TODO: Compare word with specified keyword, probably "TODO"
    }

    return "beans lmao";
}
