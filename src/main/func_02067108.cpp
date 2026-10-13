/* func_02067108 @ 0x02067108, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_02068144.h"

extern "C" void func_02067108(Base_02068144 *self)
{
    static void (Base_02068144::*tbl[6])() = {&Base_02068144::func_020670fc, &Base_02068144::func_02066f8c,
                                              &Base_02068144::func_02066f20, &Base_02068144::func_02066db0,
                                              &Base_02068144::func_02066c54, &Base_02068144::func_02066bd4};
    if (self->next == 6) {
        return;
    }
    self->idx = self->next;
    (self->*tbl[self->next])();
    self->next = 6;
}
