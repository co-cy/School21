#include <string.h>
#include <stdio.h>

int main(int argc, char **argv) {
    short is_b = 0;
    short is_e = 0;
    short is_n = 0;
    short is_s = 0;
    short is_t = 0;

    short last_null = 0;
    short cur_null = 0;

    unsigned long long int counter = 0;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-b")) {
            is_b ^= 1;
        } else if (!strcmp(argv[i], "-e") || !strcmp(argv[i], "-E")) {
            is_e ^= 1;
        } else if (!strcmp(argv[i], "-n")) {
            is_n ^= 1;
        } else if (!strcmp(argv[i], "-s")) {
            is_s ^= 1;
        } else if (!strcmp(argv[i], "-t") || !strcmp(argv[i], "-T")) {
            is_t ^= 1;
        } else {
            FILE *file = fopen(argv[i], "r");
            if (file) {
                char tmp;
                while ((tmp = fgetc(file)) != EOF) {
                    if (tmp == '\n') {
                        if (is_s && (!cur_null && !last_null))
                            continue;

                        if (is_n && !cur_null) {
                            counter++;
                            printf("%lld\t", counter);
                        }

                        if (is_e) {
                            putchar('$');
                        }

                        last_null = cur_null;
                        cur_null = 0;
                    } else {
                        if (!cur_null && (is_b || is_n) && is_e) {
                                putchar('\t');
                        }
                        if (!cur_null && (is_b || is_n)) {
                            counter++;
                            printf("%lld\t", counter);
                        }
                        cur_null = 1;
                    }
                    if (is_t && tmp == '\t') {
                        putchar('^');putchar('I');
                    } else {
                        putchar(tmp);
                    }
                }
                fclose(file);
            }
        }
    }
    return 0;
}
