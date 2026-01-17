#include "s21_grep.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <locale.h>

void parse_grep_flags(int argc, char *argv[], GrepFlags *flags, char **pattern, char ***files, int *file_count) {
    *file_count = 0;
    *files = malloc(sizeof(char*) * argc);
    flags->e = flags->i = flags->v = flags->c = flags->l = flags->n = 0;
    *pattern = NULL;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (int j = 1; argv[i][j]; j++) {
                switch (argv[i][j]) {
                    case 'e': flags->e = 1; break;
                    case 'i': flags->i = 1; break;
                    case 'v': flags->v = 1; break;
                    case 'c': flags->c = 1; break;
                    case 'l': flags->l = 1; break;
                    case 'n': flags->n = 1; break;
                    default: break;
                }
            }
        } else if (!*pattern) {
            *pattern = argv[i];
        } else {
            (*files)[(*file_count)++] = argv[i];
        }
    }
}

void run_grep(GrepFlags *flags, const char *pattern, char **files, int file_count) {
    if (!pattern) {
        fprintf(stderr, "s21_grep: no pattern\n");
        return;
    }

    setlocale(LC_ALL, "en_US.UTF-8");

    regex_t regex;
    int cflags = REG_EXTENDED;
    if (flags->i) cflags |= REG_ICASE;

    if (regcomp(&regex, pattern, cflags) != 0) {
        fprintf(stderr, "s21_grep: invalid regex\n");
        return;
    }

    for (int f = 0; f < file_count; f++) {
        FILE *file = fopen(files[f], "r");
        if (!file) {
            fprintf(stderr, "s21_grep: %s: No such file\n", files[f]);
            continue;
        }

        char buffer[4096];
        int line_number = 1;
        int match_count = 0;
        int file_has_match = 0;

        while (fgets(buffer, sizeof(buffer), file)) {

            char original[4096];
            strcpy(original, buffer);

            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            }

            int ret = regexec(&regex, buffer, 0, NULL, 0);
            int matched = (ret == 0);
            if (flags->v) matched = !matched;

            if (matched) {
                match_count++;
                file_has_match = 1;

                if (!flags->l && !flags->c) {
                    if (file_count > 1) {
                        printf("%s:", files[f]);
                    }
                    if (flags->n) {
                        printf("%d:", line_number);
                    }
                    printf("%s", original);
                    if (original[strlen(original) - 1] != '\n') {
                        printf("\n");
                    }
                }
            }
            line_number++;
        }

        fclose(file);

        if (flags->c) {
            if (file_count > 1) {
                printf("%s:", files[f]);
            }
            printf("%d\n", match_count);
        }

        if (flags->l && file_has_match) {
            printf("%s\n", files[f]);
        }
    }

    regfree(&regex);
}

int main(int argc, char *argv[]) {
    GrepFlags flags;
    char *pattern;
    char **files;
    int file_count;

    parse_grep_flags(argc, argv, &flags, &pattern, &files, &file_count);
    if (file_count == 0) {
        fprintf(stderr, "s21_grep: no input files\n");
        free(files);
        return 1;
    }

    run_grep(&flags, pattern, files, file_count);
    free(files);
    return 0;
}