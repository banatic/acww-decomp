/* func_02039f98 @ 0x02039f98, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_0208a0c8(void *);

#include "cpp/main/Obj_020da658.h"

typedef void (Obj_020da658::*PMF)();

extern int data_021c6734;
extern PMF data_020da5a0, data_020da5a8, data_020da5b0, data_020da5b8;
extern PMF data_021c673c[4];

extern "C" void func_02039f98(Obj_020da658 *self)
{
    if (self->timer > 0) {
        self->timer--;
    }
    if (!(data_021c6734 & 1)) {
        data_021c673c[0] = data_020da5a0;
        data_021c673c[1] = data_020da5a8;
        data_021c673c[2] = data_020da5b8;
        data_021c673c[3] = data_020da5b0;
        data_021c6734 |= 1;
    }
    (self->*data_021c673c[self->idx])();
    if (self->idx != 0) {
        if (self->unk_0C) {
            func_0208a0c8(&self->sub1c);
        }
        func_0208a0c8(&self->sub30);
    }
}
