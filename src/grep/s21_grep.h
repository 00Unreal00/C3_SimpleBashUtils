#ifndef GREP_H
#define GREP_H

typedef struct {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
} GrepFlags;

void parse_grep_flags(int argc, char *argv[], GrepFlags *flags, char **pattern, char ***files, int *file_count);
void run_grep(GrepFlags *flags, const char *pattern, char **files, int file_count);

#endif