/* func_020a238c @ 0x020a238c, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_020a238c.h"
typedef int (Base_020a238c::*Pmf)();
extern "C" int func_020a238c(Base_020a238c *self)
{
    int r = 0;
    static Pmf tbl[] = {&Base_020a238c::func_020a233c, &Base_020a238c::func_020a22f8, &Base_020a238c::func_020a22b8,
                        &Base_020a238c::func_020a21ec};
    unsigned char i = self->unk_A0;
    if (tbl[i]) {
        r = (self->*(tbl[i]))();
    }
    if (r != 3) {
        self->unk_A0 = 0;
        return r;
    }
    return 3;
}
