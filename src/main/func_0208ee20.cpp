/* func_0208ee20 @ 0x0208ee20, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e236c.h"

typedef void (Obj_020e236c::*Pmf)();
extern "C" void func_0208ee20(Obj_020e236c *self)
{
    static Pmf tbl[] = {&Obj_020e236c::func_0208edb8, &Obj_020e236c::func_0208ed98, &Obj_020e236c::func_0208ed60,
                        &Obj_020e236c::func_0208ed40};
    (self->*(tbl[self->unk_20]))();
}
