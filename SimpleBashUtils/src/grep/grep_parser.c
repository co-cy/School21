//
// Created by Nana Daughterless on 5/12/22.
//


#include "../linked_list/linked_list.h"
#include "privat_grep.h"
#include "../custom.h"
#include "../flag.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "grep.h"


static status_code_e parsing_file_to_patterns(char *filename, linked_list_t *pattern) {
    status_code_e status = NOTHING;

    FILE *file = fopen(filename, "r");
    if (file) {
        size_t line_size = 1;
        char *line = calloc(line_size, sizeof(char));

        while (getline(&line, &line_size, file) > 0) {
            add_to_linked_list(pattern, new_strcpy(strip(line)));
        }
        free(line);
        fclose(file);
    } else {
        print_error(NO_FILE, filename, -1);
        status = ERROR;
    }
    return status;
}


static status_code_e parsing_word(char *word, linked_list_t *files,
                                  linked_list_t *patterns, status_code_e status) {
    if (status == NOTHING) {
        add_to_linked_list(files, new_strcpy(word));
    } elif (status == PATTERNS_FILE) {
        status = parsing_file_to_patterns(word, patterns);
    } elif (status == PATTERN) {
        add_to_linked_list(patterns, new_strcpy(word));
        status = NOTHING;
    } else {
        print_error(OTHER, "WTF???", -1);
        status = ERROR;
    }
    return status;
}


static status_code_e parsing_flag(char *flag, linked_list_t *patterns, int *flags) {
    status_code_e status = NOTHING;

    short flag_exit = 0;
    for (; !flag_exit && (status == NOTHING) && *flag; flag++) {
        char tmp = *flag;

        if (tmp == 'i') {
            add_flag(*flags, FLAG_I);
        } elif (tmp == 'v') {
            add_flag(*flags, FLAG_V);
        } elif (tmp == 'f') {
            add_flag(*flags, FLAG_F);
            if (*(flag + 1))
                status = parsing_file_to_patterns((flag + 1), patterns);
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
    }
    return status;
}


static status_code_e
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


status_code_e parsing_argv(int argc, char **argv, linked_list_t *files,
                           linked_list_t *patterns, int *flags, status_code_e status) {
    for (size_t i = 0; i < argc; i++) {
        status = parsing_parameter(argv[i], files, patterns, flags, status);
        if (status == ERROR)
            break;
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

                shift_linked_list(files);

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
