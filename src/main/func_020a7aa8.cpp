/* func_020a7aa8 @ 0x020a7aa8, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e3e44.h"
typedef void (Obj_020e3e44::*Pmf)();
extern Pmf __ptmf_null;
extern "C" void func_020a8764(int *);
extern "C" void func_020a7aa8(Obj_020e3e44 *self)
{
    func_020a8764(&self->unk_28);
    static Pmf tbl[] = {&Obj_020e3e44::func_020a7a14, __ptmf_null, __ptmf_null, __ptmf_null, __ptmf_null};
    Pmf p = tbl[self->unk_24];
    if (p) {
        (self->*p)();
    }
}
