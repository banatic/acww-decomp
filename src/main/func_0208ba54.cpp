/* func_0208ba54 @ 0x0208ba54, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e21fc.h"

typedef void (Obj_020e21fc::*Pmf)();
extern int data_021d3160;
extern Pmf data_020e20e4, data_020e20f4, data_020e2114, data_020e2154;
extern Pmf data_021d31b0[4];

extern "C" void func_0208ba54(Obj_020e21fc *self)
{
    if (!(data_021d3160 & 1)) {
        data_021d31b0[0] = data_020e20f4;
        data_021d31b0[1] = data_020e20e4;
        data_021d31b0[2] = data_020e2154;
        data_021d31b0[3] = data_020e2114;
        data_021d3160 |= 1;
    }
    (self->*(data_021d31b0[self->unk_20]))();
}
