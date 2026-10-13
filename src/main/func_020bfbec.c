/* func_020bfbec @ 0x020bfbec, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    u8 pad_00[0x0c];
    int unk_0C;
    u8 pad_10[0x1f];
    u8 unk_2F;
    u8 pad_30[1];
    u8 unk_31;
    u8 pad_32[2];
    Vec unk_34;
    Vec unk_40;
    u8 pad_4C[0x0c];
    int unk_58;
    u8 pad_5C[4];
    int unk_60, unk_64, unk_68;
} UnkStruct_020bfbec;

extern int data_021f8b48;
extern int data_020ca0e8;
extern Vec data_021c67d0;
extern int *func_020bdf58(int *g, int flags);
extern void func_020c14bc(int *out, int *p);
extern int func_020952ec(int lim);

void func_020bfbec(UnkStruct_020bfbec *self, int flags)
{
    int lim;
    int *p;
    int *q;
    int v;
    int d;
    int f;
    Vec *p1;
    Vec *p2;
    int tmp[4];

    p = func_020bdf58(&data_021f8b48, flags & 0xf);
    self->unk_0C = 0x2d;
    self->unk_58 = 2;
    self->unk_60 = 0x18;
    v = p[0];
    self->unk_64 = v;
    q = p + 1;
    func_020c14bc(tmp, q);
    p1 = &self->unk_34;
    self->unk_34.x = tmp[0];
    p1->y = 0xc5000;
    p1->z = 0;
    p2 = &self->unk_40;
    self->unk_40.x = 0;
    p2->y = (int) 0xffff4000;
    p2->z = 0;
    lim = data_020ca0e8 * 2;
    if (v == func_020952ec(lim)) {
        if (q[2] < lim) {
            self->unk_2F = 1;
        }
    }
    d = q[2] - data_021c67d0.z;
    if (d < (int) 0xfffec000 || d > 0xf000) {
        f = 1;
    } else {
        f = 0;
    }
    flags = flags | (f << 31);
    if (f != 0 || self->unk_34.y >= 0xc0000) {
        self->unk_31 = 1;
    }
    self->unk_68 = flags;
}
