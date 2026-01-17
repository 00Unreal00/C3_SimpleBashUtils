#include "s21_cat.h"
#include "../common/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_cat_flags(int argc, char *argv[], CatFlags *flags, char ***files, int *file_count) {
    *file_count = 0;
    *files = malloc(sizeof(char*) * argc);
    flags->b = flags->e = flags->n = flags->s = flags->t = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (int j = 1; argv[i][j]; j++) {
                switch (argv[i][j]) {
                    case 'b': flags->b = 1; break;
                    case 'e': flags->e = 1; break;
                    case 'n': flags->n = 1; break;
                    case 's': flags->s = 1; break;
                    case 't': flags->t = 1; break;
                    default: break;
                }
            }
        } else {
            (*files)[(*file_count)++] = argv[i];
        }
    }
}

void run_cat(CatFlags *flags, char **files, int file_count) {
    for (int f = 0; f < file_count; f++) {
        int num_lines;
        char **lines = read_file_lines(files[f], &num_lines);
        if (!lines) {
            fprintf(stderr, "s21_cat: %s: No such file\n", files[f]);
            continue;
        }

        int line_number = 1;
        int prev_blank = 0;
        
        for (int i = 0; i < num_lines; i++) {
            int is_blank = (strlen(lines[i]) == 0);

            // Флаг -s: сжатие пустых строк
            if (flags->s && is_blank && prev_blank) {
                free(lines[i]);
                continue;
            }

            if (flags->b && !is_blank) {
                printf("%6d\t", line_number++);
            } else if (flags->n) {
                printf("%6d\t", line_number++);
            }


            for (char *c = lines[i]; *c; c++) {
                if (flags->t && *c == '\t') {
                    printf("^I");
                } else {
                    putchar(*c);
                }
            }
            
            if (flags->e) {
                printf("$");
            }
            
            putchar('\n');
            prev_blank = is_blank;
            free(lines[i]);
        }
        free(lines);
    }
}

int main(int argc, char *argv[]) {
    CatFlags flags;
    char **files;
    int file_count;

    parse_cat_flags(argc, argv, &flags, &files, &file_count);
    if (file_count == 0) {
        fprintf(stderr, "s21_cat: no input files\n");
        return 1;
    }

    run_cat(&flags, files, file_count);
    free(files);
    return 0;
}