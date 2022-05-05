#include <stdio.h>
#include "src/custom.h"
#include <stdlib.h>
#include <regex.h>

regex_t *get_pattern(int *argc, char ***argv, int flags) {
    regex_t *reg = NULL;

    if (*argc) {
        reg = malloc(sizeof (reg));

        if (reg) {
            int is_bad_res_comp = 0;

            is_bad_res_comp = regcomp(reg, **argv, 0);
            if (is_bad_res_comp) {
                regfree(reg);
                free(reg);

                reg = NULL;
            }
        }

        skip_arg(argc, argv);
    }

    return reg;
}

int main(void)
{

    i
    printf("%d", *a);

    return 0;
}
