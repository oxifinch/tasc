#ifndef PARSING_H
#define PARSING_H

#include <stdbool.h>

#define MAX_LINE_LENGTH 250

bool verify_todo_item(char *line);
void parse_task_line(char *buf, char *line, int ln_num, char src_file_name);
char *parse_todo_item(char* line, int ln_num, char *src_file_name);

#endif
