/* func_020c3b1c @ 0x020c3b1c, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/main/Obj_020e86ec.h"
typedef void (Obj_020e86ec::*Pmf)(void *);
extern "C" void func_020c3b1c(Obj_020e86ec *self, void *arg)
{
    static Pmf tbl[] = {&Obj_020e86ec::func_020c3b8c};
    int i = self->unk_B0;
    if (i >= 0 && i < 1 && tbl[i]) {
        (self->*(tbl[i]))(arg);
    }
}
