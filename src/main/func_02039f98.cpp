/* func_02039f98 @ 0x02039f98, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_0208a0c8(void *);

#include "cpp/main/Obj_020da658.h"

typedef void (Obj_020da658::*PMF)();

extern "C" void func_02039f98(Obj_020da658 *self)
{
    if (self->timer > 0) {
        self->timer--;
    }
    static PMF tbl[4] = {&Obj_020da658::func_02039e08, &Obj_020da658::func_02039cf8, &Obj_020da658::func_02039c4c,
                         &Obj_020da658::func_02039b90};
    (self->*tbl[self->idx])();
    if (self->idx != 0) {
        if (self->unk_0C) {
            func_0208a0c8(&self->sub1c);
        }
        func_0208a0c8(&self->sub30);
    }
}
