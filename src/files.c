#include <stdio.h>
#include "files.h"

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
        // TODO: Find task items here
    }

}
