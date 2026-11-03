/* sky_kind3: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020c10f4 @ 0x020c10f4, 0x50 bytes, Thumb
 * func_020c1064 @ 0x020c1064, 0x90 bytes, Thumb
 * func_020c105c @ 0x020c105c, 0x8 bytes, Thumb
 * func_020c0f8c @ 0x020c0f8c, 0xd0 bytes, Thumb
 * func_020c0f18 @ 0x020c0f18, 0x74 bytes, Thumb
 * func_020c0f04 @ 0x020c0f04, 0x14 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    char pad_10[0x3c];
    int unk_4C;
    int unk_50;
    char pad_54[0x4];
    int unk_58;
    char pad_5C[0x4];
    int unk_60;
    int unk_64;
} UnkStruct_020c10f4;

struct UnkStruct_020c1064 {
    int unk_00;
    int unk_04;
    char pad_08[8];
    int unk_10;
    char pad_14[32];
    int unk_34;
    int unk_38;
    int unk_3C;
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
    int unk_50;
    unsigned short unk_54;
    char pad_56[10];
    unsigned int unk_60;
    int unk_64;
};

typedef struct {
    char pad_00[0xc];
    int unk_0C;
    char pad_10[0x24];
    int unk_34;
    int unk_38;
    int unk_3C;
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4C;
    int unk_50;
    u16 unk_54;
    char pad_56[2];
    int unk_58;
} UnkStruct_020c0f8c;

typedef struct {
    int pad_00;
    int unk_04;
    int pad_08[11];
    int unk_34;
    int unk_38;
    int pad_3C;
    int unk_40;
    int pad_44[7];
    int unk_60;
} UnkStruct_020c0f18;

extern int data_020d23ec[];
extern int func_020c1144(void *);
extern void func_020eabc8(void *, int);
extern void VEC_Add(void *, void *, void *);
extern int func_0208a160(void *);
extern int data_020d26f0[];
extern void func_020bf590(void *);
extern int func_020644cc(int);
extern int func_020e8ed8(int a, int b);
extern int FX_MulFunc(int a, int b);
extern short FX_SinCosTable_[];
extern void func_020bf220(UnkStruct_020c0f8c *p, int a, int b);
extern unsigned char data_021fba88[];

void func_020c10f4(UnkStruct_020c10f4 *p, int param)
{
    int x = param & 0xf;
    int v;

    p->unk_0C = data_020d23ec[x];

    if (x == 1) {
        p->unk_58 = 3;
    } else {
        p->unk_58 = 2;
    }

    p->unk_60 = param;
    p->unk_64 = 0;

    if (x == 1) {
        v = (*(int *) data_020d26f0);
        p->unk_4C = v;
        p->unk_50 = v;
        if (func_020c1144(p) == 0) {
            p->unk_04 = 3;
        }
    }
}

void func_020c1064(struct UnkStruct_020c1064 *self)
{
    unsigned int state;
    int count;
    int val;

    state = self->unk_60 & 0xf;
    self->unk_64++;

    if (state == 0) {
        func_020eabc8(&self->unk_40, 0xe66);
        VEC_Add(&self->unk_34, &self->unk_40, &self->unk_34);
        if (func_0208a160(&self->unk_10) != 0) {
            self->unk_04 = 3;
        }
    } else if (state == 1) {
        count = self->unk_64;
        val = data_020d26f0[count];
        if (count >= 23) {
            self->unk_04 = 3;
        } else {
            self->unk_4C = val;
            self->unk_50 = val;
            self->unk_54 += 0xe39;
            if (func_020c1144(self) == 0) {
                self->unk_04 = 3;
            }
        }
    } else {
        if (self->unk_64 >= 6) {
            self->unk_04 = 3;
        }
    }
}

void func_020c105c(void *argument0)
{
    func_020bf590((void *) argument0);
}

void func_020c0f8c(UnkStruct_020c0f8c *p)
{
    int dx;
    int dy;
    int a;
    int idx;
    int s;
    int c;

    p->unk_4C = 0x1000;
    p->unk_50 = 0x800;
    if (func_020644cc(2) == 0) {
        dx = (func_020644cc(0x3c) + 0xc4) << 12;
        dy = 0;
    } else {
        dx = 0x00100000;
        dy = func_020644cc(0x30) << 12;
    }
    a = func_020e8ed8(((func_020644cc(0x17) + 0x80) << 12) - dy, -dx);
    idx = ((unsigned short) a >> 4) << 1;
    s = FX_SinCosTable_[idx];
    c = FX_SinCosTable_[idx + 1];
    dx = dx - 0x23 * c;
    dy = dy - 0x23 * s;
    p->unk_34 = dx;
    p->unk_38 = dy;
    p->unk_3C = 0;
    p->unk_40 = FX_MulFunc(c, 0x7800);
    p->unk_44 = FX_MulFunc(s, 0x7800);
    p->unk_48 = 0;
    p->unk_54 = (u16) (a - 0x4000);
    p->unk_0C = 0x11;
    p->unk_58 = 3;
    data_021fba88[0x10] = 0;
    func_020bf220(p, 6, 0x801);
}

void func_020c0f18(UnkStruct_020c0f18 *self)
{
    int x;
    int offscreen;
    int y;
    int visible;

    VEC_Add(&self->unk_34, &self->unk_40, &self->unk_34);
    x = self->unk_34 >> 12;
    y = self->unk_38 >> 12;
    if (y < -35 || y > 202 || x < -35 || x > 291) {
        offscreen = 1;
    } else {
        offscreen = 0;
    }
    if (self->unk_60 == 0 && offscreen == 0 && y > 0 && y < 192 && x > 0 && x < 256) {
        visible = 1;
    } else {
        visible = 0;
    }
    data_021fba88[0x10] = visible;
    if (offscreen != 0) {
        self->unk_04 = 3;
    }
}

void func_020c0f04(int arg)
{
    data_021fba88[0x10] = 0;
    func_020bf590((void *) arg);
}
