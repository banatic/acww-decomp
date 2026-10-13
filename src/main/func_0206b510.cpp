/* func_0206b510 @ 0x0206b510, 0xf8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#include "cpp/main/Base_0206b510.h"

typedef void (Base_0206b510::*PMF)();

extern "C" void func_020a93dc(Base_0206b510 *self, u32 arg);
extern "C" void func_020a9334(Base_0206b510 *self, void *data);
extern int data_020cce98;

extern "C" void func_0206b510(Base_0206b510 *self)
{
    static PMF table[8] = {&Base_0206b510::func_0206a8f4, &Base_0206b510::func_0206a854, &Base_0206b510::func_0206a790,
                           &Base_0206b510::func_0206a6ac, &Base_0206b510::func_0206a694, &Base_0206b510::func_0206a67c,
                           &Base_0206b510::func_0206a664, &Base_0206b510::func_0206a64c};

    PMF pmf = table[self->idx];

    if (self->flag) {
        self->flag = 0;
        (self->*pmf)();
    } else {
        func_020a93dc(self, self->arg);
        self->flag = 1;
        func_020a9334(self, &data_020cce98);
    }
}
