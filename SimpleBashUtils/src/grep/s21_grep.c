//
// Created by Nana Daughterless on 5/7/22.
//

#include "s21_grep.h"



linked_list_t *linked_list(void *data) {
    linked_list_t *new_list = calloc(1, sizeof(linked_list_t));
    if (new_list) {
        new_list->data = data;
        new_list->next_item = NULL;
    }
    return new_list;
}


void add_to_linked_list(linked_list_t *list, void *data) {
    while (list->next_item) {
        list = list->next_item;
    }
    list->next_item = linked_list(data);
}


void free_linked_list(linked_list_t *list) {
    linked_list_t *tmp;
    while (list) {
        if (list->data) {
            free(list->data);
        }
        tmp = list->next_item;
        free(list);
        list = tmp;
    }
}


int is_empty_linked_list(linked_list_t *list) {
    return !list->next_item && !list->data;
}

void *shift_linked_list(linked_list_t *list) {
    linked_list_t *tmp = list->next_item;
    void *tmp_data = NULL;

    if (tmp) {
        tmp_data = tmp->data;
        list->next_item = tmp->next_item;
        free(tmp);
    }

    return tmp_data;
}


char *strip(char *string) {
    char *a = string;

    for (; *a; a++)
        continue;

    while (a != string && *(--a) == '\n') {
        *a = '\0';
    }
    return string;
}


char *new_strcpy(char *string) {
    char *new_string = calloc(strlen(string) + 1, sizeof(char));
    return strcpy(new_string, string);
}


void print_error(int type_error, char *message, int need_print) {
    static int saved_need_print = 1;

    if (need_print >= 0 && need_print <= 1) {
        saved_need_print = need_print;
    }
    if (saved_need_print) {
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
        } elif (type_error == SET_SETTINGS) {
            // pass
        }
    }
}

int parsing_file_to_patterns(char *filename, linked_list_t *pattern, status_code_e status) {
    FILE *file = fopen(filename, "r");
    if (file) {
        size_t line_size = 1;
        char *line = calloc(line_size, sizeof(char));

        while (getline(&line, &line_size, file) > 0)
            add_to_linked_list(pattern, new_strcpy(strip(line)));
        status = NOTHING;
        free(line);
        fclose(file);
    } else {
        print_error(NO_FILE, filename, -1);
        status = ERROR;
    }
    return status;
}

int parsing_word(char *word, linked_list_t *files, linked_list_t *patterns, status_code_e status) {
    if (status == NOTHING) {
        add_to_linked_list(files, new_strcpy(word));
    } elif (status == PATTERNS_FILE) {
        status = parsing_file_to_patterns(word, patterns, status);
    } elif (status == PATTERN) {
        add_to_linked_list(patterns, new_strcpy(word));
        status = NOTHING;
    } else {
        print_error(OTHER, "WTF???", -1);
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
                add_to_linked_list(patterns, new_strcpy((flag + 1)));
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
            print_error(BAD_FLAG, &tmp, -1);
            status = ERROR;
        }
        flag++;
    }
    return status;
}


int
parsing_parameter(char *parameter, linked_list_t *files, linked_list_t *patterns, int *flags,
                  status_code_e status) {
    if (!strcmp(parameter, "-")) {
        add_to_linked_list(files, new_strcpy(parameter));
    } else {
        size_t type_parameter = strspn(parameter, "-");
        if (type_parameter == 0 || status != NOTHING) {
            status = parsing_word(parameter, files, patterns, status);
        } elif (type_parameter == 1) {
            status = parsing_flag(parameter + type_parameter, patterns, flags);
        } else {
            print_error(BAD_OPTION, parameter, -1);
            status = ERROR;
        }
    }

    return status;
}

int
parsing_argv(int argc, char **argv, linked_list_t *files, linked_list_t *patterns, int *flags,
             status_code_e status) {
    for (int i = 0; i < argc; i++) {
        char *parameter = argv[i];

        status = parsing_parameter(parameter, files, patterns, flags, status);
        if (status == ERROR) {
            break;
        }
    }

    if (status != NOTHING && status != ERROR) {
        print_error(MORE_ARGUMENT, (char *) &status, -1);
        status = ERROR;
    } elif (status == NOTHING) {
        int have_pattern = !is_empty_linked_list(patterns);
        int have_files = !is_empty_linked_list(files);

        if (have_pattern) {
            if (!have_files)
                add_to_linked_list(files, new_strcpy(stdin_file));
        } else {
            if (have_files) {
                add_to_linked_list(patterns, new_strcpy(files->next_item->data));
                free(shift_linked_list(files));
                have_files = !is_empty_linked_list(files);
                if (!have_files)
                    add_to_linked_list(files, new_strcpy(stdin_file));
            } else {
                print_error(EMPTY, "", -1);
                status = ERROR;
            }
        }
    }

    return status;
}

void compile_patterns(linked_list_t *patterns, int flags) {
    for (linked_list_t *a = patterns; a; a = a->next_item) {
        if (a->data) {
            if (!strlen(a->data) || !strcmp(a->data, "."))
                is_point = 1;
        }
    }
    if (!is_point) {
        for (linked_list_t *a = patterns; a; a = a->next_item) {
            if (a->data) {
                char *pattern = a->data;

                regex_t *reg = calloc(1, sizeof(regex_t));
                int is_bad_res_comp;
                if (strlen(pattern)) {
                    is_bad_res_comp = regcomp(reg, pattern, REG_ICASE * (check_flag(flags, FLAG_I) > 0));
                } else {
                    is_bad_res_comp = regcomp(reg, ".", REG_ICASE * (check_flag(flags, FLAG_I) > 0));
                }

                if (!is_bad_res_comp) {
                    a->data = reg;
                } else {
                    regfree(reg);
                    free(reg);
                    a->data = NULL;
                }
                free(pattern);
            }
        }
    }
}

void print_found_pattern(char *filename, char *line, int len, int lines_number, int amount_lines_found,
                         int ind_pattern,
                         int flags) {
    if (check_flag(flags, FLAG_O) && ind_pattern > 1) {
        if (len == -1) {
            printf("%s\n", line);
        } else {
            for (int i = 0; len; len--, i++) {
                putchar(line[i]);
            }
            putchar('\n');
        }
    } else {
        if (check_flag(flags, FLAG_Z) &&
            (check_flag(flags, FLAG_C) || !check_flag(flags, FLAG_L)) && !check_flag(flags, FLAG_H)) {
            printf("%s:", filename);
        }

        if (check_flag(flags, FLAG_C)) {
            printf("%d\n", amount_lines_found);
        } elif (!check_flag(flags, FLAG_L)) {
            if (check_flag(flags, FLAG_N)) {
                printf("%d:", lines_number);
            }
            strip(line);

            if (len == -1) {
                printf("%s\n", line);
            } else {
                for (int i = 0; len; len--, i++) {
                    putchar(line[i]);
                }
                putchar('\n');
            }
        }

        if (check_flag(flags, FLAG_L) && amount_lines_found) {
            printf("%s\n", filename);
        }
    }
}


void search_patterns_in_file_with_flags_o(linked_list_t *patterns, char *filename, int flags) {
    FILE *file;
    if (!strcmp(filename, "-"))
        file = stdin;
    else
        file = fopen(filename, "r");

    if (file) {
        regmatch_t reg_match = {0, 0};

        size_t line_size = 1;
        char *line = calloc(line_size, sizeof(char));

        int amount_lines_found = 0;
        int lines_number = 0;

        ssize_t len_line;

        while ((len_line = getline(&line, &line_size, file)) > 0) {
            lines_number++;

            short was = 0;
            int offset = 0;

            if (is_point) {
                was += 1;
                amount_lines_found++;
                print_found_pattern(filename, line,
                                    -1, lines_number, amount_lines_found,
                                    was, flags);
                continue;
            }

            for (linked_list_t *a = patterns; a; a = a->next_item) {
                if (a->data) {
                    regex_t *cur_reg = a->data;

                    while (offset < len_line) {
                        int res_find = regexec(cur_reg, line + offset, 1, &reg_match, 0);
                        if (res_find == REG_NOMATCH) {
                            break;
                        } elif (!res_find) {
                            was += 1;
                            amount_lines_found++;
                            print_found_pattern(filename, line + offset + reg_match.rm_so,
                                                reg_match.rm_eo - reg_match.rm_so, lines_number,
                                                amount_lines_found,
                                                was, flags);
                        }
                        offset += reg_match.rm_eo;
                    }
                }
            }
        }
        free(line);
        fclose(file);
    } else {
        print_error(NO_FILE, filename, -1);
    }
}

void search_patterns_in_file(linked_list_t *patterns, char *filename, int flags) {
    FILE *file;
    if (!strcmp(filename, "-"))
        file = stdin;
    else
        file = fopen(filename, "r");

    if (file) {
        regmatch_t reg_match = {0, 0};

        size_t line_size = 1;
        char *line = calloc(line_size, sizeof(char));

        int amount_lines_found = 0;
        int lines_number = 0;

        short fast_exit = 0;

        int need_was = !check_flag(flags, FLAG_V);
        while (!fast_exit && (getline(&line, &line_size, file)) > 0) {
            short was = 0;
            int find = 0;


            lines_number++;
            if (is_point) {
                    was += 1;
                    if (was == need_was && need_was) {
                        find = 1;
                    }
            } else {
                for (linked_list_t *a = patterns; !find && a; a = a->next_item) {
                    if (a->data) {
                        regex_t *cur_reg = a->data;

                        int res_find = regexec(cur_reg, line, 1, &reg_match, 0);
                        if (res_find == REG_NOMATCH)
                            continue;
                        elif (reg_match.rm_so != -1)was += 1;

                        if (was == need_was && need_was) {
                            find = 1;
                        }
                    }
                }
            }
            if (was == need_was && find == need_was) {
                amount_lines_found++;
                if (check_flag(flags, FLAG_L)) {
                    fast_exit = 1;
                }
                if (!check_flag(flags, FLAG_C))
                    print_found_pattern(filename, line, -1, lines_number, amount_lines_found, 0, flags);
            }
        }
        if (check_flag(flags, FLAG_C)) {
            print_found_pattern(filename, line, -1, lines_number, amount_lines_found, 0, flags);
        }
        free(line);
        fclose(file);
    } else {
        print_error(NO_FILE, filename, -1);
    }
}

void search_patterns_in_files(linked_list_t *list_filenames, linked_list_t *list_pattern, int flags) {
    for (linked_list_t *f = list_filenames; f; f = f->next_item) {
        if (f->data) {
            if (check_flag(flags, FLAG_O) && !check_flag(flags, FLAG_C) && !check_flag(flags, FLAG_L) &&
                !check_flag(flags, FLAG_V)) {
                search_patterns_in_file_with_flags_o(list_pattern, f->data, flags);
            } else {
                search_patterns_in_file(list_pattern, f->data, flags);
            }
        }
    }
}


int main(int argc, char **argv) {
    argc--, argv++;
    int flags = 0;
    linked_list_t *list_filenames = linked_list(NULL);
    linked_list_t *list_pattern = linked_list(NULL);

    status_code_e status = parsing_argv(argc, argv, list_filenames, list_pattern, &flags, NOTHING);
    if (status != ERROR) {
        int i = 1;
        for (linked_list_t *f = list_filenames; f; f = f->next_item, i++) {
            if (f->data) {
                if (i > 1) {
                    add_flag(flags, FLAG_Z);
                    break;
                }
            } else {
                i--;
            }
        }

        print_error(SET_SETTINGS, "", !check_flag(flags, FLAG_S));

        compile_patterns(list_pattern, flags);
        search_patterns_in_files(list_filenames, list_pattern, flags);

        if (!is_point) {
            for (linked_list_t *p = list_pattern; p; p = p->next_item, i++) {
                if (p->data) {
                    regfree(p->data);
                }
            }
        }
    }
    free_linked_list(list_filenames);
    free_linked_list(list_pattern);
}
