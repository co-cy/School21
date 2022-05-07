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

void print_error(int flags) {
    if (!check_flag(flags, FLAG_S) && *error) {
        fputs(error, stderr);
    }
}

int parce_c2f(int *argc, char ***argv, FILE **pattern_file, int *flags) {
    int stop = 0;

    if (***argv == 'i') {
        add_flag(*flags, FLAG_I);
    } elif (***argv == 'v') {
        add_flag(*flags, FLAG_V);
    } elif (***argv == 'f') {
        add_flag(*flags, FLAG_F);
        if (!*(**argv++))
            skip_arg(argc, argv);
        if (*argc) {
            *pattern_file = fopen(**argv, "r");
            if (!*pattern_file) {
                sprintf(error, "grep: %s: No such file or directory", **argv);
            }
        } else {
            stop = 1;
        }
    } elif (***argv == 'e') {
        add_flag(*flags, FLAG_E);
        if (*(++(**argv))) {
            // revert skip
            (*argc)++;
            (*argv)--;
        }
        stop = 1;
    } elif (***argv == 'c') {
        add_flag(*flags, FLAG_C);
    } elif (***argv == 'l') {
        add_flag(*flags, FLAG_L);
    } elif (***argv == 'n') {
        add_flag(*flags, FLAG_N);
    } elif (***argv == 'h') {
        add_flag(*flags, FLAG_H);
    } elif (***argv == 's') {
        add_flag(*flags, FLAG_S);
    } elif (***argv == 'o') {
        add_flag(*flags, FLAG_O);
    } else {
        sprintf(error, "grep: invalid option -- %s", **argv);
    }

    return stop;
}


int flags_parser(int *argc, char ***argv, FILE **pattern_file) {
    int flags = 0;

    short stop = 0;
    size_t type_arg;
    for (; !stop && *argc && !(*error) && (type_arg = strspn(**argv, "-")) > 0; skip_arg(argc, argv)) {
        (**argv) += type_arg;

        if (type_arg == 1) {
            while (***argv) {
                stop = parce_c2f(argc, argv, pattern_file, &flags);
                if (stop)
                    break;
                (**argv)++;
            }
        } else {
            sprintf(error, "grep: unrecognized option '--%s'", **argv);
        }
    }
    return flags;
}

void print_line(char *filename, char *line, size_t counter_line, size_t only_count_line, int flags) {
    static short beaut_print = 0;
    short was_shift = 0;

    short stop = 0;

    if (!check_flag(flags, FLAG_C) && only_count_line == -1) {
        beaut_print = 1;

        if (check_flag(flags, FLAG_L)) {
            printf("%s", filename);
            stop = 1;
        } elif (check_flag(flags, FLAG_Z) && !check_flag(flags, FLAG_H)) {
            printf("%s:", filename);
        } elif (check_flag(flags, FLAG_N)) {
            printf("%zu:", counter_line);
        }

        if (!stop) {
            printf("%s", line);
        }
    } elif (check_flag(flags, FLAG_C) && only_count_line != -1) {
        printf("%zu", only_count_line);
    }
}


void print_all_patterns_in_file(regex_t **regex, char* filename, int flags) {
    FILE *file = fopen(filename, "r");
    if (file) {
        regmatch_t pmatch;

        size_t size = 1;
        char *line = calloc(size, sizeof(char));

        size_t counter_line = 0;
        size_t counter = 0;
        if (line) {
            ssize_t len_line;

            short need_was = !check_flag(flags, FLAG_V);
            while ((len_line = getline(&line, &size, file)) > 0) {
                counter_line++;

                short was = 0;
                for (regex_t **reg = regex; !was && *reg; reg++) {
                    int offset = 0;
                    while (offset < len_line) {
                        int status = regexec(*reg, line + offset, 1, &pmatch, 0);
                        if (status == REG_NOMATCH)
                            break;
                        elif (pmatch.rm_so != -1)
                            was = 1;
                        offset += pmatch.rm_eo;
                    }

                    if (was == need_was) {
                        print_line(filename, line, counter_line, -1, flags);
                        counter++;
                    }
                }
            }
            print_line(filename, line, -1, counter, flags);
            free(line);
        }
        fclose(file);
    } else {
        sprintf(error, "grep: %s: No such file or directory\n", filename);
        print_error(flags);
    }
}

regex_t *get_pattern(char *string, int flags) {
    regex_t *reg = malloc(sizeof (reg));

    if (reg) {
        int is_bad_res_comp = regcomp(reg, string, REG_ICASE * (check_flag(flags, FLAG_I)));

        if (is_bad_res_comp) {
            regfree(reg);
            free(reg);

            reg = NULL;
        }
    }
    return reg;
}

regex_t ** get_patterns_from_file(FILE *file, int flags) {
    size_t i = 0;
    size_t size = 2;
    regex_t **list_regex = calloc(2, sizeof(regex_t*));

    size_t size_line = 1;
    char *line = malloc(sizeof(char));
    size_t len_line;
    while ((len_line = getline(&line, &size_line, file)) > 0) {
        if ((size - 1) == i) {
            list_regex = realloc(list_regex, sizeof(regex_t) * (size *= 2));
        }
        line[len_line] = '\0';
        list_regex[i++] = get_pattern(line, flags);
    }
    list_regex[i] = NULL;

    return list_regex;
}

regex_t ** get_patterns_from_string(char *string, int flags) {
    regex_t **regex_list = calloc(2, sizeof(regex_t*));
    regex_list[0] = get_pattern(string, flags);
    return regex_list;
}

void aboba(int argc, char **argv, regex_t **regex, int flags) {
    if (argc > 1 && !check_flag(flags, FLAG_H)) {
        add_flag(flags, FLAG_Z);
    }
    for (; argc; skip_arg(&argc, &argv)) {
            print_all_patterns_in_file(regex, *argv, flags);
    }
}


// END h, L, f
// ostalsa s, o
int main(int argc, char **argv) {
    if (argc > 1) {
        // Skip name running file
        skip_arg(&argc, &argv);

        FILE *file;
        int flags = flags_parser(&argc, &argv, &file);

        if (!(*error)) {
            regex_t **regex;
            if (file) {
                regex = get_patterns_from_file(file, flags);
            } else {
                regex = get_patterns_from_string(*argv, flags);
                skip_arg(&argc, &argv);
            }

            if (*regex) {
                aboba(argc, argv, regex, flags);
                for (regex_t **a = regex; *a; a++) {
                    regfree(*a);
                    free(*a);
                }
                free(regex);
            }

            if (file)
                fclose(file);
        } else {
            print_error(flags);
        }
    }
    return 0;
}
