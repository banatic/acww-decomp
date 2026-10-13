/* func_020aa19c @ 0x020aa19c, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e404c.h"
typedef void (Obj_020e404c::*Pmf)();
extern "C" void func_020aa19c(Obj_020e404c *self)
{
    static Pmf tbl[] = {&Obj_020e404c::func_020aa13c, &Obj_020e404c::func_020a9fac, &Obj_020e404c::func_020a9ebc,
                        &Obj_020e404c::func_020a9e04};
    (self->*(tbl[self->unk_08]))();
    self->sub.vfunc_08();
}
