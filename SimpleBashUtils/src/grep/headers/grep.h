#ifndef SIMPLEBASHUTILS_GREP_H
#define SIMPLEBASHUTILS_GREP_H

#define FLAG_E 1
#define FLAG_I 2
#define FLAG_V 4
#define FLAG_C 8
#define FLAG_L 16
#define FLAG_N 32
#define FLAG_H 64
#define FLAG_S 128
#define FLAG_F 256
#define FLAG_O 512

#define check_flag(perm, flag) (perm & flag)
#define add_flag(perm, flag) (perm += flag)

#endif //SIMPLEBASHUTILS_GREP_H
