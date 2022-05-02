#include <string.h>
#include <stdio.h>
#include "cat.h"

int parse_flags(int *argc, char ***argv) {
    int flags = 0;
    for (; *argc && strspn(**argv, "-"); (*argv)++, (*argc)--) {
        if (!strcmp(**argv, "-b") && !(flags & FLAG_B))
            flags += FLAG_B;
        else if ((!strcmp(**argv, "-e") || !strcmp((**argv), "-E")) && !(flags & FLAG_E))
            flags += FLAG_E;
        else if (!strcmp(**argv, "-n") && !(flags & FLAG_N))
            flags += FLAG_N;
        else if (!strcmp(**argv, "-s") && !(flags & FLAG_S))
            flags += FLAG_S;
        else if ((!strcmp(**argv, "-t") || !strcmp((**argv), "-T")) && !(flags & FLAG_T))
            flags += FLAG_T;
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
            if (flags &FLAG_S && (!in_line_was_sim && !last_in_line_was_sim))
                continue;

            if (flags & FLAG_N && !(flags & FLAG_B) && !in_line_was_sim)
                printf("%6lld\t", ++counter);

            if (flags & FLAG_E)
                putchar('$');

            last_in_line_was_sim = in_line_was_sim;
            in_line_was_sim = 0;
        } else {
            if (((flags & FLAG_B) || (flags & FLAG_N)) && !in_line_was_sim)
                printf("%6lld\t", ++counter);
            in_line_was_sim = 1;
        }

        if ((flags & FLAG_T) && tmp == '\t') {
            putchar('^');putchar('I');
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
        int flags = parse_flags(&argc, &argv);

        if (!argc) {
            print_file(stdin, flags);
        }

        for (;argc && argv; argc--,argv++) {
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
    return 0;
}
