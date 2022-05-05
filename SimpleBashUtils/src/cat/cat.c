#include <string.h>
#include <stdio.h>
#include "cat.h"

int flags_parser(int *argc, char ***argv) {
    int flags = 0;

    size_t type_arg;
    for (; *argc && (flags != -1) && (type_arg = strspn(**argv, "-")) > 0; (*argc)--, (*argv)++) {
        (**argv) += type_arg;

        if (type_arg == 1) {
            while (***argv) {
                if (***argv == 'b') {
                    add_flag(flags, FLAG_B);
                } elif (***argv == 'e') {
                    add_flag(flags, FLAG_E);
                } elif (***argv == 'n') {
                    add_flag(flags, FLAG_N);
                } elif (***argv == 's') {
                    add_flag(flags, FLAG_S);
                } elif (***argv == 't') {
                    add_flag(flags, FLAG_T);
                } elif (***argv == 'v') {
                    add_flag(flags, FLAG_V);
                } elif (***argv == 'E') {
                    add_flag(flags, FLAG_E);
                } elif (***argv == 'T') {
                    add_flag(flags, FLAG_T);
                } else {
                    flags = -1;
                }
                (**argv)++;
            }
        } elif (type_arg == 2) {
            if (!strcmp(**argv, "--number-nonblank")) {
                add_flag(flags, FLAG_B);
            } elif (!strcmp(**argv, "--number")) {
                add_flag(flags, FLAG_N);
            } elif (!strcmp(**argv, "--squeeze-blank")) {
                add_flag(flags, FLAG_S);
            } else {
                flags = -1;
            }
        } else {
            flags = -1;
        }
        if (flags == -1) {
            fprintf(stderr, "cat: illegal option <%s>\n", **argv);
        }
    }
    return flags;
}

void print_file(FILE *file, int flags) {
    static short last_in_line_was_sim = 0;
    static short in_line_was_sim = 0;

    static unsigned long long int counter = 0;


    char tmp;
    // Read file
    while ((tmp = fgetc(file)) != EOF) {
        if (tmp == '\n') { // End line
            if (check_flag(flags, FLAG_S) && (!in_line_was_sim && !last_in_line_was_sim))
                continue;

            if (check_flag(flags, FLAG_N) && !(check_flag(flags, FLAG_B)) && !in_line_was_sim)
                printf("%6lld\t", ++counter);

            if (check_flag(flags, FLAG_E))
                putchar('$');

            last_in_line_was_sim = in_line_was_sim;
            in_line_was_sim = 0;
        } else {
            if ((check_flag(flags, FLAG_B) || check_flag(flags, FLAG_N)) && !in_line_was_sim)
                printf("%6lld\t", ++counter);
            in_line_was_sim = 1;
        }

        if ((check_flag(flags, FLAG_V) && tmp != '\t') || (check_flag(flags, FLAG_T) && tmp == '\t')) {
            printf("%s", s21_cat_spec_symbols[(unsigned int)tmp]);
        } else {
            putchar(tmp);
        }
    }
    counter = 0;
    in_line_was_sim = 0;
    last_in_line_was_sim = 0;
}

int main(int argc, char **argv) {
    if (argc >= 1) {
        argv++, argc--;
        int flags = flags_parser(&argc, &argv);

        if (flags != -1) {
            if (!argc) {
                print_file(stdin, flags);
            } else {
                for (; argc && argv; argc--, argv++) {
                    if (!strcmp(*argv, "-")) {
                        print_file(stdin, flags);
                    } else {
                        FILE *file = fopen(*argv, "r");
                        if (file) {
                            print_file(file, flags);
                            fclose(file);
                        } else {
                            fprintf(stderr, "cat: %s: No such file or directory\n", *argv);
                        }
                    }
                }
            }
        }
    }
    return 0;
}
