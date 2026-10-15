/* func_0200b218 @ 0x0200b218, 0x15c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0200b218 {
    int x, y, z;
} UnkStruct_0200b218;
typedef struct B48 {
    int w[12];
} B48;
typedef struct Bits {
    u32 b0 : 12;
    u32 b12 : 16;
    u32 b28 : 4;
} Bits;
typedef struct UnkStruct_0200b218_2 {
    int unk_00;
    int unk_04;
} UnkStruct_0200b218_2;

typedef struct UnkStruct_0200b218_3 {
    u8 pad_00[0xc4];
    UnkStruct_0200b218 g;
    short unk_D0;
    u8 pad_D2[0x298 - 0xd2];
    B48 unk_298;
    u8 pad_2C8[0x2d8 - 0x2c8];
    Bits unk_2D8;
    u8 pad_2DC[0x698 - 0x2dc];
    B48 unk_698;
    u8 pad_6C8[0x704 - 0x6c8];
    int unk_704;
    u8 pad_708[0x7d4 - 0x708];
    UnkStruct_0200b218_2 e;
    u8 pad_7DC[0x824 - 0x7dc];
    int unk_824;
    int unk_828;
    int unk_82C;
    int unk_830;
    int unk_834;
    int unk_838;
} UnkStruct_0200b218_3;

extern void func_0200f268(UnkStruct_0200b218_3 *s, int k);
extern void *func_ov004_0223badc(int);
extern unsigned int *func_0200f27c(UnkStruct_0200b218_3 *s, int k);
extern u32 _s32_div_f(u32 a, u32 b);
extern void func_0200ee40(UnkStruct_0200b218_3 *s);
extern void func_0200f650(UnkStruct_0200b218_3 *s, int a);

void func_0200b218(UnkStruct_0200b218_3 *self)
{
    int tested_value0;
    UnkStruct_0200b218 sv;
    UnkStruct_0200b218 *q;
    B48 a;
    B48 b;
    UnkStruct_0200b218_2 *e;
    int *p;
    u32 v;
    int t;
    short sh;

    if (self->unk_704 != 0x16) {
        self->unk_830 = 0;
        self->unk_834 = 0;
        self->unk_838 = 0;
        func_0200f268(self, 0xd);
        return;
    }
    e = &self->e;
    if ((tested_value0 = (int) (e->unk_04)) >= 0) {
        p = func_ov004_0223badc(tested_value0);
        if (p == 0) {
            return;
        }
        self->unk_824 = p[0];
        self->unk_828 = p[1];
        self->unk_82C = p[2];
        func_0200f27c(self, 0xd);
        self->unk_830 = 0x1000;
        self->unk_834 = 0x1000;
        self->unk_838 = 0x1000;
        e->unk_04 = -1;
    }
    v = self->unk_2D8.b12;
    if (v < 6) {
        return;
    }
    t = 0x1000 - _s32_div_f((v - 6) << 12, 0xc);
    if (t < 0) {
        t = 0;
        func_0200f268(self, 0xd);
    }
    self->unk_830 = t;
    self->unk_834 = t;
    self->unk_838 = t;
    q = &self->g;
    sv.x = q->x;
    sv.y = q->y;
    sv.z = q->z;
    sh = self->unk_D0;
    a = self->unk_298;
    b = self->unk_698;
    func_0200ee40(self);
    func_0200f650(self, t);
    self->g.x = *(int *) &sv.x;
    self->g.y = *(int *) &sv.y;
    self->g.z = *(int *) &sv.z;
    self->unk_D0 = sh;
    self->unk_298 = a;
    self->unk_698 = b;
}
