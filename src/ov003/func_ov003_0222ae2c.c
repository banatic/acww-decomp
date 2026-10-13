/* func_ov003_0222ae2c @ 0x0222ae2c, 0x148 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_0222ae2c;

typedef struct {
    char pad_00[8];
    UnkStruct_0222ae2c v;
} UnkStruct_0222ae2c_2;

typedef struct {
    u16 v;
    char pad_02[18];
} E20;

typedef struct {
    char pad_00[0x120];
    UnkStruct_0222ae2c unk_120;
    char pad_12C[0x138 - 0x12c];
    s16 unk_138;
    char pad_13A[0x1e0 - 0x13a];
    int unk_1E0;
    char pad_1E4[4];
    int unk_1E8;
    char pad_1EC[0x1ff - 0x1ec];
    u8 kind;
    char pad_200[0x22c - 0x200];
    UnkStruct_0222ae2c_2 *h;
    char pad_230[0x23e - 0x230];
    u8 dir;
} UnkStruct_0222ae2c_3;

extern int data_ov003_0225f0c0;
extern E20 data_ov003_0223c01e[];

extern int func_02056f28(int *p, int n);
extern int func_ov003_0222791c(int a, int b);
extern void func_ov003_0222be78(UnkStruct_0222ae2c *p, int a, int b);
extern void *func_02095794(int n);
extern int func_0200322c(void *p, UnkStruct_0222ae2c *v);

int func_ov003_0222ae2c(UnkStruct_0222ae2c_3 *self)
{
    UnkStruct_0222ae2c t;
    UnkStruct_0222ae2c *q;
    UnkStruct_0222ae2c_2 *h;
    void *o;
    int step;
    int ang;
    int v;
    int r;

    h = self->h;
    if (h == 0) {
        return 0;
    }
    if (self->kind >= 3) {
        step = 0x1000;
    } else {
        step = 0x1249;
    }
    if (self->dir != 0) {
        if (func_02056f28(&self->unk_1E0, 4) != 0) {
            self->unk_1E8 = 0x3000;
        }
        self->unk_138 = self->unk_138 + step;
        ang = (s16) (self->unk_138 - 0x4000);
    } else {
        if (func_02056f28(&self->unk_1E0, 0xb) != 0) {
            self->unk_1E8 = 0xa000;
        }
        self->unk_138 = self->unk_138 - step;
        ang = (s16) (self->unk_138 + 0x4000);
    }
    v = data_ov003_0225f0c0 + func_ov003_0222791c(3, 10);
    data_ov003_0225f0c0 = v;
    if (v < -12) {
        data_ov003_0225f0c0 = -12;
    } else if (v > 0x14) {
        data_ov003_0225f0c0 = 0x14;
    }
    r = data_ov003_0225f0c0 + func_ov003_0222791c(0, 0xf);
    r = ((r + data_ov003_0223c01e[self->kind].v) << 12) / 100;
    q = &h->v;
    t.x = q->x;
    t.y = q->y;
    t.z = q->z;
    self->unk_120.x = t.x;
    self->unk_120.z = t.z;
    func_ov003_0222be78(&self->unk_120, r, ang);
    o = func_02095794(4);
    if (o != 0) {
        func_ov003_0222be78(&self->unk_120, 0xa00, func_0200322c(o, &t));
    }
    return 1;
}
