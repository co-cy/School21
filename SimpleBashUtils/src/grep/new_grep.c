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
        fprintf(stderr, "grep: %s: No such file or directory", message);
    } elif (type_error == BAD_FLAG) {
        fprintf(stderr, "grep: invalid option -- %c", *message);
    } elif (type_error == BAD_OPTION) {
        fprintf(stderr, "grep: unrecognized option `%s'", message);
    } elif (type_error == MORE_ARGUMENT) {
        if (*message == PATTERNS_FILE) {
            fprintf(stderr, "grep: option requires an argument -- f");
        } elif (*message == PATTERN) {
            fprintf(stderr, "grep: option requires an argument -- e");
        }
    } elif (type_error == OTHER) {
        fprintf(stderr, "%s", message);
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
        printf("PARAM %c\n", *flag);

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
        printf("STATUS: %d\n", status);
        status = parsing_parameter(parameter, files, patterns, flags, status);
        if (status == ERROR) {
            break;
        }
    }

    if (status != NOTHING && status != ERROR) {
        print_error(MORE_ARGUMENT, (char *) &status);
        status = ERROR;
    }

    return status;
}


int main(int argc, char **argv) {
    argc--, argv++;
    int flags;
    linked_list_t *list_filenames = linked_list(NULL);
    linked_list_t *list_pattern = linked_list(NULL);

    status_code_e status = parsing_argv(argc, argv, list_filenames, list_pattern, &flags, NOTHING);
    if (status != ERROR) {
        int i = 1;
        for (linked_list_t *f = list_filenames->next_item; f; f = f->next_item, i++) {
            printf("FILES %d: _%s_\n", i, (char *) f->data);
        }
        i = 1;
        for (linked_list_t *p = list_pattern->next_item; p; p = p->next_item, i++) {
            printf("PATTERNS %d: _%s_\n", i, (char *) p->data);
        }
    }
}