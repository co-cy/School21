#ifndef SIMPLEBASHUTILS_GREP_H
#define SIMPLEBASHUTILS_GREP_H

#include "../custom.h"
#include "../flag.h"
#include <string.h>

#define start_with(string, other_string) (st)

static char error[1024] = {'\0'};
static char stdin_file[] = "-";

typedef enum flag {
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

typedef enum type_error {
    NO_FILE,
    BAD_FLAG,
    BAD_OPTION,
    MORE_ARGUMENT,
    EMPTY,
    OTHER,
    SET_SETTINGS,
} type_error_e;

typedef enum status_code {
    ERROR = -1,
    NOTHING,
    PATTERNS_FILE,
    PATTERN,
} status_code_e;

#endif //SIMPLEBASHUTILS_GREP_H
