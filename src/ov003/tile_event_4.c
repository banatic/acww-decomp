/* tile_event_4: 7 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_022221cc @ 0x022221cc, 0xc0 bytes, Thumb
 * func_ov003_0222214c @ 0x0222214c, 0x80 bytes, Thumb
 * func_ov003_022220f4 @ 0x022220f4, 0x58 bytes, Thumb
 * func_ov003_022220a4 @ 0x022220a4, 0x50 bytes, Thumb
 * func_ov003_02221fb0 @ 0x02221fb0, 0xf4 bytes, Thumb
 * func_ov003_02221f50 @ 0x02221f50, 0x60 bytes, Thumb
 * func_ov003_02221f14 @ 0x02221f14, 0x3c bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[8];
    unsigned short unk_08;
    char pad_0A[0x10 - 0xa];
    int unk_10;
    int unk_14;
    Vec3 unk_18;
    char pad_24[0x30 - 0x24];
    Vec3 unk_30;
    char pad_3C[0x4c - 0x3c];
    short unk_4C;
    char pad_4E[0x60 - 0x4e];
    int unk_60;
} UnkStruct_022221cc;

typedef struct {
    char pad_00[0x18];
    int unk_18;
    int unk_1C;
    int unk_20;
    char pad_24[0x0c];
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3C;
    int unk_40;
    int unk_44;
    short unk_48;
    char pad_4A[0x16];
} UnkStruct_0222214c;

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_0222214c_2;

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_0222214c_3;

typedef struct {
    fx32 x, y, z;
} VecFx32;

typedef struct {
    char pad_00[0x18];
    VecFx32 pos; // 0x18
    fx32 unk_24;
    char pad_28[8];
    VecFx32 vel; // 0x30
    char pad_3C[0x12];
    unsigned short angle; // 0x4e
} UnkStruct_022220f4;

struct In {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
};

struct UnkStruct_022220a4 {
    char pad_00[0x18];
    unsigned int unk_18;
    unsigned int unk_1C;
    unsigned int unk_20;
    char pad_24[0x0c];
    unsigned int unk_30;
    unsigned int unk_34;
    unsigned int unk_38;
    unsigned int unk_3C;
    unsigned int unk_40;
    unsigned int unk_44;
    char pad_48[0x18];
    char data[0x7f];
};

typedef struct {
    char pad_00[0x18];
    char unk_18[4];
    int unk_1C;
    char pad_20[0x10];
    int unk_30;
    int unk_34;
    int unk_38;
    char pad_3C[0x10];
    short unk_4C;
    char pad_4E[2];
    short unk_50;
    short unk_52;
} UnkStruct_02221fb0;

typedef struct {
    int x, y;
} UnkStruct_02221f50;

typedef struct {
    char pad_00[0x30];
    fx32 unk_30, unk_34, unk_38, unk_3C, unk_40, unk_44;
    char pad_48[0x58];
    unsigned char unk_A0;
} UnkStruct_02221f50_2;

struct UnkStruct_02221f14;

struct UnkStruct_02221f14 {
    char pad_00[0x18];
    int unk_18;
    int unk_1C;
    char pad_20[0x10];
    int unk_30;
    int unk_34;
    int unk_38;
};

extern void VEC_Add(void *a, void *b, void *c);
extern void func_0204f794(int *out, int a, int b);
extern int func_020044c0(void *p, int a, int b, int c);
extern void func_ov003_02222860(void *self);
extern void func_ov003_02222aa4(void *self);
extern fx16 FX_SinCosTable_[];
extern void func_02044534(void);
extern void func_ov003_0222da78(void *a);
extern void func_ov003_0222284c(UnkStruct_02221fb0 *s);
extern void func_ov003_02224140(int, int, int, int);

void func_ov003_022221cc(UnkStruct_022221cc *self)
{
    volatile unsigned short t;
    int out[3];
    unsigned int ok;
    unsigned short lo, hi;
    int q;

    self->unk_30.y = self->unk_30.y - 0x400;
    VEC_Add(&self->unk_18, &self->unk_30, &self->unk_18);
    if (self->unk_18.y < 0) {
        if (self->unk_4C == 0) {
            func_0204f794(out, self->unk_10, self->unk_14);
            q = (out[2] - self->unk_18.z) / 8;
            self->unk_30.x = (out[0] - self->unk_18.x) / 8;
            self->unk_30.y = 0x1000;
            self->unk_30.z = q;
            self->unk_4C = 1;
            t = 0xfff1;
            t = self->unk_08;
            ok = 0;
            lo = t;
            hi = t;
            if (hi >= 0x1492 && lo <= 0x14fd) {
                ok = 1;
            }
            if (ok > 0) {
                func_020044c0(&self->unk_60, 0x70, 0x7f, 0);
            }
        } else {
            self->unk_30.x = 0;
            self->unk_30.y = 0;
            self->unk_30.z = 0;
            func_ov003_02222860(self);
        }
        self->unk_18.y = 0;
    }
}

void func_ov003_0222214c(UnkStruct_0222214c *self, UnkStruct_0222214c_2 *b, UnkStruct_0222214c_3 *c)
{
    int locals[3];
    int mod1, mod2, mod3;

    func_0204f794(locals, b->unk_00, b->unk_04);

    mod1 = (locals[2] - c->unk_08) / 30;
    mod2 = -(c->unk_04 / 30);
    mod3 = (locals[0] - c->unk_00) / 30;

    self->unk_30 = mod3;
    self->unk_34 = mod2;
    self->unk_38 = mod1;

    self->unk_18 = c->unk_00;
    self->unk_1C = c->unk_04;
    self->unk_20 = c->unk_08;

    self->unk_3C = 0x1000;
    self->unk_40 = 0x1000;
    self->unk_44 = 0x1000;

    if (self->unk_48 != 0) {
        func_ov003_02222aa4(self);
    }

    func_020044c0((char *) self + 0x60, 0x7eb, 0x7f, 0);
}

static __inline fx16 FX_SinIdx(int idx)
{
    return FX_SinCosTable_[((idx >> 4) << 1)];
}

void func_ov003_022220f4(UnkStruct_022220f4 *self)
{
    VEC_Add((void *) (&self->pos), (void *) (&self->vel), (void *) (&self->pos));
    self->angle += 0x888;
    self->unk_24 = FX_SinIdx((unsigned short) (short) self->angle) >> 1;
    if (self->pos.y < 0) {
        self->pos.y = 0;
        self->vel.x = 0;
        self->vel.y = 0;
        self->vel.z = 0;
        func_ov003_02222860(self);
    }
}

void func_ov003_022220a4(struct UnkStruct_022220a4 *s, void *unused, struct In *t)
{
    s->unk_30 = 0;
    s->unk_34 = 0x800;
    s->unk_38 = 0x300;
    s->unk_18 = t->unk_00;
    s->unk_1C = t->unk_04;
    s->unk_20 = t->unk_08;
    s->unk_3C = 0x1000;
    s->unk_40 = 0x1000;
    s->unk_44 = 0x1000;
    func_020044c0((void *) ((int) (s->data)), (int) (0x7d6), (int) (0x7f), 0);
    ((void) (func_ov003_02222aa4((void *) s)), func_02044534());
}

void func_ov003_02221fb0(UnkStruct_02221fb0 *s)
{
    switch (s->unk_4C) {
        case 0:
            s->unk_34 -= 0x400;
            VEC_Add(&s->unk_18, &s->unk_30, &s->unk_18);
            if (s->unk_1C < 0) {
                s->unk_1C = 0;
                s->unk_30 = 0;
                s->unk_34 = 0x1000;
                s->unk_38 = 0;
                s->unk_4C = 1;
            }
            break;
        case 1:
            s->unk_34 -= 0x400;
            VEC_Add(&s->unk_18, &s->unk_30, &s->unk_18);
            if (s->unk_1C < 0) {
                s->unk_1C = 0;
                s->unk_30 = 0;
                s->unk_34 = 0;
                s->unk_38 = 0;
                s->unk_4C = 2;
                s->unk_50 = 0x14;
            }
            break;
        case 2:
            s->unk_50 = (short) (s->unk_50 - 1);
            if (s->unk_50 < 0) {
                func_ov003_0222da78(&s->unk_18);
                s->unk_50 = 0x1e;
                s->unk_4C = 3;
            }
            break;
        case 3:
            s->unk_50 = (short) (s->unk_50 - 1);
            if (s->unk_50 < 0) {
                s->unk_4C = 4;
            }
            break;
        default:
            s->unk_52 = (short) (s->unk_52 - 1);
            if (s->unk_52 < 0) {
                func_ov003_0222284c(s);
            }
            break;
    }
}

static __inline fx16 FX_CosIdx(int idx)
{
    return FX_SinCosTable_[((idx >> 4) << 1) + 1];
}

void func_ov003_02221f50(UnkStruct_02221f50_2 *self, UnkStruct_02221f50 *p, int a)
{
    func_0204f794((int *) ((char *) self + 0x18), p->x, p->y);
    self->unk_30 = (FX_SinIdx((unsigned short) a) * 0x400) >> 12;
    self->unk_34 = 0x1000;
    self->unk_38 = (FX_CosIdx((unsigned short) a) * 0x400) >> 12;
    self->unk_3C = 0x1000;
    self->unk_40 = 0x1000;
    self->unk_44 = 0x1000;
    self->unk_A0 = 0;
    func_ov003_02224140(p->x, p->y, 0xfff1, 0);
}

void func_ov003_02221f14(struct UnkStruct_02221f14 *s)
{
    s->unk_34 -= 0x400;
    VEC_Add((void *) (&s->unk_18), (void *) (&s->unk_30), (void *) (&s->unk_18));
    if (s->unk_1C >= 0) {
        return;
    }
    s->unk_1C = 0;
    s->unk_30 = 0;
    s->unk_34 = 0;
    s->unk_38 = 0;
    func_ov003_02222860((void *) s);
}
