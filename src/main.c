#include <stdio.h>

#include "files.h"

void show_help() {
    printf("Usage:\n");
    printf("    tasc FILE...\n");
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("ERROR: Please provide at least one file to operate on.\n");
        show_help();
        return 1;
    }

    read_source_file(argv[1]);

    return 0;
}
