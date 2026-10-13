/* func_020aa6b4 @ 0x020aa6b4, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e406c.h"
typedef void (Obj_020e406c::*Pmf)();
extern "C" void func_020aa6b4(Obj_020e406c *self)
{
    static Pmf tbl[] = {&Obj_020e406c::func_020aa660, &Obj_020e406c::func_020aa4f4, &Obj_020e406c::func_020aa420,
                        &Obj_020e406c::func_020aa360};
    (self->*(tbl[self->unk_08]))();
    self->sub.vfunc_08();
}
