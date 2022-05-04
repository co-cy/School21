#include "headers/find_all_pattern_in_file.h"
#include <regex.h>
#include <stdlib.h>

#include <string.h>

void find_all_pattern_in_file(char *pattern, FILE *file, int flags) {
    regex_t regex;
    regmatch_t pmatch;

    size_t size = 1;
     char *line = calloc(size, sizeof (char));
//    char line[1000] = {'\0'};
//    memset(line, 0, 1000);
    if (line) {
        size_t len_line;

        int value = regcomp(&regex, pattern, flags);
        while (!value && (len_line = getline(&line, &size, file)) > 0) {
            if (len_line < size) {
                line[len_line] = '\0';
            } else {
                line = realloc(line, size *= 2);
                line[len_line] = '\0';
            }

            int offset = 0;
            short was = 0;
            while (offset < len_line) {
                int status = regexec(&regex, line + offset, 1, &pmatch, 0);
                if (status != REG_NOMATCH && pmatch.rm_so != -1) {
                    was = 1;
                }
                offset += pmatch.rm_eo;
            }

            if (was) {
                printf("%s", line);
            }

        }
        regfree(&regex);
        free(line);
    }
}