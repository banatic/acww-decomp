/* func_020aad9c @ 0x020aad9c, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_020aad9c.h"
typedef void (Base_020aad9c::*Pmf)();
extern "C" int func_020aabe0(Base_020aad9c *);
extern "C" void func_020aaabc(Base_020aad9c *);
extern "C" void func_020aab48(Base_020aad9c *);
extern "C" void func_020aad9c(Base_020aad9c *self)
{
    if (!func_020aabe0(self)) {
        static Pmf tbl[] = {&Base_020aad9c::func_020aa888, &Base_020aad9c::func_020aa83c};
        func_020aaabc(self);
        func_020aab48(self);
        (self->*(tbl[self->unk_2C]))();
    }
}
