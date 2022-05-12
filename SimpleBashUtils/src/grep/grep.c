//
// Created by Nana Daughterless on 5/7/22.
//

#include "../linked_list/linked_list.h"
#include "privat_grep.h"
#include "../custom.h"
#include "../flag.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
#include "grep.h"


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


void compile_patterns(linked_list_t *patterns, int flags) {
    int point = 0;

    for (linked_list_t *a = patterns; a; a = a->next_item) {
        if (a->data) {
            char *pattern = a->data;

            regex_t *reg = malloc(sizeof (regex_t));
            int is_bad_res_comp;
            if (strlen(a->data)) {
                is_bad_res_comp = regcomp(reg, pattern, REG_ICASE * (check_flag(flags, FLAG_I)));
            } else {
                point = 1;
                is_bad_res_comp = regcomp(reg, ".", REG_ICASE * (check_flag(flags, FLAG_I)));
            }


            if (!is_bad_res_comp) {
                for (linked_list_t *b = patterns; b != a; b = b->next_item) {
                    if (b->data) {
                        ((gopa*)b->data)->BIG = point;
                    }
                }
                gopa *gop = malloc(sizeof(gopa));
                gop->reg = reg;
                gop->BIG = point;
                a->data = gop;
            } else {
                regfree(reg);
                free(reg);
                a->data = NULL;
            }
            free(pattern);
        }
    }
}

void print_found_pattern(char *filename,
                         char *line, long long len,
                         int lines_number, int amount_lines_found,
                         int ind_pattern, int flags) {
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
        regmatch_t reg_match;

        size_t line_size = 1;
        char *line = calloc(line_size, sizeof (char));

        int amount_lines_found = 0;
        int lines_number = 0;

        ssize_t len_line;

        int fast_exit = 0;

        int need_was = !check_flag(flags, FLAG_V);
        while (!fast_exit && (len_line = getline(&line, &line_size, file)) > 0) {
            lines_number++;

            if (strchr(line, '\n'))
                len_line--;

            short was = 0;
            long long int offset = 0;
            int fast_boom = 0;
            for (linked_list_t *a = patterns; !fast_boom && a; a = a->next_item) {
                if (a->data) {
                    gopa *gor = a->data;
                    regex_t *cur_reg = gor->reg;

                    if (gor->BIG) {
                        if (need_was) {
                            amount_lines_found++;
                            print_found_pattern(filename, line,
                                                -1, lines_number, amount_lines_found,
                                                was, flags);
                        } else {
                            fast_exit = 1;
                        }
                        fast_boom = 1;
                    }
                    while (!fast_boom && offset < len_line) {
                        int res_find = regexec(cur_reg, line + offset, 1, &reg_match, 0);
                        if (res_find == REG_NOMATCH || reg_match.rm_so == -1) {
                            break;
                        } elif (!res_find) {
                            was += 1;
                        }
                        if (was && need_was) {
                            print_found_pattern(filename, line + offset + reg_match.rm_so,
                                                reg_match.rm_eo - reg_match.rm_so,
                                                lines_number, amount_lines_found,
                                                was, flags);
                        }

                        offset += reg_match.rm_eo;
                    }
                }
            }
            if (!fast_boom && was == need_was && !need_was) {
                amount_lines_found++;
                if (check_flag(flags, FLAG_L)) {
                    fast_exit = 1;
                }
                print_found_pattern(filename, line, -1, lines_number, amount_lines_found, was, flags);
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
        regmatch_t reg_match;

        size_t line_size = 1;
        char *line = calloc(line_size, sizeof (char));

        int amount_lines_found = 0;
        int lines_number = 0;

        short fast_exit = 0;

        int need_was = !check_flag(flags, FLAG_V);
        while (!fast_exit && (getline(&line, &line_size, file)) > 0) {
            short was = 0;
            int find = 0;

            lines_number++;
            for (linked_list_t *a = patterns; !find && a; a = a->next_item) {
                if (a->data) {
                    gopa *gor = a->data;
                    regex_t *cur_reg = gor->reg;

                    int res_find = regexec(cur_reg, line, 1, &reg_match, 0);
                    if (res_find == REG_NOMATCH)
                        continue;
                    elif (!res_find)
                        was += 1;

                    if (was == need_was && need_was) {
                        find = 1;
                    }
                } else {
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
        if (check_flag(flags, FLAG_C))
            print_found_pattern(filename, line, -1, lines_number, amount_lines_found, 0, flags);

        fclose(file);
    } else {
        print_error(NO_FILE, filename, -1);
    }
}

void search_patterns_in_files(linked_list_t* list_filenames, linked_list_t *list_pattern, int flags) {
    for (linked_list_t *f = list_filenames->next_item; f; f = f->next_item) {
        if (check_flag(flags, FLAG_O) && !check_flag(flags, FLAG_C) && !check_flag(flags, FLAG_L)) {
            search_patterns_in_file_with_flags_o(list_pattern, f->data, flags);
        } else {
            search_patterns_in_file(list_pattern, f->data, flags);
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

        free_linked_list(list_filenames);

        for (linked_list_t *p = list_pattern; p; p = p->next_item, i++) {
            if (p->data) {
                regfree(((gopa*)p->data)->reg);
                free(((gopa*)p->data)->reg);
            }
        }
        free_linked_list(list_pattern);
    }
}
