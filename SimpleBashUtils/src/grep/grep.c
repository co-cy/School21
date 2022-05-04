#include "headers/find_all_pattern_in_file.h"
#include "headers/flags_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc > 1) {
        argc--;
        argv++;

        FILE *file;
        int flags = flags_parser(&argc, &argv, &file);
        if (argc) {
            if (!file) {
                if (argc) {
                    char *template = *argv;
                    argv++;
                    argc--;

                    while (argc) {
                        if (!strncmp(*argv, "-", 1)) {
                            find_all_pattern_in_file(template, stdin, flags);
                        } else {
                            FILE *file = fopen(*argv, "r");
                            if (file) {
                                find_all_pattern_in_file(template, file, flags);
                                free(file);
                            } else {
                                fprintf(stderr, "grep: %s: No such file or directory\n", *argv);
                            }
                        }
                        argv++;
                        argc--;
                    }

                } else {
                    free(file);
                }
            }
        }
    } else if (argc == 1) {

    } else {

    }

    return 0;
}
