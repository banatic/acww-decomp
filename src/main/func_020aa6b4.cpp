/* func_020aa6b4 @ 0x020aa6b4, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e406c.h"
typedef void (Obj_020e406c::*Pmf)();
extern int data_021f45a4;
extern Pmf data_020e3f24, data_020e3f2c, data_020e3f34, data_020e3f3c;
extern Pmf data_021f45f0[4];

extern "C" void func_020aa6b4(Obj_020e406c *self)
{
    if (!(data_021f45a4 & 1)) {
        data_021f45f0[0] = data_020e3f3c;
        data_021f45f0[1] = data_020e3f34;
        data_021f45f0[2] = data_020e3f24;
        data_021f45f0[3] = data_020e3f2c;
        data_021f45a4 |= 1;
    }
    (self->*(data_021f45f0[self->unk_08]))();
    self->sub.vfunc_08();
}
