/* func_0208dd78 @ 0x0208dd78, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e226c.h"
typedef void (Obj_020e226c::*Pmf)();
extern "C" void func_0208d4a4(Obj_020e226c *);
extern "C" void func_0208d784(Obj_020e226c *);
extern "C" void func_0208d410(Obj_020e226c *);
extern "C" void func_0208dd78(Obj_020e226c *self)
{
    static Pmf tbl[] = {&Obj_020e226c::func_0208dcd4, &Obj_020e226c::func_0208dc64, &Obj_020e226c::func_0208dc44,
                        &Obj_020e226c::func_0208dbd8};
    (self->*(tbl[self->unk_20]))();
    func_0208d4a4(self);
    func_0208d784(self);
    if (self->unk_20) {
        func_0208d410(self);
    }
}
