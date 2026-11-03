/* sky_shots_4: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020bfbec @ 0x020bfbec, 0xc4 bytes, Thumb
 * func_020bfb20 @ 0x020bfb20, 0xcc bytes, Thumb
 * func_020bfb18 @ 0x020bfb18, 0x8 bytes, Thumb
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

typedef struct {
    u8 pad_00[0x04];
    int unk_04;
    u8 pad_08[0x28];
    u8 unk_30;
    u8 unk_31;
    u8 pad_32[0x02];
    int unk_34;
    int unk_38;
    u8 pad_3C[0x04];
    int unk_40;
    u8 pad_44[0x1c];
    int unk_60;
    u8 pad_64[0x04];
    u32 unk_68;
} UnkStruct_020bfb20;

extern int data_021f8b48;
extern int data_020ca0e8;
extern Vec data_021c67d0;
extern int *func_020bdf58(int *g, int flags);
extern void func_020c14bc(int *out, int *p);
extern int func_020952ec(int lim);
extern void VEC_Add(int *a, int *b, int *c);
extern void func_020bf590(void *);

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

void func_020bfb20(UnkStruct_020bfb20 *self)
{
    int *v;
    int *p40;
    int flag3, flag2, flag1;
    int y;
    u32 f68;
    u32 kind;
    u32 bit;

    f68 = self->unk_68;
    self->unk_60--;

    if (self->unk_60 < 0) {
        v = &self->unk_34;
        p40 = &self->unk_40;

        if (self->unk_60 == -2) {
            kind = (f68 >> 4) & 0xf;
            if (kind == 1) {
                *p40 = 0x2800;
            } else if (kind == 2) {
                *p40 = 0xffffd800;
            }
        }

        VEC_Add(v, p40, v);

        flag3 = 1;
        flag2 = flag3;
        flag1 = flag3;
        y = v[1];
        if (y >= -0xa000 && y <= 0xca000) {
            flag1 = 0;
        }
        if (flag1 == 0 && v[0] >= -0xa000) {
            flag2 = 0;
        }
        if (flag2 == 0 && v[0] <= 0x10a000) {
            flag3 = 0;
        }
        if (flag3 != 0 || self->unk_30 != 0) {
            self->unk_04 = 3;
        }
    }

    if (self->unk_31 != 0) {
        bit = (f68 >> 31) & 1;
        if (bit == 0 && self->unk_38 < 0x000c0000) {
            self->unk_31 = 0;
        }
    }
}

void func_020bfb18(void *argument0)
{
    func_020bf590((void *) argument0);
}
