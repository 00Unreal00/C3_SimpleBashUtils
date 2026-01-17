#ifndef CAT_H
#define CAT_H

typedef struct {
    int b;
    int e; 
    int n;
    int s;
    int t;
} CatFlags;

void parse_cat_flags(int argc, char *argv[], CatFlags *flags, char ***files, int *file_count);
void run_cat(CatFlags *flags, char **files, int file_count);

#endif