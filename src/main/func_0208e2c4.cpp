/* func_0208e2c4 @ 0x0208e2c4, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e22f8.h"
typedef void (Obj_020e22f8::*Pmf)();
extern "C" void func_0208a0c8(void *);
extern "C" void func_0208e2c4(Obj_020e22f8 *self)
{
    static Pmf tbl[] = {&Obj_020e22f8::func_0208e214, &Obj_020e22f8::func_0208e1cc, &Obj_020e22f8::func_0208e1a8,
                        &Obj_020e22f8::func_0208e174};
    (self->*(tbl[self->unk_70]))();
    if (self->unk_70) {
        func_0208a0c8(self->unk_14);
    }
}
