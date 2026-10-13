/* func_0208c6b0 @ 0x0208c6b0, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e2250.h"
typedef void (Obj_020e2250::*Pmf)();
extern "C" void func_0208c6b0(Obj_020e2250 *self)
{
    static Pmf tbl[] = {&Obj_020e2250::func_0208c3a0, &Obj_020e2250::func_0208c310, &Obj_020e2250::func_0208c2ac,
                        &Obj_020e2250::func_0208c21c};
    (self->*(tbl[self->unk_C0]))();
}
