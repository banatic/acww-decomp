/* func_0203637c @ 0x0203637c, 0xcc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_0203637c.h"
typedef void (Base_0203637c::*PMF)(void *);

extern "C" void func_0203637c(Base_0203637c *self)
{
    static PMF table[8] = {&Base_0203637c::func_02036378, &Base_0203637c::func_02036310, &Base_0203637c::func_020362a0,
                           &Base_0203637c::func_02036264, &Base_0203637c::func_02036228, &Base_0203637c::func_02036188,
                           &Base_0203637c::func_02036124, &Base_0203637c::func_020360d0};
    int i;
    for (i = 0; i < 8; i++) {
        (self->*table[i])(&self->arr[i]);
    }
}
