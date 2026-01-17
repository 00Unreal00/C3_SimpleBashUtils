#ifndef UTILS_H
#define UTILS_H

char **read_file_lines(const char *filename, int *num_lines);
void free_file_lines(char **lines, int num_lines);

#endif