/* func_02058a5c @ 0x02058a5c, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_02058a5c.h"
typedef void (Base_02058a5c::*PMF)();

extern "C" void func_02058a5c(Base_02058a5c *self)
{
    static PMF table[2] = {&Base_02058a5c::func_02058b5c, &Base_02058a5c::func_02058ac8};
    unsigned char i = self->idx;
    if (i >= 2) {
        return;
    }
    (self->*table[i])();
}
