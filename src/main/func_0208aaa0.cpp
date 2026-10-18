/* func_0208aaa0 @ 0x0208aaa0, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e20ac.h"
typedef void (Obj_020e20ac::*Pmf)();
extern "C" void func_0208a0c8(void *);
extern "C" void func_0208a490(Obj_020e20ac *);
extern int data_021d3128;
extern Pmf data_020e206c, data_020e2074, data_020e207c, data_020e2084;
extern Pmf data_021d312c[4];

extern "C" void func_0208aaa0(Obj_020e20ac *self)
{
    if (!(data_021d3128 & 1)) {
        data_021d312c[0] = data_020e2074;
        data_021d312c[1] = data_020e2084;
        data_021d312c[2] = data_020e206c;
        data_021d312c[3] = data_020e207c;
        data_021d3128 |= 1;
    }
    (self->*(data_021d312c[self->unk_34]))();
    if (self->unk_34) {
        func_0208a0c8(self->unk_0C);
        func_0208a0c8(self->unk_20);
        func_0208a490(self);
    }
}
