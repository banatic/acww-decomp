/* field_actor_42: 6 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_02216970 @ 0x02216970, 0x34 bytes, Thumb
 * func_ov003_02216948 @ 0x02216948, 0x28 bytes, Thumb
 * func_ov003_02216780 @ 0x02216780, 0x1c8 bytes, Thumb
 * func_ov003_02216740 @ 0x02216740, 0x40 bytes, Thumb
 * func_ov003_022166f8 @ 0x022166f8, 0x46 bytes, Thumb
 * func_ov003_022166e8 @ 0x022166e8, 0xe bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x800];
    int unk_800;
} UnkStruct_02216970;

struct VT;

struct UnkStruct_02216780 {
    struct VT *vt;
};

struct VT {
    void (*fn[64])(struct UnkStruct_02216780 *, short *);
};

struct UnkStruct_02216780_2 {
    u8 pad_00[0x5c];
    int v[3];
    u8 pad_68[0x8e - 0x68];
    short unk_8E;
    u8 pad_90[0x168 - 0x90];
    struct UnkStruct_02216780 *unk_168;
    u8 unk_16C;
    u8 pad_16D[0x7d4 - 0x16d];
    u8 unk_7D4[4];
    u8 pad_7D8[0x800 - 0x7d8];
    unsigned int unk_800;
};

struct UnkStruct_02216740 {
    char pad_00[0x2d0];
    int unk_2D0;
    char pad_2D4[0x7f0 - 0x2d4];
    int unk_7F0;
    char pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
};

struct UnkStruct_022166f8 {
    char pad_00[0x98];
    int unk_98;
};

extern int data_020ccf94;
extern int func_02073908(int a, int b);
extern int func_0200f290(UnkStruct_02216970 *p, int a);
extern void func_02010f5c(int argument0);
extern int func_02056f28(void *p, int n);
extern void func_0201107c(struct UnkStruct_02216780_2 *self, int *r);
extern void func_020110c4(u16 *out, struct UnkStruct_02216780_2 *self);
extern int func_0200fc90(struct UnkStruct_02216780_2 *self);
extern int func_0200f328(struct UnkStruct_02216780_2 *self, int a);
extern unsigned int *func_0200f27c(struct UnkStruct_02216780_2 *self, int a);
extern void func_0200f268(struct UnkStruct_02216780_2 *self, int a);
extern int func_02095694(int a, unsigned int b);
extern void func_ov003_022241a4(int *p);
extern int func_020912d4(int a, int *b, short *c, int d);
extern int FX_MulFunc(int a, int b);
extern int func_ov003_0221abf8(void *object, int flag);
extern short FX_SinCosTable_[];
extern int func_02056f94(void *p);
extern int func_02008258(void *obj, int field);
extern int func_0200d4e8(void *obj, int a, int b, int c);
extern int func_0201100c(struct UnkStruct_022166f8 *self);
extern void func_02010d64(struct UnkStruct_022166f8 *self);
extern int func_02011398(int a, int b);

void func_ov003_02216780(struct UnkStruct_02216780_2 *self);

void func_ov003_02216970(UnkStruct_02216970 *param)
{
    int ret;
    ret = func_02073908(data_020ccf94, param->unk_800);
    if (ret != 0) {
        return;
    }
    ret = func_0200f290(param, 0x1C);
    if (ret == 0) {
        return;
    }
    func_ov003_02216780((struct UnkStruct_02216780_2 *) param);
}

void func_ov003_02216948(void *p)
{
    func_02010f5c((int) p);
    if (func_02056f28((char *) p + 0x2d0, 8)) {
        func_ov003_02216780((struct UnkStruct_02216780_2 *) p);
    }
}

void func_ov003_02216780(struct UnkStruct_02216780_2 *self)
{
    short ang;
    u16 out;
    int t;
    int pair[2];
    int v[3];
    u8 *p;
    int st;

    t = -819;
    func_0201107c(self, &t);
    p = self->unk_7D4;
    st = func_0200fc90(self);
    if (p[2] != 0) {
        st = st + 1;
        if (st == 7) {
            func_0200f328(self, 0x83e);
        } else if (st == 9) {
            func_0200f328(self, 0x83f);
        }
    }
    func_02095694(st, self->unk_800);
    func_0200f27c(self, 9);
    if (p[3] != 0) {
        {
            int y = p[1];
            int x = p[0];
            pair[0] = x;
            pair[1] = y;
        }
        func_ov003_022241a4(pair);
        func_0200f268(self, 0x12);
        func_0200f268(self, 0x1c);
    }

    switch (self->unk_16C) {
        case 0: {
            int i;
            int b;
            int dz;
            int a;
            int dx;
            int *q = self->v;
            v[0] = self->v[0];
            v[1] = q[1];
            v[2] = q[2];
            ang = self->unk_8E;
            i = (u16) ang >> 4;
            a = FX_SinCosTable_[i * 2];
            b = FX_SinCosTable_[i * 2 + 1];
            dz = FX_MulFunc(b, 0xccd) - FX_MulFunc(a, -0x800);
            dx = FX_MulFunc(a, 0xccd) + FX_MulFunc(b, -0x800);
            v[0] = v[0] + dx;
            v[2] = v[2] + dz;
            v[1] = v[1] + 0xccd;
            ang = ang + 0x2000;
            func_020912d4(4, v, &ang, 0);
            func_0200f328(self, 0x83c);
            break;
        }
        case 1:
            func_0200f328(self, 0x7df);
            break;
        case 2:
            func_0200f328(self, 0x7df);
            if (self->unk_168 != 0) {
                func_020110c4(&out, self);
                self->unk_168->vt->fn[24](self->unk_168, (short *) &out);
            }
            break;
        case 3:
            if (func_02073908((int) ((*(void **) &data_020ccf94)), self->unk_800) != 0) {
                if (func_ov003_0221abf8(self->unk_168, 1) == 0) {
                    func_0200f328(self, 0x7df);
                }
            } else {
                func_0200f328(self, 0x7df);
            }
            break;
    }

    self->unk_168 = 0;
    self->unk_16C = 0;
}

void func_ov003_02216740(struct UnkStruct_02216740 *obj)
{
    if (func_02056f94(&obj->unk_2D0) != 0) {
        obj->unk_7FC = func_02008258(obj, obj->unk_7F0);
        func_0200d4e8(obj, 3, 1, -1);
    }
}

void func_ov003_022166f8(struct UnkStruct_022166f8 *self)
{
    int val;
    int temp;
    func_ov003_02216948((void *) self);
    func_0201100c(self);
    func_02010d64(self);
    val = self->unk_98;
    if (val < 0) {
        val = -val;
    }
    temp = -1 * func_02011398(val, 0);
    func_0201107c((struct UnkStruct_02216780_2 *) self, &temp);
    func_ov003_02216740((struct UnkStruct_02216740 *) self);
}

void func_ov003_022166e8(unsigned char *r0, unsigned char r1, unsigned char r2, unsigned int *r3)
{
    r0[2] = r1;
    r0[3] = r2;
    r0[0] = (unsigned char) (*r3);
    r0[1] = (unsigned char) (*(r3 + 1));
}
