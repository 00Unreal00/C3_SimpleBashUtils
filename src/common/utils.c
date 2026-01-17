#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **read_file_lines(const char *filename, int *num_lines) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    char **lines = NULL;
    int count = 0;
    char buffer[4096];

    while (fgets(buffer, sizeof(buffer), file)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        char *line = malloc(len + 1);
        strcpy(line, buffer);

        char **tmp = realloc(lines, sizeof(char*) * (count + 1));
        if (!tmp) {
            free(line);
            for (int i = 0; i < count; i++) free(lines[i]);
            free(lines);
            fclose(file);
            return NULL;
        }
        lines = tmp;
        lines[count++] = line;
    }

    fclose(file);
    *num_lines = count;
    return lines;
}

void free_file_lines(char **lines, int num_lines) {
    for (int i = 0; i < num_lines; i++) {
        free(lines[i]);
    }
    free(lines);
}