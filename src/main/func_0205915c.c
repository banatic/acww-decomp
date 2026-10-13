/* func_0205915c @ 0x0205915c, 0x114 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Vec {
    int x, y, z;
};

struct This {
    u8 pad_00[0x50];
    u16 unk_50;
    u8 pad_52[0x60 - 0x52];
    int unk_60, unk_64, unk_68;
    int unk_6C, unk_70, unk_74;
    u8 pad_78[0x90 - 0x78];
    int unk_90, unk_94, unk_98;
    int unk_9C, unk_A0, unk_A4;
    u8 pad_A8[0xcc - 0xa8];
    void *unk_CC;
    u8 pad_D0[0xd6 - 0xd0];
    u16 unk_D6;
};

extern struct Vec data_021c939c;

extern void func_0205967c(struct This *, struct Vec *);
extern int func_0204fd3c(int);
extern int func_02059cc4(void *, int);
extern void VEC_Add();
extern void func_02059598(struct Vec *, struct This *, int);
extern void func_020595fc(struct This *, int *, struct Vec *, int);
extern int _s32_div_f(int, int);
extern void func_02059674(struct This *, int);

void func_0205915c(struct This *t)
{
    struct Vec a;
    struct Vec b;
    struct Vec c;
    int ok;
    u16 h;
    int tx, ty, tz;

    func_0205967c(t, &a);
    ok = 0;
    t->unk_9C = 0;
    t->unk_A0 = 0;
    t->unk_A4 = 0;
    b.x = data_021c939c.x;
    b.y = data_021c939c.y;
    b.z = data_021c939c.z;
    h = t->unk_50;
    if (h >= 0x12e8 && h <= 0x131f) {
        ok = 1;
    }
    if (ok) {
        VEC_Add(&b, func_02059cc4(t->unk_CC, func_0204fd3c(h - 0x12e8)), &b);
    }
    func_02059598(&c, t, 0);
    VEC_Add(&b, &c, &b);
    func_020595fc(t, &t->unk_9C, &b, 0);
    t->unk_6C = t->unk_9C;
    t->unk_70 = a.y + t->unk_A0;
    t->unk_74 = t->unk_A4;
    tz = _s32_div_f(t->unk_74 - t->unk_68, 2);
    if (tz < 0) {
        tz = -tz;
    }
    ty = _s32_div_f(t->unk_70 - t->unk_64, 2);
    if (ty < 0) {
        ty = -ty;
    }
    tx = _s32_div_f(t->unk_6C - t->unk_60, 2);
    if (tx < 0) {
        tx = -tx;
    }
    t->unk_90 = tx;
    t->unk_94 = ty;
    t->unk_98 = tz;
    t->unk_D6 = 0;
    func_02059674(t, 1);
}
