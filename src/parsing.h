#ifndef PARSING_H
#define PARSING_H

#include <stdbool.h>

#define MAX_LINE_LENGTH 250

int find_pattern_index(char *substr, char *str);
bool verify_todo_item(char *line);

#endif
