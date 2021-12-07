#ifndef PARSING_H
#define PARSING_H

#define MAX_LINE_LENGTH 250

int find_pattern_index(char *substr, char *str);
int parse_task_line(char *line, char *dest);

#endif
