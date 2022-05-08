//
// Created by Nana Daughterless on 5/7/22.
//

#include "../linked_list/linked_list.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include "grep.h"

void strip(char *string) {
    char *a;

    for (a = string; *a;) {
        a++;
    }

    while (a != string && *(--a) == '\n') {
        *a = '\0';
    }
}


void print_error(int type_error, char *message) {
    if (type_error == NO_FILE) {
        fprintf(stderr, "grep: %s: No such file or directory\n", message);
    } elif (type_error == BAD_FLAG) {
        fprintf(stderr, "grep: invalid option -- %c\n", *message);
    } elif (type_error == BAD_OPTION) {
        fprintf(stderr, "grep: unrecognized option `%s'\n", message);
    } elif (type_error == MORE_ARGUMENT) {
        if (*message == PATTERNS_FILE) {
            fprintf(stderr, "grep: option requires an argument -- f\n");
        } elif (*message == PATTERN) {
            fprintf(stderr, "grep: option requires an argument -- e\n");
        }
    } elif (type_error == EMPTY) {
        fprintf(stderr, "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] [-C[num]]\n"
                        "        [-e pattern] [-f file] [--binary-files=value] [--color=when]\n"
                        "        [--context[=num]] [--directories=action] [--label] [--line-buffered]\n"
                        "        [--null] [pattern] [file ...]\n");
    } elif (type_error == OTHER) {
        fprintf(stderr, "%s\n", message);
    }
}

int parsing_file_to_patterns(char *filename, linked_list_t *pattern, status_code_e status) {
    FILE *file = fopen(filename, "r");
    if (file) {
        size_t line_size = 1;
        char *line = calloc(line_size, sizeof(char));

        while (getline(&line, &line_size, file) > 0) {
            strip(line);

            char *copy_line = malloc(sizeof (char) * (strlen(line) + 1));
            strcpy(copy_line, line);
            add_to_linked_list(pattern, copy_line);
        }
        status = NOTHING;
        free(line);
    } else {
        print_error(NO_FILE, filename);
        status = ERROR;
    }
    return status;
}

int parsing_word(char *word, linked_list_t *files, linked_list_t *patterns, status_code_e status) {
    if (status == NOTHING) {
        add_to_linked_list(files, word);
    } elif (status == PATTERNS_FILE) {
        status = parsing_file_to_patterns(word, patterns, status);
    } elif (status == PATTERN) {
        add_to_linked_list(patterns, word);
        status = NOTHING;
    } else {
        print_error(OTHER, "WTF???");
        status = ERROR;
    }
    return status;
}


int parsing_flag(char *flag, linked_list_t *patterns, int *flags) {
    status_code_e status = NOTHING;

    char tmp;
    short flag_exit = 0;
    while (!flag_exit && (status == NOTHING) && *flag) {
        tmp = *flag;
//        printf("PARAM %c\n", *flag);

        if (tmp == 'i') {
            add_flag(*flags, FLAG_I);
        } elif (tmp == 'v') {
            add_flag(*flags, FLAG_V);
        } elif (tmp == 'f') {
            add_flag(*flags, FLAG_F);
            if (*(flag + 1))
                status = parsing_file_to_patterns((flag + 1), patterns, status);
            else
                status = PATTERNS_FILE;
            flag_exit = 1;
        } elif (tmp == 'e') {
            add_flag(*flags, FLAG_E);
            if (*(flag + 1))
                add_to_linked_list(patterns, (flag + 1));
            else
                status = PATTERN;
            flag_exit = 1;
        } elif (tmp == 'c') {
            add_flag(*flags, FLAG_C);
        } elif (tmp == 'l') {
            add_flag(*flags, FLAG_L);
        } elif (tmp == 'n') {
            add_flag(*flags, FLAG_N);
        } elif (tmp == 'h') {
            add_flag(*flags, FLAG_H);
        } elif (tmp == 's') {
            add_flag(*flags, FLAG_S);
        } elif (tmp == 'o') {
            add_flag(*flags, FLAG_O);
        } else {
            print_error(BAD_FLAG, &tmp);
            status = ERROR;
        }
        flag++;
    }
    return status;
}


int parsing_parameter(char *parameter, linked_list_t *files, linked_list_t *patterns, int *flags, status_code_e status) {
    if (!strcmp(parameter, "-")) {
        add_to_linked_list(files, parameter);
    } else {
        size_t type_parameter = strspn(parameter, "-");
        if (type_parameter == 0 || status != NOTHING) {
            status = parsing_word(parameter, files, patterns, status);
        } elif (type_parameter == 1) {
            status = parsing_flag(parameter + type_parameter, patterns, flags);
        } else {
            print_error(BAD_OPTION, parameter);
            status = ERROR;
        }
    }

    return status;
}

int parsing_argv(int argc, char **argv, linked_list_t *files, linked_list_t *patterns, int *flags, status_code_e status) {
    for (size_t i = 0; i < argc; i++) {
        char *parameter = argv[i];
        // flag or file or flag_(file-pattern)
//        printf("STATUS: %d\n", status);
        status = parsing_parameter(parameter, files, patterns, flags, status);
        if (status == ERROR) {
            break;
        }
    }

    if (status != NOTHING && status != ERROR) {
        print_error(MORE_ARGUMENT, (char *) &status);
        status = ERROR;
    } elif (status == NOTHING) {
        // TODO REFACTORY
        short a = !is_empty_linked_list(patterns);
        short b = !is_empty_linked_list(files);

        if (a) {
            if (b) {
                // pass
            } else {
                char *file = malloc(sizeof (char) * (1 + 1));
                strcpy(file, "-");
                add_to_linked_list(files, file);
            }
        } else {
            if (b) {
                add_to_linked_list(patterns, files->next_item->data);
                shift_linked_list(files);
                b = !is_empty_linked_list(files);
                if (!b) {
                    char *file = malloc(sizeof (char) * (1 + 1));
                    strcpy(file, "-");
                    add_to_linked_list(files, file);
                }
            } else {
                print_error(EMPTY, "");
                status = ERROR;
            }
        }
    }

    return status;
}

void compile_patterns(linked_list_t *patterns, int flags) {
    for (linked_list_t *a = patterns; a; a = a->next_item) {
        if (a->data) {
            char *pattern = a->data;

            regex_t *reg = malloc(sizeof (reg));
            int is_bad_res_comp = regcomp(reg, pattern, REG_ICASE * (check_flag(flags, FLAG_I)));

            if (!is_bad_res_comp) {
                a->data = reg;
            } else {
                regfree(reg);
                free(reg);
                a->data = NULL;
            }
//            TODO: FIX FREE
//            free(pattern);
        }
    }
}

void print_found_pattern(char *filename, char *line, int counter_line, int only_count_line, int flags) {
    if (!check_flag(flags, FLAG_C) && counter_line != -1 && !check_flag(flags, FLAG_O)) {
        strip(line);

        if (check_flag(flags, FLAG_L)) {
            printf("%s\n", filename);
        } else {
            if (check_flag(flags, FLAG_Z) && !check_flag(flags, FLAG_H)) {
                printf("%s:", filename);
            }
            if (check_flag(flags, FLAG_N)) {
                printf("%d:", counter_line);
            }
            printf("%s\n", line);
        }
    } elif (check_flag(flags, FLAG_C) && only_count_line != -1) {
        if (check_flag(flags, FLAG_Z) && !check_flag(flags, FLAG_H))
            printf("%s:", filename);
        printf("%d\n", only_count_line);
        if (only_count_line && check_flag(flags, FLAG_L)) {
            printf("%s\n", filename);
        }
    }
}


// TODO: REFACTOR THIS PARASHA
void parasha_print(char *filename, char *line, int n_byte, int counter_line, int flags) {
    if (check_flag(flags, FLAG_O) && !check_flag(flags, FLAG_C)) {
        static int last_counter_line = -1;

        if (last_counter_line != counter_line || (check_flag(flags, FLAG_V))) {
            if (check_flag(flags, FLAG_L)) {
                printf("%s\n", filename);
            } else {
                if (check_flag(flags, FLAG_Z) && !check_flag(flags, FLAG_H)) {
                    printf("%s:", filename);
                }
                if (check_flag(flags, FLAG_N)) {
                    printf("%d:", counter_line);
                }
            }
        }
        for (; n_byte; line++, n_byte--) {
            if (*line != '\n')
                putchar(*line);
        }
        putchar('\n');
        last_counter_line = counter_line;

    }
}

void search_patterns_in_file(linked_list_t *patterns, char *filename, int flags) {
    FILE *file;
    if (!strcmp(filename, "-"))
        file = stdin;
    else
        file = fopen(filename, "r");

    if (file) {
        regmatch_t reg_match;

        size_t line_size = 1;
        char *line = calloc(line_size, sizeof(char));

        size_t counter_line = 0;
        size_t counter = 0;
        if (line) {
            ssize_t len_line;

            short need_was = !check_flag(flags, FLAG_V);
            short flags_exit = 0;

            while (!flags_exit && (len_line = getline(&line, &line_size, file)) > 0) {
                counter_line++;

                short was = 0;
                for (linked_list_t *a = patterns; !flags_exit && !was && a; a = a->next_item) {
                    regex_t *reg = a->data;
                    if (reg) {
                        int offset = 0;
                        while (offset < len_line) {
                            int status = regexec(reg, line + offset, 1, &reg_match, 0);
                            if (status != 0) {
                                break;
                            } elif (reg_match.rm_so != -1) {
                                was = 1;
                                if (was == need_was)
                                    parasha_print(filename, line + offset + reg_match.rm_so, reg_match.rm_eo - reg_match.rm_so, counter_line, flags);
                            }

                            offset += reg_match.rm_eo;
                        }

                        if (was == need_was) {
                            if (check_flag(flags, FLAG_V)) {
                                parasha_print(filename, line, strlen(line), counter_line, flags);
                            }
                            print_found_pattern(filename, line, counter_line, -1, flags);
                            counter++;

                            if (check_flag(flags, FLAG_L)) {
                                flags_exit = 1;
                            }
                        }
                    }
                }
            }
            print_found_pattern(filename, line, -1, counter, flags);
            free(line);
        }
        fclose(file);
    } else {
        print_error(NO_FILE, filename);
    }
}

void search_patterns_in_files(linked_list_t* list_filenames, linked_list_t *list_pattern, int flags) {
    for (linked_list_t *f = list_filenames->next_item; f; f = f->next_item) {
        search_patterns_in_file(list_pattern, f->data, flags);
    }
}


int main(int argc, char **argv) {
    argc--, argv++;
    int flags;
    linked_list_t *list_filenames = linked_list(NULL);
    linked_list_t *list_pattern = linked_list(NULL);

    status_code_e status = parsing_argv(argc, argv, list_filenames, list_pattern, &flags, NOTHING);
    if (status != ERROR) {
        int i = 1;
        for (linked_list_t *f = list_filenames; f; f = f->next_item, i++) {
            if (f->data) {
//                printf("FILES %d: _%s_\n", i, (char *) f->data);
                if (i > 1) {
                    add_flag(flags, FLAG_Z);
                }
            } else {
                i--;
            }

        }
//        i = 1;
//        for (linked_list_t *p = list_pattern->next_item; p; p = p->next_item, i++) {
//            printf("PATTERNS %d: _%s_\n", i, (char *) p->data);
//        }
//        puts("\n\n_________RESULT_________");
        compile_patterns(list_pattern, flags);
        search_patterns_in_files(list_filenames, list_pattern, flags);
    }
}