#ifndef SIMPLEBASHUTILS_GREP_H
#define SIMPLEBASHUTILS_GREP_H

#include "regex.h"

static char error[1024] = {'\0'};
static char stdin_file[] = "-";

typedef enum {
    BAD,
    FLAG_E,
    FLAG_I,
    FLAG_V,
    FLAG_C,
    FLAG_L,
    FLAG_N,
    FLAG_H,
    FLAG_F,
    FLAG_S,
    FLAG_O,
    FLAG_Z,
} flag_e;

typedef enum {
    NO_FILE,
    BAD_FLAG,
    BAD_OPTION,
    MORE_ARGUMENT,
    EMPTY,
    OTHER,
    SET_SETTINGS,
} type_error_e;

typedef enum {
    ERROR = -1,
    NOTHING,
    PATTERNS_FILE,
    PATTERN,
} status_code_e;

typedef struct {
    regex_t *reg;
    int BIG;
} gopa;

void print_error(int type_error, char *message, int need_print);

#endif  // SIMPLEBASHUTILS_GREP_H
