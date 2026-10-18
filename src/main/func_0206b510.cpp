/* func_0206b510 @ 0x0206b510, 0xf8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

#include "cpp/main/Base_0206b510.h"

typedef void (Base_0206b510::*PMF)();

extern "C" void func_020a93dc(Base_0206b510 *self, u32 arg);
extern "C" void func_020a9334(Base_0206b510 *self, void *data);
extern int data_020cce98;

extern int data_021cda80;
extern PMF data_020de8d4, data_020de904, data_020de914, data_020debec, data_020debf4, data_020debfc, data_020dec14,
    data_020dec1c;
extern PMF data_021cdbb4[8];

extern "C" void func_0206b510(Base_0206b510 *self)
{
    if (!(data_021cda80 & 1)) {
        data_021cdbb4[0] = data_020dec1c;
        data_021cdbb4[1] = data_020dec14;
        data_021cdbb4[2] = data_020de914;
        data_021cdbb4[3] = data_020de8d4;
        data_021cdbb4[4] = data_020debfc;
        data_021cdbb4[5] = data_020debf4;
        data_021cdbb4[6] = data_020debec;
        data_021cdbb4[7] = data_020de904;
        data_021cda80 |= 1;
    }

    PMF pmf = data_021cdbb4[self->idx];

    if (self->flag) {
        self->flag = 0;
        (self->*pmf)();
    } else {
        func_020a93dc(self, self->arg);
        self->flag = 1;
        func_020a9334(self, &data_020cce98);
    }
}
