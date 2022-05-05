#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "grep.h"


void skip_arg(int *argc, char ***argv) {
    if (*argc) {
        (*argc)--;
        (*argv)++;
    }

}

int flags_parser(int *argc, char ***argv, FILE **pattern_file) {
    int flags = 0;

    short stop = 0;
    size_t type_arg;
    for (; !stop && *argc && (flags != -1) && (type_arg = strspn(**argv, "-")) > 0; skip_arg(argc, argv)) {
        (**argv) += type_arg;

        if (type_arg == 1) {
            if (!strcmp(**argv, "e")) {
                add_flag(flags, FLAG_E);
                stop = 1;
            } elif (!strcmp(**argv, "f")) {
                add_flag(flags, FLAG_F);
                (*argv)++;
                *pattern_file = fopen(**argv, "r");
                if (!*pattern_file) {
                    flags = -1;
                }
            } else {
                while (***argv) {
                    if (***argv == 'i') {
                        add_flag(flags, FLAG_I);
                    } elif (***argv == 'v') {
                        add_flag(flags, FLAG_V);
                    } elif (***argv == 'c') {
                        add_flag(flags, FLAG_C);
                    } elif (***argv == 'l') {
                        add_flag(flags, FLAG_L);
                    } elif (***argv == 'n') {
                        add_flag(flags, FLAG_N);
                    } elif (***argv == 'h') {
                        add_flag(flags, FLAG_H);
                    } elif (***argv == 's') {
                        add_flag(flags, FLAG_S);
                    } elif (***argv == 'o') {
                        add_flag(flags, FLAG_O);
                    } else {
                        flags = -1;
                    }
                    (**argv)++;
                }
            }
        } else {
            flags = -1;
        }
    }
    return flags;
}


void print_all_patterns_in_file(regex_t *regex, FILE *file, int flags) {
    regmatch_t pmatch;

    size_t size = 1;
    char *line = calloc(size, sizeof (char));

    short only_count_line = check_flag(flags, FLAG_C);
    short show_line = check_flag(flags, FLAG_N);
    size_t counter_line = 0;
    size_t counter = 0;

    if (line) {
        ssize_t len_line;

        short need_was = !check_flag(flags, FLAG_V);
        while ((len_line = getline(&line, &size, file)) > 0) {
            counter_line++;
            int offset = 0;
            short was = 0;
            while (offset < len_line) {
                int status = regexec(regex, line + offset, 1, &pmatch, 0);
                if(status == REG_NOMATCH) {
                    break;
                } elif (pmatch.rm_so != -1) {
                    was = 1;
                }
                offset += pmatch.rm_eo;
            }

            if (was == need_was) {
                counter++;

                if (show_line)
                    printf("%zu:%s", counter_line, line);
                elif (!only_count_line)
                    printf("%s", line);
            }
        }
        if (only_count_line)
            printf("%zu", counter);
        free(line);
    }
}

regex_t *get_pattern(int *argc, char ***argv, int flags) {
    regex_t *reg = NULL;

    if (*argc) {
        reg = malloc(sizeof (reg));

        if (reg) {
            int is_bad_res_comp = regcomp(reg, **argv, REG_ICASE * (check_flag(flags, FLAG_I)));

            if (is_bad_res_comp) {
                regfree(reg);
                free(reg);

                reg = NULL;
            }
        }

        skip_arg(argc, argv);
    }

    return reg;
}

int main(int argc, char **argv) {
    if (argc > 1) {
        // Skip name running file
        skip_arg(&argc, &argv);

        FILE *file;
        int flags = flags_parser(&argc, &argv, &file);

        if (flags == -1) {
            if (check_flag(flags, FLAG_F) && !file) {
                fprintf(stderr, "grep: %s: No such file or directory\n", *argv);
            } else {
                fprintf(stderr, "grep: illegal option <%s>\n", *argv);
            }
        } else {
            regex_t *regex = get_pattern(&argc, &argv, flags);

            if (regex) {
                for (; argc; skip_arg(&argc, &argv)) {
                    if (!strcmp(*argv, "-")) {
                        print_all_patterns_in_file(regex, stdin, flags);
                    } else {
                        FILE *file = fopen(*argv, "r");
                        if (file) {
                            print_all_patterns_in_file(regex, file, flags);
                            fclose(file);
                        } else {
                            fprintf(stderr, "grep: %s: No such file or directory\n", *argv);
                        }
                    }
                }
                regfree(regex);
                free(regex);
            }

            if (file)
                fclose(file);
        }
    }
    return 0;
}
