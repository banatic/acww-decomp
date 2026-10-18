/* func_020aa19c @ 0x020aa19c, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e404c.h"
typedef void (Obj_020e404c::*Pmf)();
extern int data_021f45ac;
extern Pmf data_020e3edc, data_020e3ef4, data_020e3f6c, data_020e3f74;
extern Pmf data_021f45d0[4];

extern "C" void func_020aa19c(Obj_020e404c *self)
{
    if (!(data_021f45ac & 1)) {
        data_021f45d0[0] = data_020e3f6c;
        data_021f45d0[1] = data_020e3f74;
        data_021f45d0[2] = data_020e3edc;
        data_021f45d0[3] = data_020e3ef4;
        data_021f45ac |= 1;
    }
    (self->*(data_021f45d0[self->unk_08]))();
    self->sub.vfunc_08();
}
