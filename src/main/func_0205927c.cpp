/* func_0205927c @ 0x0205927c, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_0205927c.h"
typedef void (Base_0205927c::*Pmf)();
extern "C" void func_0205927c(Base_0205927c *self)
{
    static Pmf tbl[] = {&Base_0205927c::func_02059420, &Base_0205927c::func_02059304, &Base_0205927c::func_02059304,
                        &Base_0205927c::func_02059304};
    unsigned char i = self->unk_D4;
    if (i < 4) {
        (self->*(tbl[i]))();
    }
}
