/* func_020b8b88 @ 0x020b8b88, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Base_020b8b88.h"

extern "C" void func_020b8af0(Base_020b8b88 *self);

typedef void (Base_020b8b88::*MFN)();

extern int data_021f6af0;
extern MFN data_020e5820, data_020e5828, data_020e5830, data_020e5838;
extern MFN data_021f6b00[4];

extern "C" void func_020b8b88(Base_020b8b88 *self)
{
    if (!(data_021f6af0 & 1)) {
        data_021f6b00[0] = data_020e5830;
        data_021f6b00[1] = data_020e5820;
        data_021f6b00[2] = data_020e5838;
        data_021f6b00[3] = data_020e5828;
        data_021f6af0 |= 1;
    }
    func_020b8af0(self);
    (self->*data_021f6b00[self->index])();
    self->flag = 0;
    self->sub.vfunc_0c();
}
