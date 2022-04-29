#include <string.h>
#include <stdio.h>

int main(int argc, char **argv) {
    short is_b = 0;
    short is_e = 0;
    short is_n = 0;
    short is_s = 0;
    short is_t = 0;

    short last_in_line_was_sim = 0;
    short in_line_was_sim = 0;

    unsigned long long int counter = 0;

    char **cur_arg = argv;
    for (cur_arg++; cur_arg && strspn(*cur_arg, "-"); cur_arg++) {
        fprintf(stderr, "flags - %s\n", *cur_arg);
        if (!strcmp(*cur_arg, "-b")) {
            is_b += 1;
        } else if (!strcmp(*cur_arg, "-e") || !strcmp((*cur_arg), "-E")) {
            is_e += 1;
        } else if (!strcmp(*cur_arg, "-n")) {
            is_n += 1;
        } else if (!strcmp(*cur_arg, "-s")) {
            is_s += 1;
        } else if (!strcmp(*cur_arg, "-t") || !strcmp((*cur_arg), "-T")) {
            is_t += 1;
        }
    }

    for (;*cur_arg; cur_arg++) {
        fprintf(stderr, "files - %s\n", *cur_arg);
        FILE *file = fopen(*cur_arg, "r");
        if (file) {
            char tmp;

            // Read file
            while ((tmp = fgetc(file)) != EOF) {
                if (tmp == '\n') { // End line
                    if (is_s && (!in_line_was_sim && !last_in_line_was_sim))
                        continue;

                    if (is_n && !is_b && !in_line_was_sim) {
                        counter++;
                        printf("%6lld\t", counter);
                    }

                    if (is_e) {
                        putchar('$');
                    }

                    last_in_line_was_sim = in_line_was_sim;
                    in_line_was_sim = 0;
                } else {
                    if ((is_b || is_n) && !in_line_was_sim) {
                        counter++;
                        printf("%6lld\t", counter);
                    }
                    in_line_was_sim = 1;
                }

                if (is_t && tmp == '\t') {
                    putchar('^');putchar('I');
                } else {
                    putchar(tmp);
                }
            }
            counter = 0;
            fclose(file);
        } else {
            fprintf(stderr, "cat: %s: No such file or directory\n", *cur_arg);
        }
    }
    return 0;
}
