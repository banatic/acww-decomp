/* func_020a7aa8 @ 0x020a7aa8, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e3e44.h"
typedef void (Obj_020e3e44::*Pmf)();
extern Pmf __ptmf_null;
extern "C" void func_020a8764(int *, int);
extern int data_021f4400;
extern Pmf data_021f44b4[5];

extern "C" void func_020a7aa8(Obj_020e3e44 *self, int argument1)
{
    func_020a8764(&self->unk_28, (int) argument1);
    if (!(data_021f4400 & 1)) {
        data_021f44b4[0] = &Obj_020e3e44::func_020a7a14;
        data_021f44b4[1] = __ptmf_null;
        data_021f44b4[2] = __ptmf_null;
        data_021f44b4[3] = __ptmf_null;
        data_021f44b4[4] = __ptmf_null;
        data_021f4400 |= 1;
    }
    Pmf p = data_021f44b4[self->unk_24];
    if (p) {
        (self->*p)();
    }
}
