/* fish_shadow_swim: 6 functions, module ov003
 * mwccarm 1.2/base -O4,s
 * func_ov003_0222af74 @ 0x0222af74, 0x240 bytes, Thumb
 * func_ov003_0222ae2c @ 0x0222ae2c, 0x148 bytes, Thumb
 * func_ov003_0222ad80 @ 0x0222ad80, 0xac bytes, Thumb
 * func_ov003_0222ad2c @ 0x0222ad2c, 0x54 bytes, Thumb
 * func_ov003_0222aba4 @ 0x0222aba4, 0x188 bytes, Thumb
 * func_ov003_0222ab4c @ 0x0222ab4c, 0x58 bytes, Thumb
 */

#include "types.h"

typedef struct {
    int x, y, z;
} UnkStruct_0222af74;

typedef struct {
    char pad_00[8];
    UnkStruct_0222af74 v;
} UnkStruct_0222af74_2;

typedef struct {
    u8 b;
    u8 unk_01;
    char pad[10];
    u16 w;
    char pad_0E[6];
} UnkStruct_0222af74_3;

typedef struct {
    u8 *p;
    int pad;
} UnkStruct_0222af74_4;

typedef struct {
    char pad_00[0x7e];
    signed char unk_7E;
    char pad_7F[0x120 - 0x7f];
    UnkStruct_0222af74 unk_120;
    char pad_12C[0x138 - 0x12c];
    s16 unk_138;
    char pad_13A[2];
    int unk_13C;
    char pad_140[0x1ff - 0x140];
    u8 kind;
    char pad_200[0x225 - 0x200];
    u8 unk_225;
    char pad_226[1];
    signed char unk_227;
    char pad_228[0x22c - 0x228];
    UnkStruct_0222af74_2 *h;
} UnkStruct_0222af74_5;

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

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    int x, y, z;
} UnkStruct_0222aba4;

typedef struct {
    char pad_00[8];
    UnkStruct_0222aba4 v;
} UnkStruct_0222aba4_2;

typedef struct {
    volatile u16 id;
    u16 pad_02;
    int pad_04;
} UnkStruct_0222aba4_3;

typedef struct {
    char pad_00[0x7e];
    s8 unk_7E;
    char pad_7F[0x138 - 0x7f];
    s16 unk_138;
    char pad_13A[2];
    int unk_13C;
    char pad_140[0x1ff - 0x140];
    u8 kind;
    char pad_200[0x224 - 0x200];
    u8 unk_224;
    u8 unk_225;
    char pad_226[1];
    s8 unk_227;
    char pad_228[0x22c - 0x228];
    UnkStruct_0222aba4_2 *h;
    UnkStruct_0222aba4 unk_230;
    char pad_23C[2];
    u8 unk_23E;
    u8 unk_23F;
} UnkStruct_0222aba4_4;

extern UnkStruct_0222af74_3 data_ov003_0223c014[];
extern UnkStruct_0222af74_4 data_ov003_0223bf04[];
extern u8 data_020cb786[];
extern s16 func_0200322c(UnkStruct_0222af74 *a, UnkStruct_0222af74 *b);
extern void func_ov003_0222be78(UnkStruct_0222af74 *p, int a, int b);
extern void func_ov003_022277fc(UnkStruct_0222af74_5 *s, int n);
extern int func_ov003_0222799c(UnkStruct_0222af74 *p, UnkStruct_0222af74 *t, int a, int b, int c);
extern int func_ov003_0222793c(int a, int b);
extern void func_02095764(volatile u16 *t, int a);
extern void func_0206026c(UnkStruct_0222af74_2 *h, int a);
extern int data_ov003_0225f0c0;
extern E20 data_ov003_0223c01e[];
extern int func_02056f28(int *p, int n);
extern int func_ov003_0222791c(int a, int b);
extern void *func_02095794(int n);
extern int data_020c904c;
extern void func_02091278(void *h, Vec3 *v, int a, int b);
extern int func_ov003_0222a784(void *self);
extern int func_ov003_0222a398(void *self);
extern u8 data_021fbdd8;
extern u8 data_ov003_0223c016[];
extern u8 data_ov003_0223c017[];
extern int func_ov003_0222a3ec(void *self, u8 k);

int func_ov003_0222af74(UnkStruct_0222af74_5 *self)
{
    UnkStruct_0222af74_2 *h;
    UnkStruct_0222af74 *tgt;
    int ok;
    u16 lo, hi;
    volatile u16 t;
    int sel;
    int *p13c;
    int spd;
    int ang;
    int r;

    h = self->h;
    if (h == 0) {
        return 0;
    }
    if (self->unk_227 == -1) {
        return 0;
    }
    tgt = &h->v;
    func_ov003_022277fc(self, 0x18);
    func_02095764(&t, self->unk_227);
    ok = 0;
    lo = t;
    hi = t;
    if (hi >= 0x1374 && lo <= 0x1374) {
        ok = 1;
    }
    if (ok != 0) {
        sel = 0;
    } else if (lo >= 0x1375 && lo <= 0x1375) {
        sel = 1;
    } else {
        return 0;
    }
    p13c = &self->unk_13C;
    if (*p13c >= data_ov003_0223bf04[sel].p[data_020cb786[self->unk_7E * 6]]) {
        *p13c = 0;
        func_0206026c(h, 4);
        return 0;
    }
    switch (self->unk_225) {
        case 6:
            spd = ((int) data_ov003_0223c014[self->kind].b << 12) / 100;
            ang = func_0200322c(&self->unk_120, tgt);
            func_ov003_0222be78(&self->unk_120, 0x180, ang);
            func_ov003_0222be78(&self->unk_120, 0xc0, (s16) (ang + 0x4000));
            if (func_ov003_0222799c(&self->unk_120, tgt, spd, spd, spd) != 0) {
                self->unk_225 = 8;
            } else {
                self->unk_225 = 7;
            }
            break;
        case 7:
            spd = ((int) data_ov003_0223c014[self->kind].b << 12) / 100;
            ang = func_0200322c(&self->unk_120, tgt);
            func_ov003_0222be78(&self->unk_120, 0x180, ang);
            func_ov003_0222be78(&self->unk_120, 0xc0, (s16) (ang - 0x4000));
            if (func_ov003_0222799c(&self->unk_120, tgt, spd, spd, spd) != 0) {
                self->unk_225 = 8;
            } else {
                self->unk_225 = 6;
            }
            break;
        case 8:
            spd = ((int) data_ov003_0223c014[self->kind].unk_01 << 12) / 100;
            func_ov003_0222be78(&self->unk_120, 0x180, func_0200322c(tgt, &self->unk_120));
            r = func_ov003_0222793c(0, 100);
            if (func_ov003_0222799c(&self->unk_120, tgt, spd, spd, spd) == 0) {
                if (r >= 0x46) {
                    self->unk_225 = 6;
                } else {
                    self->unk_225 = 9;
                }
            }
            break;
        case 9:
            if (func_ov003_0222793c(0, 100) <= 0x32) {
                self->unk_225 = 7;
            }
            break;
    }
    self->unk_138 = func_0200322c(&self->unk_120, tgt);
    return 1;
}

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
    func_ov003_0222be78((UnkStruct_0222af74 *) (&self->unk_120), r, ang);
    o = func_02095794(4);
    if (o != 0) {
        func_ov003_0222be78((UnkStruct_0222af74 *) (&self->unk_120), 0xa00, (int) func_0200322c((UnkStruct_0222af74 *) o, (UnkStruct_0222af74 *) (&t)));
    }
    return 1;
}

int func_ov003_0222ad80(char *self)
{
    Vec3 v;
    int n;
    int d;
    func_ov003_022277fc((UnkStruct_0222af74_5 *) self, 0x1c);
    n = *(int *) (self + 0x13c);
    d = 0x19 * (n + 0xa);
    if (d >= 0x180) {
        d = 0x180;
    }
    if (*(u8 *) (self + 0x7f)) {
        if (n >= 0x14) {
            func_ov003_022277fc((UnkStruct_0222af74_5 *) self, 3);
        } else if (n >= 0xf) {
            func_ov003_022277fc((UnkStruct_0222af74_5 *) self, 0x10);
        } else {
            func_ov003_022277fc((UnkStruct_0222af74_5 *) self, 0x20);
        }
    }
    func_ov003_0222be78((UnkStruct_0222af74 *) (self + 0x120), d, *(short *) (self + 0x138));
    v.x = *(int *) (self + 0x120);
    v.y = *(int *) (self + 0x124);
    v.z = *(int *) (self + 0x128);
    v.y = data_020c904c;
    func_02091278(*(void **) (self + 0x204), &v, 0, 0);
    return 1;
}

void func_ov003_0222ad2c(void *self)
{
    if (*(u8 *) ((char *) self + 0x23c) == 1) {
        switch (*(u8 *) ((char *) self + 0x224)) {
            case 3:
            case 4:
            case 5:
                func_ov003_0222a784(self);
                break;
            case 6:
                break;
            default:
                if (func_ov003_0222a398(self) == 0) {
                    func_ov003_0222a784(self);
                }
                break;
        }
    }
}

int func_ov003_0222aba4(UnkStruct_0222aba4_4 *self)
{
    UnkStruct_0222aba4_3 w;
    UnkStruct_0222aba4_2 *h;
    int ret;
    unsigned int ok;
    int idx;
    u16 lo, hi;
    int v;
    UnkStruct_0222aba4 *sv;
    UnkStruct_0222aba4 *dv;

    ret = 0;
    if (self == 0) {
        return ret;
    }
    h = self->h;
    if (h == 0) {
        func_ov003_0222a784((void *) self);
        return ret;
    }
    switch (self->unk_224) {
        case 4:
            func_02095764((volatile u16 *) (&w), self->unk_227);
            ok = 0;
            lo = w.id;
            hi = w.id;
            if (hi >= 0x1374 && lo <= 0x1374) {
                ok = 1;
            }
            if (ok) {
                idx = 0;
            } else if (lo >= 0x1375 && lo <= 0x1375) {
                idx = 1;
            } else {
                func_ov003_0222a784((void *) self);
                return 0;
            }
            if (data_021fbdd8 == 0) {
                if (self->unk_13C > ((u8 * *) data_ov003_0223bf04)[idx * 2][data_020cb786[6 * self->unk_7E]] - 1) {
                    func_ov003_0222a784((void *) self);
                    return 0;
                }
            }
            self->unk_224 = 5;
            self->unk_225 = 0xa;
            self->unk_13C = 0;
            func_0206026c((UnkStruct_0222af74_2 *) h, 6);
            if (func_ov003_0222793c(0, 2) != 0) {
                v = 1;
            } else {
                v = 0;
            }
            self->unk_23E = v;
            self->unk_23F = func_ov003_0222793c(data_ov003_0223c016[20 * self->kind], data_ov003_0223c017[20 * self->kind]);
            sv = &h->v;
            dv = &self->unk_230;
            dv->x = h->v.x;
            dv->y = sv->y;
            dv->z = sv->z;
            if (self->unk_23E != 0) {
                self->unk_138 = self->unk_138 - 0x4000;
            } else {
                self->unk_138 = self->unk_138 + 0x4000;
            }
            ret = 1;
            break;
        case 6:
            break;
        case 3:
            func_ov003_0222a784((void *) self);
            break;
        default:
            if (func_ov003_0222a398((void *) self) == 0) {
                func_ov003_0222a784((void *) self);
            }
            break;
    }
    return ret;
}

int func_ov003_0222ab4c(void *self)
{
    int r = 0;
    if (self == 0) {
        return r;
    }
    if (*(u8 *) ((char *) self + 0x224) != 5) {
        return r;
    }
    if (*(int *) ((char *) self + 0x13c) >= *(u8 *) ((char *) self + 0x23f)) {
        if (func_ov003_0222a3ec(self, *(u8 *) ((char *) self + 0x211))) {
            r = 2;
        } else {
            func_ov003_0222a784(self);
            r = 1;
        }
    }
    return r;
}
