/* func_ov009_02264e98 @ 0x02264e98, 0xd0 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

#include "cpp/ov009/Obj_ov009_022658dc.h"

extern "C" int func_02055140(Obj_020dd05c *, void *);
extern "C" void func_02055060(Obj_020dd05c *, int, int, int, int, int);
extern "C" void func_02055050(Obj_020dd05c *);
extern "C" int func_ov009_02264c90(Obj_ov009_022658dc *);
extern "C" void *func_ov009_02262fcc(Obj_ov009_022658dc *);
extern "C" int func_0204bcdc(void *argument0);
extern "C" void *func_0204bc64(void *);
extern "C" int func_020b312c(unsigned short);
extern void *data_021c9b1c;

extern "C" void func_ov009_02264e98(Obj_ov009_022658dc *self)
{
    if (self->vfunc_64() || self->vfunc_68()) {
        func_02055140(&self->unk_13c, data_021c9b1c);
        func_02055060(&self->unk_13c, self->vfunc_64(), 0, 0x1000, 0, 0);
        func_02055050(&self->unk_13c);
    }

    if (func_ov009_02264c90(self) == 0) {
        return;
    }

    unsigned short tmp;
    void *p = func_ov009_02262fcc(self);
    int r = func_0204bcdc((void *) p);
    int b;

    if (r != 0) {
        tmp = 0x501d;
        p = func_0204bc64(p);
        void *q = func_0204bc64(&tmp);
        b = (p == q);
    } else {
        b = (*(unsigned short *) p == 0x501d);
    }

    if (b) {
        self->vfunc_6c(func_020b312c(self->unk_136));
    } else {
        self->vfunc_6c(0);
    }
}
