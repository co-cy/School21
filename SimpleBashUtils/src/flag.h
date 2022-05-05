#ifndef SIMPLEBASHUTILS_FLAG_H
#define SIMPLEBASHUTILS_FLAG_H

#define Iflag(flag) (1 << flag)
#define add_flag(flags, flag) (flags |= Iflag(flag))
#define check_flag(flags, flag) (flags & Iflag(flag))

#endif //SIMPLEBASHUTILS_FLAG_H
