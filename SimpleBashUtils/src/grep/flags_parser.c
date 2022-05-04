#include <string.h>
#include "headers/grep.h"
#include <stdio.h>

int flags_parser(int *argc, char ***argv, FILE **pattern_file) {
    int flags = 0;
    while (*argc) {
        if (!strncmp(**argv, "-e", 2) && !check_flag(flags, FLAG_E)) {
            add_flag(flags, FLAG_E);
        } else if (!strncmp(**argv, "-i", 2) && !check_flag(flags, FLAG_I)) {
            add_flag(flags, FLAG_I);
        } else if (!strncmp(**argv, "-v", 2) && !check_flag(flags, FLAG_V)) {
            add_flag(flags, FLAG_V);
        } else if (!strncmp(**argv, "-c", 2) && !check_flag(flags, FLAG_C)) {
            add_flag(flags, FLAG_C);
        } else if (!strncmp(**argv, "-l", 2) && !check_flag(flags, FLAG_L)) {
            add_flag(flags, FLAG_L);
        } else if (!strncmp(**argv, "-n", 2) && !check_flag(flags, FLAG_N)) {
            add_flag(flags, FLAG_N);
        } else if (!strncmp(**argv, "-h", 2) && !check_flag(flags, FLAG_H)) {
            add_flag(flags, FLAG_H);
        } else if (!strncmp(**argv, "-s", 2) && !check_flag(flags, FLAG_S)) {
            add_flag(flags, FLAG_S);
        } else if (!strncmp(**argv, "-f", 2) && !check_flag(flags, FLAG_F)) {
            add_flag(flags, FLAG_F);
            (*argv)++;
            *pattern_file = fopen(**argv, "r");
            if (!*pattern_file) {
                fprintf(stderr, "grep: %s: No such file or directory\n", **argv);
                *argc = 0;
            }
        } else if (!strncmp(**argv, "-o", 2) && !check_flag(flags, FLAG_O)) {
            add_flag(flags, FLAG_O);
        } else {
            break;
        }
        (*argc)--;
        (*argv)++;
    }
    return flags;
}