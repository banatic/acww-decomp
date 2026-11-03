/* camera_view: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203c030 @ 0x0203c030, 0x38 bytes, Thumb
 * func_0203be6c @ 0x0203be6c, 0x1c4 bytes, Thumb
 * func_0203bd84 @ 0x0203bd84, 0xe8 bytes, Thumb
 * func_0203bcc4 @ 0x0203bcc4, 0xc0 bytes, Thumb
 * func_0203bc50 @ 0x0203bc50, 0x74 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x1b0];
    int unk_1B0;
    int unk_1B4;
    int unk_1B8;
    char pad_1BC[0xc];
    short unk_1C8;
} UnkStruct_0203c030;

typedef struct {
    fx32 x, y, z;
} VecFx32;

typedef struct UnkStruct_0203be6c {
    u8 pad_00[0xc8];
    fx32 unk_C8; // 0x0c8
    u8 pad_CC[0xfc - 0xcc];
    s16 unk_FC;      // 0x0fc
    s16 unk_FE;      // 0x0fe
    fx32 unk_100;    // 0x100
    VecFx32 unk_104; // 0x104
    VecFx32 unk_110; // 0x110
    u8 pad_11C[0x148 - 0x11c];
    s16 unk_148;     // 0x148
    s16 unk_14A;     // 0x14a
    fx32 unk_14C;    // 0x14c
    VecFx32 unk_150; // 0x150
    VecFx32 unk_15C; // 0x15c
    u8 pad_168[0x1e4 - 0x168];
    fx32 unk_1E4; // 0x1e4
    fx32 unk_1E8; // 0x1e8
} UnkStruct_0203be6c;

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x168];
    Vec3 A;
    short sh;
    char pad_176[0x188 - 0x176];
    Vec3 B;
    Vec3 C;
    Vec3 D;
} UnkStruct_0203bd84;

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    char pad_00[0x110];
    Vec3 pos;
} UnkStruct_0203bc50;

extern void func_0203c40c(void *s, short val);
extern int func_0203ad88(void);
extern int func_0203c528(UnkStruct_0203be6c *self);
extern int func_0203c4e4(UnkStruct_0203be6c *self);
extern int func_0203c4d0(UnkStruct_0203be6c *self);
extern int func_0203c4bc(UnkStruct_0203be6c *self);
extern fx32 func_020643dc(fx32 a, int b, int c, int d, int e);
extern void func_020eaca0(VecFx32 *dst, const VecFx32 *a, const VecFx32 *b);
extern void func_020eabc8(VecFx32 *v, fx32 t);
extern void func_01ffd070(VecFx32 *dst, const VecFx32 *a, const VecFx32 *b);
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern void func_020ea78c(Vec3 *v, int s);
extern void func_020ea6e0(Vec3 *v, int a);
extern int func_0203f844(Vec3 *dst, Vec3 *src);
extern Vec3 *func_0203c59c(UnkStruct_0203bd84 *self);
extern void func_020ea634(Vec3 *v, int s);
extern Vec3 data_021c67d0;
extern Vec3 data_021c67b8;
extern int data_021c679c;
extern int VEC_Mag(Vec *v);
extern s16 FX_SinCosTable_[];
extern int func_020ea9c8(void *in);
extern int func_020ea838(void *in);
extern int func_0203c558(void *self);

void func_0203c030(UnkStruct_0203c030 *s)
{
    s->unk_1B0 = 0x1548;
    s->unk_1B4 = 0xf6;
    s->unk_1B8 = 0x0003e800;
    func_0203c40c(s, s->unk_1C8);
}

void func_0203be6c(UnkStruct_0203be6c *self)
{
    VecFx32 delta0;
    VecFx32 delta1;
    VecFx32 res0;
    VecFx32 res1;
    fx32 t;

    if (func_0203ad88()) {
        int a = func_0203c528(self);
        int b = func_0203c4e4(self);
        int c = func_0203c4d0(self);
        int d = func_0203c4bc(self);

        t = func_020643dc(self->unk_C8, a, b, c, d);

        func_020eaca0(&delta0, &self->unk_110, &self->unk_15C);
        func_020eabc8(&delta0, t);
        func_01ffd070(&res0, &self->unk_15C, &delta0);
        self->unk_15C.x = res0.x;
        self->unk_15C.y = res0.y;
        self->unk_15C.z = res0.z;

        func_020eaca0(&delta1, &self->unk_104, &self->unk_150);
        func_020eabc8(&delta1, t);
        func_01ffd070(&res1, &self->unk_150, &delta1);
        self->unk_150.x = res1.x;
        self->unk_150.y = res1.y;
        self->unk_150.z = res1.z;

        self->unk_14A = (s16) (self->unk_14A + FX_MulFunc(self->unk_FE - self->unk_14A, t));
        self->unk_148 = (s16) (self->unk_148 + FX_MulFunc(self->unk_FC - self->unk_148, t));
        self->unk_14C += FX_MulFunc(self->unk_100 - self->unk_14C, t);
        self->unk_1E8 += FX_MulFunc(self->unk_1E4 - self->unk_1E8, t);

        self->unk_C8 = self->unk_C8 + 0x1000;
    } else {
        self->unk_15C.x = self->unk_110.x;
        self->unk_15C.y = self->unk_110.y;
        self->unk_15C.z = self->unk_110.z;
        self->unk_150.x = self->unk_104.x;
        self->unk_150.y = self->unk_104.y;
        self->unk_150.z = self->unk_104.z;
        self->unk_14A = self->unk_FE;
        self->unk_148 = self->unk_FC;
        self->unk_14C = self->unk_100;
        self->unk_1E8 = self->unk_1E4;
    }
}

void func_0203bd84(UnkStruct_0203bd84 *self, Vec3 *src, int angle, int param, int gval)
{
    Vec3 v1, v2;
    int tmp;

    v1.x = 0;
    v1.y = 0;
    v1.z = gval;

    func_020ea78c(&v1, (short) -angle);
    func_020ea6e0(&v1, param);

    func_01ffd070((VecFx32 *) (&v2), (const VecFx32 *) src, (const VecFx32 *) (&v1));

    self->A.x = v2.x;
    self->A.y = v2.y;
    self->A.z = v2.z;

    tmp = func_0203f844(&self->B, src);

    func_0203f844(&self->C, func_0203c59c(self));

    self->D.x = 0;
    self->D.y = 0x1000;
    self->D.z = 0;

    func_020ea78c(&self->D, tmp);
    func_020ea634(&self->D, self->sh);

    data_021c67d0.x = src->x;
    data_021c67d0.y = src->y;
    data_021c67d0.z = src->z;

    {
        Vec3 *p = func_0203c59c(self);
        data_021c67b8.x = p->x;
        data_021c67b8.y = p->y;
        data_021c67b8.z = p->z;
    }

    data_021c679c = gval;
}

void func_0203bcc4(u8 *self, Vec *a, Vec *b)
{
    int r;
    int k;
    Vec t;

    r = func_0203f844((Vec3 *) (self + 0x188), (Vec3 *) a);
    func_0203f844((Vec3 *) (self + 0x194), (Vec3 *) b);
    *(int *) (self + 0x1a0) = 0;
    *(int *) (self + 0x1a4) = 0x1000;
    *(int *) (self + 0x1a8) = 0;
    k = (int) (u16) r >> 4;
    *(int *) (self + 0x1a4) = FX_SinCosTable_[k * 2 + 1];
    *(int *) (self + 0x1a8) = FX_SinCosTable_[k * 2];
    func_020ea634((Vec3 *) ((int *) (self + 0x1a0)), *(s16 *) (self + 0x174));
    (*(Vec *) &data_021c67d0).x = a->x;
    (*(Vec *) &data_021c67d0).y = a->y;
    (*(Vec *) &data_021c67d0).z = a->z;
    (*(Vec *) &data_021c67b8).x = b->x;
    (*(Vec *) &data_021c67b8).y = b->y;
    (*(Vec *) &data_021c67b8).z = b->z;
    func_020eaca0((VecFx32 *) (&t), (const VecFx32 *) a, (const VecFx32 *) b);
    data_021c679c = VEC_Mag(&t);
}

void func_0203bc50(UnkStruct_0203bc50 *self, Vec3 *p)
{
    Vec3 d;
    int v;

    self->pos.y = p->y;
    func_020eaca0((VecFx32 *) (&d), (const VecFx32 *) (&self->pos), (const VecFx32 *) p);
    v = func_020ea9c8(&d);
    if (v > func_0203c558(self)) {
        v -= func_0203c558(self);
        if (func_020ea838(&d) != 0) {
            self->pos.x -= (int) FX_MulFunc(d.x, v);
            self->pos.z -= (int) FX_MulFunc(d.z, v);
        }
    }
}
