/* func_0208aaa0 @ 0x0208aaa0, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e20ac.h"
typedef void (Obj_020e20ac::*Pmf)();
extern "C" void func_0208a0c8(void *);
extern "C" void func_0208a490(Obj_020e20ac *);
extern "C" void func_0208aaa0(Obj_020e20ac *self)
{
    static Pmf tbl[] = {&Obj_020e20ac::func_0208a978, &Obj_020e20ac::func_0208a8d4, &Obj_020e20ac::func_0208a8ac,
                        &Obj_020e20ac::func_0208a848};
    (self->*(tbl[self->unk_34]))();
    if (self->unk_34) {
        func_0208a0c8(self->unk_0C);
        func_0208a0c8(self->unk_20);
        func_0208a490(self);
    }
}
