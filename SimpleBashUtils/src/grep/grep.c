//
// Created by Nana Daughterless on 5/7/22.
//

#include "../linked_list/linked_list.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "grep.h"

int nigga_comp(const char *a, const char *b, int flags) {
    int res;
    if (flags) {
        int d = 0;
        for (;*a && *b && !d; a++, b++) {
            d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        }
        if (!d) {
            res = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        } else {
            res = d;
        }
    } else {
        res = strcmp(a, b);
    }
    return res;

}

void strip(char *string) {
    char *a = string;

    for (; *a;a++)
        continue;

    while (a != string && *(--a) == '\n') {
        *a = '\0';
    }
}


void print_error(int type_error, char *message, short need_print) {
    static short saved_need_print = 1;

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

        while (getline(&line, &line_size, file) > 0) {
            strip(line);

            char *copy_line = malloc(sizeof(char) * (strlen(line) + 1));
            strcpy(copy_line, line);
            add_to_linked_list(pattern, copy_line);
        }
        status = NOTHING;
        free(line);
    } else {
        print_error(NO_FILE, filename, -1);
        status = ERROR;
    }
    return status;
}

int parsing_word(char *word, linked_list_t *files, linked_list_t *patterns, status_code_e status) {
    if (status == NOTHING) {
        char *copy_word = malloc(sizeof (char) * (strlen(word) + 1));
        strcpy(copy_word, word);

        add_to_linked_list(files, copy_word);
    } elif (status == PATTERNS_FILE) {
        status = parsing_file_to_patterns(word, patterns, status);
    } elif (status == PATTERN) {
        char *copy_word = malloc(sizeof (char) * (strlen(word) + 1));
        strcpy(copy_word, word);

        add_to_linked_list(patterns, copy_word);
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
            if (*(flag + 1)) {
                char *copy_word = malloc(sizeof(char) * (strlen((flag + 1)) + 1));
                strcpy(copy_word, (flag + 1));

                add_to_linked_list(patterns, copy_word);
            } else
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


int parsing_parameter(char *parameter, linked_list_t *files, linked_list_t *patterns, int *flags, status_code_e status) {
    if (!strcmp(parameter, "-")) {
        char *copy_parameter = malloc(sizeof (char) * (strlen(parameter) + 1));
        strcpy(copy_parameter, parameter);

        add_to_linked_list(files, copy_parameter);
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

int parsing_argv(int argc, char **argv, linked_list_t *files, linked_list_t *patterns, int *flags, status_code_e status) {
    for (size_t i = 0; i < argc; i++) {
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
        short have_pattern = !is_empty_linked_list(patterns);
        short have_files = !is_empty_linked_list(files);

        if (have_pattern) {
            if (!have_files) {
                char *copy_parameter = malloc(sizeof (char) * (strlen(stdin_file) + 1));
                strcpy(copy_parameter, stdin_file);

                add_to_linked_list(files, copy_parameter);
            }
        } else {
            if (have_files) {
                char *copy_parameter = malloc(sizeof (char) * (strlen(files->next_item->data) + 1));
                strcpy(copy_parameter, files->next_item->data);

                add_to_linked_list(patterns, copy_parameter);
                shift_linked_list(files);
                have_files = !is_empty_linked_list(files);
                if (!have_files) {
                    char *copy_parameter = malloc(sizeof (char) * (strlen(stdin_file) + 1));
                    strcpy(copy_parameter, stdin_file);

                    add_to_linked_list(files, copy_parameter);
                }
            } else {
                print_error(EMPTY, "", -1);
                status = ERROR;
            }
        }
    }

    return status;
}

void compile_patterns(linked_list_t *patterns, int flags) {
    int point = 0;

//    for (linked_list_t *a = patterns; a; a = a->next_item) {
//        if (a->data && a->next_item) {
//            for (linked_list_t *b = a->next_item; b; b = b->next_item) {
//                if (b->data) {
//                    if (!nigga_comp(a->data, b->data, check_flag(flags, FLAG_I))) {
//                        a->was += b->was;
////                        printf("TEST WAS %d: %s\n", a->was, b->data);
//                        free(b->data);
//                        b->data = NULL;
//                    }
//                }
//            }
//        }
//    }


    for (linked_list_t *a = patterns; a; a = a->next_item) {
        if (a->data) {
            char *pattern = a->data;
//            printf("PATTERNS: %s\n", pattern);

            regex_t *reg = malloc(sizeof (regex_t));
            int is_bad_res_comp;
            if (strlen(a->data)) {
                is_bad_res_comp = regcomp(reg, pattern, REG_ICASE * (check_flag(flags, FLAG_I)));
            } else {
                point = 1;
                is_bad_res_comp = regcomp(reg, ".", REG_ICASE * (check_flag(flags, FLAG_I)));
            }


            if (!is_bad_res_comp) {
//                int zora = 0;
                for (linked_list_t *b = patterns; b != a; b = b->next_item) {
                    if (b->data) {
//                        reg->
//                        printf("ABOBA %d\n", memcmp(((gopa*)b->data)->reg, reg, sizeof (regex_t) - 1));
//                        if (!memcmp(((gopa*)b->data)->reg, reg, sizeof (regex_t))) {
//                            ((gopa *) b->data)->was++;
//                            zora = 1;
//                        }
                        ((gopa*)b->data)->BIG = point;
                    }
                }
//                if (!zora) {
                    gopa *gop = malloc(sizeof(gopa));
                    gop->reg = reg;
//                    printf("PAT %d %s\n", a->was, pattern);
                    gop->was = a->was;
                    gop->BIG = point;
                    a->data = gop;
//                }
//                printf("%d\n", ((gopa*)a->data)->was);
            } else {
                regfree(reg);
                free(reg);
                a->data = NULL;
            }
            free(pattern);
        }
    }
}

void print_found_pattern(char *filename, char *line, int len, int lines_number, int amount_lines_found, int ind_pattern, int flags) {
    if (check_flag(flags, FLAG_O) && ind_pattern > 1) {
        if (len == -1)
            printf("%s\n", line);
        else {
            for (int i = 0;len; len--, i++) {
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

            if (len == -1)
                printf("%s\n", line);
            else {
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

void find_pattern_in_patterns(char *line, size_t len_pattern, linked_list_t *cur_pat, linked_list_t *patterns, int lines_number, int flags) {
    char *beb = calloc(len_pattern + 1, sizeof(char));
    if (beb) {

        // TODO: ПРОХОДКА ТОЛЬКО В ОДНУ СТРОНУ
        strncpy(beb, line, len_pattern);
        beb[len_pattern] = 0;

//        printf("BOB: _%s_\n", beb);
        regmatch_t reg_match;
        int i =-2;
        for (linked_list_t *a = patterns; a; a = a->next_item) {
            i++;
            if (a != cur_pat && a->data) {
//                printf("LSIT %d\n", i);
                gopa *gop = a->data;
                regex_t *cur_reg = gop->reg;

                int res_find = regexec(cur_reg, beb, 1, &reg_match, 0);
//                if (!strcmp(beb, "permission") && i == 2) {
//                    printf("AASODPAS: %d\n", res_find);
//                }
                if (res_find == REG_NOMATCH || reg_match.rm_so == -1) {
                    continue;
                } elif (!res_find) {
//                    printf("FINDED\n");
//                    printf("ABSSS: %lld %lld\n", reg_match.rm_so, reg_match.rm_eo);
                    print_found_pattern("", beb + reg_match.rm_so,
                                        reg_match.rm_eo - reg_match.rm_so, lines_number, 0,
                                        2, flags);
                    find_pattern_in_patterns(beb + reg_match.rm_so, reg_match.rm_eo - reg_match.rm_so, a, patterns,
                                             lines_number, flags);
                }

            }
        }
        free(beb);
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

        short need_was = !check_flag(flags, FLAG_V);
        while (!fast_exit && (len_line = getline(&line, &line_size, file)) > 0) {
            lines_number++;

            if (strchr(line, '\n'))
                len_line--;

            short was = 0;
            int offset = 0;
            int fast_boom = 0;
            int bomg = 0;
            for (linked_list_t *a = patterns; !fast_boom && a; a = a->next_item) {
                if (a->data) {
                    gopa *gor = a->data;
                    regex_t *cur_reg = gor->reg;
//                    printf("ABOBAS %d\n", a->was);


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
                    int hor_boom = 0;
                    while (!fast_boom && !hor_boom && offset < len_line) {
                        int res_find = regexec(cur_reg, line + offset, 1, &reg_match, 0);
                        if (res_find == REG_NOMATCH || reg_match.rm_so == -1) {
                            offset -= bomg;
                            bomg = 0;
                            break;
                        } elif (!res_find) {
                            was += 1;
                        }
                        if (was && need_was) {
//                            printf("WAS: %d\n", gor->was);
                            was--;
                            for (int i = 0; i < gor->was; i++) {
                                was++;
                                if (!gor->BIG) {
                                    print_found_pattern(filename, line + offset + reg_match.rm_so,
                                                        reg_match.rm_eo - reg_match.rm_so, lines_number, amount_lines_found,
                                                        was, flags);
                                    find_pattern_in_patterns(line + offset + reg_match.rm_so, reg_match.rm_eo - reg_match.rm_so, a, patterns, lines_number, flags);
                                } else {
                                    offset = len_line;
                                }
                            }
//
//
////                            printf("OFF %d %lld %zd\n", offset, reg_match.rm_eo, len_line);
//                            if (offset + reg_match.rm_eo >= len_line) {
//                                offset = 0;
//                                bomg = 0;
//                                hor_boom = 1;
//                            } else {
//                                bomg = reg_match.rm_eo - reg_match.rm_so;
//                                offset += reg_match.rm_eo;
//                            }
////                            printf("NOFF %d %lld %zd\n", offset, reg_match.rm_eo, len_line);
                        }
//                        else {
//                            bomg = reg_match.rm_eo - reg_match.rm_so;
                            offset += reg_match.rm_eo;
//                        }
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

        short need_was = !check_flag(flags, FLAG_V);
        int find;
        short was;
        while (!fast_exit && (getline(&line, &line_size, file)) > 0) {
            was = 0;
            find = 0;

            lines_number++;
            for (linked_list_t *a = patterns; !find && a; a = a->next_item) {
                if (a->data) {
                    gopa *gor = a->data;
                    regex_t *cur_reg = gor->reg;

                    int res_find = regexec(cur_reg, line, 1, &reg_match, 0);
//                    printf("%d", res_find);
                    if (res_find == REG_NOMATCH)
                        continue;
                    elif (!res_find)
                        was += 1;
//                    printf("WAS: %d\n", was);

                    if (was == need_was && need_was) {
                        find = 1;
                    }
                } else {
//                    printf("ABOBA: _%s\n", line);
                }
            }
//            printf("\nLINE: %s", line);
//            printf("END WAS: %d %d %d\n", was, find, need_was);
            if (was == need_was && find == need_was){
//                printf("______ABOBA____%s\n", line);
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
            }
        }
        free_linked_list(list_pattern);
    }
}
