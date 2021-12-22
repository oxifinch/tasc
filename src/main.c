#include <stdio.h>

#include "files.h"
#include "parsing.h"

void show_help() {
    printf("Usage:\n");
    printf("    tasc FILE...\n");
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("[ ERROR ] Please provide at least one file to operate on.\n");
        show_help();
        return 1;
    }

    char *str_list[100][MAX_LINE_LENGTH];

    // TODO: HELLO THERE!
    // todo: eat beans lmao
    read_source_file(argv[1], **str_list);

    return 0;
}
